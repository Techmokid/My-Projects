#include <Adafruit_NeoPixel.h>

#define LED_PIN        6
#define BUTTON_PIN     7
#define NUMPIXELS      102
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 100
#define RANDOM_FLICKER 50

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

bool StripIsOn = false;
int prevR = 0;
int prevG = 0;
int prevB = 0;
int stateMachineVariable = 0;
int currentBrightness = 255;

void setup() {
  pinMode(LED_PIN,INPUT_PULLUP);
  pinMode(BUTTON_PIN,INPUT_PULLUP);

  pixels.begin();

  turnOffStrip(false);
}

void loop() {
  if (getButtonPress()) {
    //This is a long press
    //Turn on/off
    if (StripIsOn) {
      turnOffStrip(true);
    } else {
      turnOnStrip(prevR,prevG,prevB);
    }
  } else {
    //This is a short press
    //Change color

    switch(stateMachineVariable) {
      case 0:
        turnOnStrip(255,0,0); //Red
        break;
      case 1:
        turnOnStrip(255,15,0); //Orange
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
        stateMachineVariable = -1;
        break;
    }

    stateMachineVariable++;
  }
}

bool getButtonPress() {
  if (!digitalRead(BUTTON_PIN)) { while(!digitalRead(BUTTON_PIN)) { doLEDFlicker(); } }
  while(digitalRead(BUTTON_PIN)) { doLEDFlicker(); }

  //We have pressed the button
  unsigned long prevMillis = millis();
  while(!digitalRead(BUTTON_PIN)) { doLEDFlicker(); }

  if (millis() - prevMillis < 800) { return false; }
  return true;
}

void doLEDFlicker() {
  if (StripIsOn) {
    if (random(0,RANDOM_FLICKER) == 1) {
      currentBrightness += random(-50,50);
      if (currentBrightness > MAX_BRIGHTNESS) { currentBrightness = MAX_BRIGHTNESS; }
      if (currentBrightness < MIN_BRIGHTNESS) { currentBrightness = MIN_BRIGHTNESS; }
      pixels.setBrightness(currentBrightness);
      pixels.show();
    }
  }
}

void turnOnStrip(int R, int G, int B) {
  StripIsOn = true;
  prevR = R;
  prevG = G;
  prevB = B;
  for(int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i,pixels.Color(R,G,B));
  }
}

void turnOffStrip(bool doAnim) {
  StripIsOn = false;

  if (doAnim && StripIsOn) {
    for(int i = NUMPIXELS/2; i >= 0; i--) {
      pixels.setPixelColor(i,pixels.Color(0,0,0));
      pixels.setPixelColor(NUMPIXELS - i,pixels.Color(0,0,0));
      delay(25);
    }
  }

  pixels.clear();
  pixels.show();
  delay(10);

  int LED_Brightness = 50;
  for (int i = 0; i < 3; i++) {
    pixels.setPixelColor(i, pixels.Color(LED_Brightness,LED_Brightness,LED_Brightness));
  }
  for (int i = NUMPIXELS; i > NUMPIXELS - 3; i--) {
    pixels.setPixelColor(i, pixels.Color(LED_Brightness,LED_Brightness,LED_Brightness));
  }
  pixels.show();
}