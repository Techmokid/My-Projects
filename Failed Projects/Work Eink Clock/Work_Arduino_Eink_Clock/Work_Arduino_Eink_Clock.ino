#include <GxEPD2_BW.h>                   // EInk libraries
#include <GxEPD2_3C.h>                   //     |
#include <Fonts/FreeMonoBold9pt7b.h>     //     ↓

#include <Wire.h>                        // RTC Libraries
#include "RTClib.h"                      //     ↓

#include <ESP8266WiFi.h>                 // Memory/Sleep Libraries
#include <EEPROM.h>                      //     ↓

#define BUTTON_LEFT      1   // User Interface Pins
#define BUTTON_RIGHT     2   //     |
#define BUTTON_SELECT    3   //     |
#define BUTTON_UP        4   //     |
#define BUTTON_DOWN      5   //     ↓

#define CLK_PIN          13  // Auto-defined SPI pin
#define DIN_PIN          11  // Auto-defined SPI pin
#define CS_PIN           10  // EInk Pins
#define DC_PIN           9   //     |
#define RST_PIN          8   //     |
#define BUSY_PIN         7   //     ↓

#define YEAR_ADDR        0   // EEPROM addresses
#define MONTH_ADDR       1
#define DAY_ADDR         2
#define wrapAround           // Do the menus wrap around to the other side, or just stop at the ends

// Initialize the display class for a specific e-ink display model
GxEPD2_3C<GxEPD2_154c, GxEPD2_154c::HEIGHT> display(GxEPD2_154c(CS_PIN, DC_PIN, RST_PIN, BUSY_PIN));

int displayWidth;
int displayHeight;
DateTime lastInjuryDate;
DateTime now;
RTC_DS1307 rtc;
bool interrupted = false;

// Function declarations
void Update_Eink();
void Handle_LCD_Menu();
void enterDeepSleep();
void SaveLastInjuryDate(int day, int month, int year);

void setup() {
  // Initialize SPI and the display
  display.init();
  display.setRotation(1);

  // Clear the screen
  clearScreen();
  display.setFont(&FreeMonoBold9pt7b);
  
  int displayWidth = display.width();
  int displayHeight = display.height();

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    display.setCursor(displayWidth/4, displayHeight/4);
    display.print("ERROR:  No RTC Module Detected");
    display.update();
    delay(2000);

    while (!rtc.begin()) {
      display.setCursor(displayWidth/2, 3*displayHeight/4);
      display.print("!!!");
      display.update();
      delay(2000);
      display.setCursor(displayWidth/2, 3*displayHeight/4);
      display.print("   ");
      display.update();
      delay(2000);
    }
  }
  
  EEPROM.begin(512); // Initialize EEPROM with size 512 bytes

  // Read year, month, and day from EEPROM
  int year = EEPROM.read(YEAR_ADDR) + 2000; // Assuming year is stored as offset from 2000
  int month = EEPROM.read(MONTH_ADDR);
  int day = EEPROM.read(DAY_ADDR);
  lastInjuryDate = DateTime(year, month, day, 0, 0, 0);

  // Deep sleep
  attachInterrupt(digitalPinToInterrupt(BUTTON_LEFT), Handle_LCD_Menu, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_RIGHT), Handle_LCD_Menu, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_SELECT), Handle_LCD_Menu, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_UP), Handle_LCD_Menu, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_DOWN), Handle_LCD_Menu, CHANGE);
  ESP.deepSleep(6 * 60 * 60 * 1000000); // Schedule wakeup every 6 hours (6*60*60 seconds) in terms of microseconds
}

void loop() { }








// E-ink functions
void clearScreen() {
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
  } while (display.nextPage());
}
void writeText(int x, int y, const char* text, uint16_t color) {
  display.setFullWindow();
  display.firstPage();
  do {
    display.setCursor(x, y);
    display.setTextColor(color);
    display.setFont(&FreeMonoBold9pt7b);
    display.print(text);
  } while (display.nextPage());
}








void Update_Eink() {
  now = rtc.now();
  TimeSpan diff = now - lastInjuryDate;

  // Print the difference to the Serial port
  display.setCursor(30, 50);
  display.print("Days Since Last Injury");
  display.setCursor(50, 100);
  display.print(diff.days());
  display.update();
}

void SaveLastInjuryDate(int day, int month, int year) {
  EEPROM.write(YEAR_ADDR, year - 2000); // Store year as offset from 2000
  EEPROM.write(MONTH_ADDR, month);
  EEPROM.write(DAY_ADDR, day);
  EEPROM.commit(); // Ensure data is written to EEPROM
}

char returnKeyPress() {
  if (digitalRead(BUTTON_LEFT)) {
    while (digitalRead(BUTTON_LEFT));
    return 'L';
  }

  if (digitalRead(BUTTON_RIGHT)) {
    while (digitalRead(BUTTON_RIGHT));
    return 'R';
  }

  if (digitalRead(BUTTON_SELECT)) {
    while (digitalRead(BUTTON_SELECT));
    return 'S';
  }

  if (digitalRead(BUTTON_UP)) {
    while (digitalRead(BUTTON_UP));
    return 'U';
  }

  if (digitalRead(BUTTON_DOWN)) {
    while (digitalRead(BUTTON_DOWN));
    return 'D';
  }

  return 0;
}

void Handle_LCD_Menu() {
  if (interrupted) //Stops multiple ISR's being called while processing the LCD menu
    return;
  interrupted = true;

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
    char key = returnKeyPress();
    if (key != 0) { lastPressTime = millis(); }

    // Here handle the keypresses and menu system. Still to do

    delay(10);
  }
  
  Update_Eink();
  interrupted = false;
  ESP.deepSleep(6 * 60 * 60 * 1000000); // Reset deep sleep timer after handling menu
}

void enterDeepSleep() {
  ESP.deepSleep(6 * 60 * 60 * 1000000);
}