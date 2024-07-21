#include <Adafruit_NeoPixel.h>

#define PIN 6 // Pin connected to the NeoPixels
#define NUM_LEDS 24 // Number of LEDs in your circle

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  static uint16_t startIndex = 0;
  rainbowCircle(startIndex);
  startIndex = (startIndex + 1) % 256; // Increment the startIndex for rotation
  delay(20); // Adjust delay for desired rotation speed
}

// Function to generate colors based on the wheel position
uint32_t wheel(byte pos) {
  pos = 255 - pos;
  if (pos < 85) {
    return strip.Color(255 - pos * 3, 0, pos * 3);
  } else if (pos < 170) {
    pos -= 85;
    return strip.Color(0, pos * 3, 255 - pos * 3);
  } else {
    pos -= 170;
    return strip.Color(pos * 3, 255 - pos * 3, 0);
  }
}

// Function to display a rainbow circle
void rainbowCircle(uint16_t startIndex) {
  for (int i = 0; i < NUM_LEDS; i++) {
    int colorIndex = (startIndex + (i * 256 / NUM_LEDS)) % 256;
    strip.setPixelColor(i, wheel(colorIndex));
  }
  strip.show();
}

