#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal_PCF8574.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>

// Pin for buttons
#define KEYPIN A0
// Button constants
#define btnRIGHT 6
#define btnUP 5
#define btnDOWN 4
#define btnLEFT 3
#define btnSELECT 2
#define btnNONE (-1)

// EEPROM addresses
#define YEAR_ADDR 0
#define MONTH_ADDR 1
#define DAY_ADDR 2

// Do the menus wrap around to the other side, or just stop at the ends
#define wrapAround

// RTC and LCD setup
RTC_DS1307 rtc;
LiquidCrystal_PCF8574 lcd(0x27);
DateTime now;
DateTime lastInjuryDate(2023, 1, 1, 0, 0, 0);

// Function declarations
void Update_Eink();
void Handle_LCD_Menu();
void enterDeepSleep();
void SaveLastInjuryDate(int day, int month, int year);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setBacklight(255);
  lcd.clear();
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    lcd.setCursor(1, 0);
    lcd.print("ERROR:  No RTC");
    lcd.setCursor(8, 1);
    lcd.blink();
    while (1) {
      lcd.setBacklight(0);
      delay(500);
      lcd.setBacklight(255);
      delay(500);
    }
  }

  EEPROM.begin(512); // Initialize EEPROM with size 512 bytes

  // Read year, month, and day from EEPROM
  int year = EEPROM.read(YEAR_ADDR) + 2000; // Assuming year is stored as offset from 2000
  int month = EEPROM.read(MONTH_ADDR);
  int day = EEPROM.read(DAY_ADDR);
  lastInjuryDate = DateTime(year, month, day, 0, 0, 0);

  // Deep sleep
  attachInterrupt(digitalPinToInterrupt(KEYPIN), Handle_LCD_Menu, CHANGE); // Attach interrupt to the button pin
  ESP.deepSleep(6 * 60 * 60 * 1000000); // Schedule wakeup every 6 hours (6*60*60 seconds) in terms of microseconds
}

void loop() {}

void Update_Eink() {
  now = rtc.now();
  TimeSpan diff = now - lastInjuryDate;

  // Print the difference to the Serial port
  Serial.print("Days: ");
  Serial.print(diff.days());
  Serial.print(" Hours: ");
  Serial.print(diff.hours());
  Serial.print(" Minutes: ");
  Serial.print(diff.minutes());
  Serial.print(" Seconds: ");
  Serial.println(diff.seconds());
}

void SaveLastInjuryDate(int day, int month, int year) {
  EEPROM.write(YEAR_ADDR, year - 2000); // Store year as offset from 2000
  EEPROM.write(MONTH_ADDR, month);
  EEPROM.write(DAY_ADDR, day);
  EEPROM.commit(); // Ensure data is written to EEPROM
}

int read_LCD_buttons() {
  int adc_key_in = 0;
  adc_key_in = analogRead(KEYPIN);           // read the value from the sensor
  delay(5);                                  //switch debounce delay. Increase this delay if incorrect switch selections are returned.
  int k = (analogRead(KEYPIN) - adc_key_in); //gives the button a slight range to allow for a little contact resistance noise
  if (5 < abs(k))
    return btnNONE; // double checks the keypress. If the two readings are not equal +/-k value after debounce delay, it tries again.
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000)
    return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  if (adc_key_in < 50)
    return btnRIGHT;
  if (adc_key_in < 195)
    return btnUP;
  if (adc_key_in < 380)
    return btnDOWN;
  if (adc_key_in < 555)
    return btnLEFT;
  if (adc_key_in < 790)
    return btnSELECT;
  return btnNONE; // when all others fail, return this...
}

int returnKeyPress() {
  int result = read_LCD_buttons();
  while ((result != btnNONE) && (read_LCD_buttons() == result)); // Wait for us to either change button pressed, or just let go of the current button. Stops spamming the ISR
  return result;
}

void Handle_LCD_Menu() {
  lcd.display();
  lcd.setBacklight(255);
  lcd.blink();

  // Here we handle the menu.
  now = rtc.now();
  int injuryDay = EEPROM.read(DAY_ADDR);
  int injuryMonth = EEPROM.read(MONTH_ADDR);
  int injuryYear = EEPROM.read(YEAR_ADDR) + 2000;
  int currentDay = now.day();
  int currentMonth = now.month();
  int currentYear = now.year();
  int currentHour = now.hour();
  int currentMinute = now.minute();

  int currentMenu = 0;  
  int currentCursorPosition = 0;
  int timeout = 1000 * 30; // After 30 seconds of no button pressing, sleep again
  unsigned long lastPressTime = millis();
  unsigned long blinkTimer = millis();
  while (millis() - lastPressTime < timeout) {
    int key = returnKeyPress();
    if (key != btnNONE) {
      lastPressTime = millis();

      // Here handle the keypress. Still to do




      // Here handle the LCD display
      // "01/01/2023 xx:xx" <- Perfect 16 characters wide if we use 24 hour time
      // "   01/01/2023   " <- Works well too
      if (currentMenu == 0) {
        lcd.setCursor(0, 0);
        lcd.print("Edit Current Day");
        lcd.setCursor(0, 1);
        lcd.print("Edit Last Injury");
        lcd.setCursor(0, currentMenu);
      } else if (currentMenu == 1) {
        // Save the datetime using:
        //
        // DateTime newDateTime(year, month, day, hour, minute, second); // Replace with your desired values
        // rtc.adjust(newDateTime);
        //

        lcd.setCursor(0, 0);
        lcd.print("Edit Current Day");
        lcd.setCursor(0, 1);

        String currentDatetime = String(currentDay / 10, DEC) + String(currentDay % 10, DEC) + "/";
        currentDatetime +=       String(currentMonth / 10, DEC) + String(currentMonth % 10, DEC) + "/";
        currentDatetime +=       currentYear;
        currentDatetime +=       String(currentHour / 10, DEC) + String(currentHour % 10, DEC) + ":";
        currentDatetime +=       String(currentMinute / 10, DEC) + String(currentMinute % 10, DEC);
        lcd.print(currentDatetime);

        #ifdef wrapAround
        if (currentCursorPosition > 15) {currentCursorPosition = 0;}
        if (currentCursorPosition < 0)  {currentCursorPosition = 15;}
        #else
        if (currentCursorPosition > 15) {currentCursorPosition = 15;}
        if (currentCursorPosition < 0)  {currentCursorPosition = 0;}
        #endif

        lcd.setCursor(currentCursorPosition, 1);
      } else {
        // Save the date using SaveLastInjuryDate(day, month, year);
        lcd.setCursor(0, 0);
        lcd.print("Edit Last Injury");
        lcd.setCursor(0, 1);

        String injuryDate = String(injuryDay / 10, DEC) + String(injuryDay % 10, DEC) + "/";
        injuryDate +=       String(injuryMonth / 10, DEC) + String(injuryMonth % 10, DEC) + "/";
        injuryDate +=       injuryYear;
        lcd.setCursor(3,1);
        lcd.print(injuryDate);

        #ifdef wrapAround
        if (currentCursorPosition > 7) {currentCursorPosition = 0;}
        if (currentCursorPosition < 0) {currentCursorPosition = 7;}
        #else
        if (currentCursorPosition > 7) {currentCursorPosition = 7;}
        if (currentCursorPosition < 0) {currentCursorPosition = 0;}
        #endif

        switch (currentCursorPosition) {
          case 0:
            lcd.setCursor(3,1);
          case 1:
            lcd.setCursor(4,1);
          case 2:
            lcd.setCursor(6,1);
          case 3:
            lcd.setCursor(7,1);
          case 4:
            lcd.setCursor(9,1);
          case 5:
            lcd.setCursor(10,1);
          case 6:
            lcd.setCursor(11,1);
          case 7:
            lcd.setCursor(12,1);
        }
      }
    }

    delay(10);
  }
  
  Update_Eink()
  lcd.noDisplay();
  lcd.setBacklight(0);
  ESP.deepSleep(6 * 60 * 60 * 1000000); // Reset deep sleep timer after handling menu
}

void enterDeepSleep() {
  ESP.deepSleep(6 * 60 * 60 * 1000000);
}
