#define neopixels_pin     11
#define buttonInputs_pin  10
#define numberOfPixels    120
#define maxNumberOfStates 3

#include <Adafruit_NeoPixel.h>

//Don't touch these
int currentState = 0;
bool triggered = true;
Adafruit_NeoPixel strip(numberOfPixels, neopixels_pin, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(64); // Value between 0 (min) and 255 (max)
}

void loop() {
  //See if we have hit the button
  checkButton();

  //Only update the light strip if the user has hit the button
  if (triggered) {
    triggered = false;
    strip.clear();
    
    //We loop over every pixel to set them all to the same value
    for(int x = 0; x < numberOfPixels; x++) {
      if (currentState == 0) {
        strip.setPixelColor(x, 150, 50, 0);   // Set To Orange
      } else if (currentState == 1) {
        strip.setPixelColor(x, 20,  80, 150); // Set To Aqua/Cyan
      } else if (currentState == 2) {
        strip.setPixelColor(x, 100, 0,  100); // Set To Purple
      }
    }
    
    strip.show();
    delay(1);
  }
}

//This is just fancy code for "Only change the state when you press the button" instead of "Change the state if the button is pressed, EVERY SINGLE CODE LOOP (Causes insanely quick colour flickering)"
bool previousReading = false;
void checkButton() {
  bool currentReading = digitalRead(buttonInputs_pin);
  
  if ((!previousReading) && currentReading) {
    triggered = true;
    currentState++;
    
    //If we hit the button and it was at the last state we want it in, just return to the first state to loop it over.
    if (currentState == maxNumberOfStates) { currentState = 0; }
  }

  previousReading = currentReading;
}
