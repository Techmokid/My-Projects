//Which pin of the leonardo we want to use
#define neopixels_pin   11

//How many "Pixels" (Number of LEDs) are in the LED strip.
//Getting this value wrong isn't a big deal. For testing I think I just put "10" and that kinda worked.
#define numberOfPixels  120

//Here we include the library
#include <Adafruit_NeoPixel.h>

//This is just some weird setup that the library does.
Adafruit_NeoPixel strip(numberOfPixels, neopixels_pin, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(255); // Value between 0 (min) and 255 (max)
}

void loop() {
  // put your main code here, to run repeatedly:
  strip.clear();  //Turn off all pixels. Literally "clearing" the strip of light
  strip.show();
  delay(1000);
  
  setStripColor(100, 0, 100);
  strip.show();
  delay(1000);

  //while (true) {}
}

void setStripColor(int r, int g, int b) {
  for (int i = 0; i < numberOfPixels; i++) {
    strip.setPixelColor(i, r,  g, b);
  }
}
