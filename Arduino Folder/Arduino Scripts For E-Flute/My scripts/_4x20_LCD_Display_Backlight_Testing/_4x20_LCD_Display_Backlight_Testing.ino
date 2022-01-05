#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,20,4);  // Set the LCD I2C address

void setup() {
  lcd.begin(20,4);
}

void loop() {
  lcd.backlight();
  delay(500);
  lcd.noBacklight();
  delay(500);
}
