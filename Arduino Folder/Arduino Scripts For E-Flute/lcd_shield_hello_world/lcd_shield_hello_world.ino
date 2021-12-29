/*
  LiquidCrystal Library - Hello World
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
*/
 
// include the library code:
#include <LiquidCrystal.h>
 
// initialize the library with the numbers of the interface pins
// these numbers tell the Arduino which pins the LCD Shield uses
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(320, 240);
  // Print a message to the LCD.
  lcd.print("Mr. Muffin is...");
}
 
void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis()/1000);
}
