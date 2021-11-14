#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMPIXELS 120

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pixels.begin();

  delay(500);
  setColour(255,0,0);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void setColour(int R, int G, int B) {
  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(R,G,B)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(10); // Delay for a period of time (in milliseconds).

  }
}
