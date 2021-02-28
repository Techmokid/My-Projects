#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <PinToGPIO.h>
#include <EEPROM.h>

#define neopixels_pin     11
#define numberOfPixels    120

PinToGPIO p;
Adafruit_NeoPixel strip(numberOfPixels ,p.pinToGPIO(neopixels_pin), NEO_GRB + NEO_KHZ800);

//status = 0      Off
//status = 1      Single Colour
//status = 2      Colour Fading
int status = 0;

void setup() {
  setupWifi();
  strip.begin();
}

void loop() {
  handleWifiClient();
  
  if (status == 0) {
    //Do nothing
  } else if (status == 1) {
    updateSingleColour();
  } else if (status == 2) {
    updateFade();
  }
}
