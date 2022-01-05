/**
 @file oled.ino
 @brief This is an Example for the FaBo OLED I2C Brick.

   http://fabo.io/214.html

   Released under APACHE LICENSE, VERSION 2.0

   http://www.apache.org/licenses/

 @author FaBo<info@fabo.io>
*/

#include <Wire.h>
#include <FaBoOLED_EROLED096.h>

FaBoOLED_EROLED096 faboOled;

void setup() {
  Serial.begin(9600);
  Serial.println("RESET");
  Serial.println();

  faboOled.begin();

  faboOled.showBitmap();
  delay(1000);
  faboOled.clear();
  faboOled.print("Hello! FaBo");
}

void loop() {
  faboOled.setCursor(0, 1);
  faboOled.print(millis() / 1000);
}

