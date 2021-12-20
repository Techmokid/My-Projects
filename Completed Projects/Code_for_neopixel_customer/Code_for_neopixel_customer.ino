#include<Adafruit_NeoPixel.h>

#define PIN 6
#define NUMPIXELS 60
#define CHANGE_SPEED 400
#define DELAY_TRAIL 20
#define BRIGHTNESS 100

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

float y[NUMPIXELS];

void setup() {
  Serial.begin(115200);
  pixels.begin();
  pixels.clear();
}

void loop() {
  float x = millis() / (float)CHANGE_SPEED;
  for (int i = 0; i < NUMPIXELS; i++) {
    int R = 127 + 128 * sin((float)x +          (float)i/(float)DELAY_TRAIL);
    int G = 127 + 128 * sin((float)x + 2*PI/3 + (float)i/(float)DELAY_TRAIL);
    int B = 127 + 128 * sin((float)x + 4*PI/3 + (float)i/(float)DELAY_TRAIL);
    
    R = R * BRIGHTNESS / 255;
    G = G * BRIGHTNESS / 255;
    B = B * BRIGHTNESS / 255;
    
    pixels.setPixelColor(i,pixels.Color(R,G,B));
    pixels.show();
  }
}
