#include <Adafruit_NeoPixel.h>

//Hardware data
#define LED_PIN        6
#define BUTTON_PIN     7
#define NUMPIXELS      102

//Brightness
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 80

//Generic Saber Variables
#define SABER_RETRACT_SPEED 5
#define DO_FLICKER
#define RANDOM_FLICKER 500

//Rainbow Saber Variables
#define RAINBOW_SPEED 25
#define DO_RAINBOW_FLICKER

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

bool StripIsOn = false;
bool firstTime = true;
bool isRainbow = false;
int prevR = 255;
int prevG = 0;
int prevB = 0;
int stateMachineVariable = 0;
int currentBrightness = 255;

void setup() {
  pinMode(LED_PIN,INPUT_PULLUP);
  pinMode(BUTTON_PIN,INPUT_PULLUP);

  pixels.begin();
  
  turnOffStrip(false);
  firstTime = false;
}

void loop() {
  if (getButtonPress()) {
    Serial.println("Long press");
    //This is a long press
    //Turn on/off
    if (StripIsOn) {
      turnOffStrip(true);
    } else {
      if (isRainbow) {
        unsheathRainbow();
      } else {
        turnOnStrip(prevR,prevG,prevB);
      }
    }
  } else {
    Serial.println("short press");
    //This is a short press
    //Change color

    switch(stateMachineVariable) {
      case 0:
        isRainbow = false;
        turnOnStrip(255,0,0); //Red
        break;
      case 1:
        turnOnStrip(255,25,0); //Orange
        break;
      case 2:
        turnOnStrip(255,255,0); //Yellow-Green
        break;
      case 3:
        turnOnStrip(255,180,0); //Yellow
        break;
      case 4:
        turnOnStrip(0,255,0); //Green
        break;
      case 5:
        turnOnStrip(0,0,255); //Blue
        break;
      case 6:
        turnOnStrip(0,50,255); //Cyan
        break;
      case 7:
        turnOnStrip(190*0.3,0,255*0.3); //Purple
        break;
      case 8:
        turnOnStrip(255,255,255); //White
        break;
      case 9:
        turnOffStrip(true);
        unsheathRainbow();
        stateMachineVariable = -1;
        break;
    }

    stateMachineVariable++;
  }
}

bool getButtonPress() {
  delay(1);
  if (!digitalRead(BUTTON_PIN)) { while(!digitalRead(BUTTON_PIN)) { doLEDFlicker(); } }
  delay(1);
  while(digitalRead(BUTTON_PIN)) { doLEDFlicker(); }
  delay(1);

  //We have pressed the button
  unsigned long prevMillis = millis();
  while(!digitalRead(BUTTON_PIN)) {
    if (millis() - prevMillis > 800) { return true; }
    doLEDFlicker();
  }

  return false;
}

void doLEDFlicker() {
  if (StripIsOn) {
    if (isRainbow) {
       rainbow(RAINBOW_SPEED);
    } else {
#ifndef DO_FLICKER
      if (random(0,RANDOM_FLICKER) == 1) {
        currentBrightness += random(-50,50);
        if (currentBrightness > MAX_BRIGHTNESS) { currentBrightness = MAX_BRIGHTNESS; }
        if (currentBrightness < MIN_BRIGHTNESS) { currentBrightness = MIN_BRIGHTNESS; }
        pixels.setBrightness(currentBrightness);
  
        for(int i = 0; i < NUMPIXELS; i++) {
          pixels.setPixelColor(i,pixels.Color(prevR,prevG,prevB));
        }
  
        pixels.show();
      }
#endif
    }
  }
}

void turnOnStrip(int R, int G, int B) {
  if (isRainbow) {
    StripIsOn = true;
    unsheathRainbow();
    return;
  }
  
  turnOffStrip(true);
  
  StripIsOn = true;
  prevR = R;
  prevG = G;
  prevB = B;
  for(int i = 0; i <= NUMPIXELS/2; i++) {
      pixels.setPixelColor(i,pixels.Color(R,G,B));
      pixels.setPixelColor(NUMPIXELS - i,pixels.Color(R,G,B));
      pixels.show();

      delay(SABER_RETRACT_SPEED);
  }
}

void turnOffStrip(bool doAnim) {
  int LED_Brightness = 50;
  if (StripIsOn) {
    for(int i = NUMPIXELS/2; i >= 0; i--) {
      if (i < 3) {
        pixels.setPixelColor(i,pixels.Color(LED_Brightness,LED_Brightness,LED_Brightness));
        pixels.setPixelColor(NUMPIXELS - i,pixels.Color(LED_Brightness,LED_Brightness,LED_Brightness));
      } else {
        pixels.setPixelColor(i,pixels.Color(0,0,0));
        pixels.setPixelColor(NUMPIXELS - i,pixels.Color(0,0,0));
      }

      if (doAnim) {
        pixels.show();

        delay(SABER_RETRACT_SPEED);
      }
    }

    if (!doAnim) {
      Serial.begin(115200);
      delay(50);
      Serial.println("Setting");
      pixels.show();
      delay(50);
    }
  }

  if (firstTime) {
    for(int i = NUMPIXELS/2; i >= 0; i--) {
      if (i < 3) {
        pixels.setPixelColor(i,pixels.Color(LED_Brightness,LED_Brightness,LED_Brightness));
        pixels.setPixelColor(NUMPIXELS - i,pixels.Color(LED_Brightness,LED_Brightness,LED_Brightness));
      } else {
        pixels.setPixelColor(i,pixels.Color(0,0,0));
        pixels.setPixelColor(NUMPIXELS - i,pixels.Color(0,0,0));
      }
    }
    pixels.show();
  }

  StripIsOn = false;
}
