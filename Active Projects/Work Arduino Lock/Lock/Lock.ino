#include <LiquidCrystal.h>
#include "MiFareWrapper.h"

#define LED_RED_PIN A0
#define LED_GRN_PIN A1
#define RELAY_UNLOCK_PIN A2
#define PASSCODE "Xq7!v2$Kd@9Rf^pL"

// RFID
const int ss = 10, rst = 9;
MiFareWrapper rfid(ss, rst);

const int rs = 6, en = 7, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

unsigned long prevMillis;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("-------------------------------");
  Serial.println();

  pinMode(LED_RED_PIN,OUTPUT);
  pinMode(LED_GRN_PIN,OUTPUT);
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_RED_PIN,HIGH);
    digitalWrite(LED_GRN_PIN,HIGH);
    delay(100);
    digitalWrite(LED_RED_PIN,LOW);
    digitalWrite(LED_GRN_PIN,LOW);
    delay(100);
  }

  lcd.begin(16, 2);

  // Initialize RFID
  if (!rfid.initialize()) {
    Serial.println(F("RFID failed to initialize :("));
    while (true) {
      lcd.setCursor(0, 0); lcd.print("STARTUP: FAILURE");
      lcd.setCursor(0, 1); lcd.print("RFID:  INIT FAIL");
      digitalWrite(LED_RED_PIN,HIGH);
      delay(250);
      digitalWrite(LED_RED_PIN,LOW);
      delay(250);
    }
  }

  Serial.println(F("RFID initialized successfully"));

  lcd.setCursor(0, 0); lcd.print("STARTUP: SUCCESS");
  lcd.setCursor(0, 1); lcd.print("RFID:    WORKING");
  delay(2000);

  lcd.clear();

  prevMillis = millis();
}

void loop() {
  // Reset the display periodically to HOPEFULLY avoid the LCD data corruption glitch
  if (millis() - prevMillis > 60000) {
    lcd.clear();
    lcd.setCursor(0, 0);
    prevMillis = millis();
  }

  // If no new card was detected, just cancel out
  if (!rfid.newCardDetected()) { delay(100); return; }

  // Try and avoid LCD data corruption glitch by clearing the LCD
  lcd.clear();
  lcd.setCursor(0, 0);

  Serial.println();
  Serial.println("-------------------------------");
  Serial.println();
  Serial.println("Detected Card");

  // Read key from our RFID card
  String dataRead = rfid.readFromCard().substring(0,16);
  dataRead.trim();
  if (dataRead == "") {
    lcd.setCursor(0, 0); lcd.print("ERROR: READ FAIL");
    lcd.setCursor(0, 1); lcd.print("   TRY  AGAIN   ");
    Serial.println(F("Failed to read data from the card"));
    for (int i = 0; i < 20; i++) {
      digitalWrite(LED_RED_PIN,HIGH); delay(200);
      digitalWrite(LED_RED_PIN,LOW);  delay(100);
    }

    lcd.clear();
    return;
  }
  //Serial.print(F("Data read from block: "));
  //Serial.println(dataRead);
  
  // Decide whether to allow the card or not
  if (dataRead == PASSCODE) {
    // Correct code
    Serial.println("Code is valid. Opening lock...");
    lcd.setCursor(0, 0); lcd.print("KEYCARD:ACCEPTED");
    lcd.setCursor(0, 1); lcd.print("TIMER:          ");

    digitalWrite(RELAY_UNLOCK_PIN,HIGH);
    for (int i = 5; i >= 0; i--) {
      lcd.setCursor(0, 1); lcd.print("TIMER:          ");
      lcd.setCursor(16 - String(i).length(), 1); lcd.print(i);

      digitalWrite(LED_GRN_PIN,HIGH); delay(1000);
      digitalWrite(LED_GRN_PIN,LOW);  delay(500);
    }
    digitalWrite(RELAY_UNLOCK_PIN,LOW);
    Serial.println("Relocking...");
    lcd.clear();
    lcd.setCursor(0, 0); lcd.print("     LOCKED     ");
    delay(2000);
  } else {
    // Incorrect code
    Serial.println("Code is invalid. Keep lock closed");
    lcd.setCursor(0, 0); lcd.print("    KEY-CARD    ");
    lcd.setCursor(0, 1); lcd.print("    REJECTED    ");

    for (int i = 0; i < 20; i++) {
      digitalWrite(LED_RED_PIN,HIGH); delay(200);
      digitalWrite(LED_RED_PIN,LOW);  delay(100);
    }
  }

  // Finally clear the display again
  delay(500);
  lcd.clear();
}