#include <Wire.h>  
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <stdio.h>
#include <ctype.h>

SoftwareSerial Bluetooth(5,6);
LiquidCrystal_I2C lcd(0x3F,20, 4);
char BT_input;
int n = 0;
char text;

void setup() {
  lcd.init();
  lcd.backlight(); // makes Backligh ON. 
  lcd.clear();     // Clears LCD
  lcd.home();      // Sets cursor at Column 0 and Line 0
  lcd.print("ROBO INDIA");  
  Bluetooth.begin(9600);
  Serial.begin(9600);
}


void loop() {
  if (Bluetooth.available()) {
    BT_input=(Bluetooth.read());
    
    if(BT_input == '9') {
      lcd.clear(); 
      lcd.home();
      lcd.print("ROBO INDIA");
      n=0;
    }
    
    if (isalpha(BT_input) != 0 || isdigit(BT_input) !=0 || BT_input == ' ') {
      text = BT_input;
      lcd.setCursor(n,1);
      lcd.print(text);
      Serial.write(text);
      
      if(n<15) {
        n++;
      } else {
        n = 0;
        lcd.clear();
        lcd.home();
        lcd.print("ROBO INDIA");
      }
    }
  }
}
