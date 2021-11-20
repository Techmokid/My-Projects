#include <Adafruit_NeoPixel.h>

#define LED_PIN 6
#define COLOUR_BUTTON_PIN 7
#define POWER_BUTTON_PIN 8
#define NUMPIXELS 120

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(COLOUR_BUTTON_PIN,INPUT_PULLUP);
  pinMode(POWER_BUTTON_PIN,INPUT_PULLUP);
  
  // put your setup code here, to run once:
  pixels.begin();

  delay(500);
  pixels.setBrightness(250);
}

int currentColourR = 255;
int currentColourG = 255;
int currentColourB = 255;

void loop() {
  setColour(255,0,0); //Red
  waitForButton();
  
  setColour(255,15,0); //Orange
  waitForButton();
  
  setColour(255,255,0); //Yellow-Green
  waitForButton();
  
  setColour(255,180,0); //Yellow
  waitForButton();
  
  setColour(0,255,0); //Green
  waitForButton();
  
  setColour(0,0,255); //Blue
  waitForButton();
  
  setColour(0,50,255); //Cyan
  waitForButton();
  
  setColour(190*0.3,0,255*0.3); //Purple
  waitForButton();
}

void setColour(int R, int G, int B) {
  currentColourR = R;
  currentColourG = G;
  currentColourB = B;
  
  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(R,G,B)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    //delay(10); // Delay for a period of time (in milliseconds).

  }
}

bool StripIsOn = true;
void waitForButton() {
  //BUTTON_PIN
  StripIsOn = true;
  while(!digitalRead(COLOUR_BUTTON_PIN)) { }
  while(digitalRead(COLOUR_BUTTON_PIN)) {
    if (!digitalRead(POWER_BUTTON_PIN)) {
      if (StripIsOn) {
        pixels.clear();
        pixels.show();
      } else {
        setColour(currentColourR,currentColourG,currentColourB);
      }
      
      StripIsOn = !StripIsOn;
      while(!digitalRead(POWER_BUTTON_PIN)) {}
      delay(50);
    }
  }
}

