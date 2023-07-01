#include <EEPROM.h>
#include <DMD2.h>
//#include <glcd.h>

//#include "fonts/SystemFont5x7.h";

#define scrollSpeed 100

//          Wide,High
SoftDMD dmd(2,   1);
String sentence = "Welcome     To     Jaycar     Midland!                                             ";
bool state = false;

void setup() {
  Serial.begin(115200);
  
  dmd.setBrightness(255);
  dmd.begin();
  
  start();
  
  state = bool(EEPROM.read(0));
  EEPROM.write(0,!state);
}

void loop() {
  //updateScrollingDisplay(SystemFont5x7);
}
