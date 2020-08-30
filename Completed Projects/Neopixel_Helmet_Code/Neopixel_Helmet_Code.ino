#include <Adafruit_NeoPixel.h>
#include <PinToGPIO.h>

//Alter these as needed
int neopixels_pin = 1;
int buttonInputs_pin = 2;
int maxNumberOfStates = 3;
int numberOfPixels = 5;

//Don't touch these
PinToGPIO p;
int state = 0;
Adafruit_NeoPixel strip(5, p.pinToGPIO(neopixels_pin), NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(64); // Value between 0 (min) and 255 (max)
}

void loop() {
  strip.clear();
  checkButton();

  //We loop over every pixel to set them all to the same value
  if (state == 0) {
    for(int x = 0; x < numberOfPixels; x++) {
      strip.setPixelColor(x, 150, 50, 0);   // Set To Orange
    }
  } else if (state == 1) {
    for(int x = 0; x < numberOfPixels; x++) {
      strip.setPixelColor(x, 20,  80, 150); // Set To Aqua/Cyan
    }
  } else if (state == 2) {
    for(int x = 0; x < numberOfPixels; x++) {
      strip.setPixelColor(x, 100, 0,  100); // Set To Purple
    }
  }
  
  strip.show();
  delay(1);
}

bool previousReading = false;
void checkButton() {
  bool currentReading = digitalRead(p.pinToGPIO(buttonInputs_pin));
  
  if ((!previousReading) && currentReading) {
    state++;
    if (state == maxNumberOfStates) { state = 0; }
    delay(200);
  }

  previousReading = currentReading;
}
