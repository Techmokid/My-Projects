#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,20,4);  // Set the LCD I2C address

float result = 0.00f;
bool three = false;
int looper = 0;
int scale = 0;
int scaler = 0;
String Unit[] = {"Z","N","TT","HO","S","O"};
String sentence;
float previous_result = 0.00f;

void menu() {
  lcd.clear();
  delay(1000);
  lcd.setCursor(1,0);
  lcd.print("Train Speed Scaler");
  lcd.setCursor(0,2);
  lcd.print("Please Select Scale:");
  lcd.setCursor(9,3);
  lcd.print(Unit[scale]);
  while (!digitalRead(5)) {
    if (digitalRead(4)) {
      if (scale < 5) {
        scale = scale + 1;
      }
      delay(500);
      menu();
    }
    if (digitalRead(6)) {
      if (scale > 0){
        scale = scale - 1;
      }
      delay(500);
      menu();
    }
  }
  lcd.clear();
}

void lcdSetup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(20,4);
  lcd.backlight();
}

void setup(){
  lcdSetup();
  menu();

  if (scale == 0) {
    scaler = 220;
  }
  if (scale == 1) {
    scaler = 160;
  }
  if (scale == 2) {
    scaler = 120;
  }
  if (scale == 3) {
    scaler = 87;
  }
  if (scale == 4) {
    scaler = 64;
  }
  if (scale == 5) {
    scaler = 45;
  }
  
  lcd.setCursor(0,0);
  lcd.print(" Train Speed Scaler");
  lcd.setCursor(0,2);
  lcd.print("-Recorded: N/A");
  lcd.setCursor(0,3);
  lcd.print("-Scaled: N/A");
  delay(2000);
  next_step();
}
  
void next_step() {
  while(true){
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("  Reading Sensors:");
    lcd.setCursor(0,3);
    lcd.print("Previous: " + String(previous_result) + "Km/H");
    while (looper < 500) {
      if (digitalRead(2) or digitalRead(3)) {
        if (digitalRead(3)) {
          three = true;
        }
        display_part_B();
      }
      delay(1);
      looper = looper + 1;
    }
    looper = 0;
    lcd.setCursor(9,2);
    lcd.print(".");
    while (looper < 500) {
      if (digitalRead(2) or digitalRead(3)) {
        if (digitalRead(3)) {
          three = true;
        }
        display_part_B();
      }
      delay(1);
      looper = looper + 1;
    }
    looper = 0;
    lcd.setCursor(10,2);
    lcd.print(".");
    while (looper < 500) {
      if (digitalRead(2) or digitalRead(3)) {
        if (digitalRead(3)) {
          three = true;
        }
        display_part_B();
      }
      delay(1);
      looper = looper + 1;
    }
    looper = 0;
    lcd.setCursor(11,2);
    lcd.print(".");
    while (looper < 500) {
      if (digitalRead(2) or digitalRead(3)) {
        if (digitalRead(3)) {
          three = true;
        }
        display_part_B();
      }
      delay(1);
      looper = looper + 1;
    }
    looper = 0;
  }
}

void display_part_B() {
  lcd.clear();
  delay(100);
  if (three) {
    lcd.setCursor(0,1);
    lcd.print("Sensor 2 Active");
    lcd.setCursor(0,2);
    lcd.print("Waiting for Sensor 1");
    lcd.setCursor(0,3);
    lcd.print("Previous: " + String(previous_result) + "Km/H");
    while (!digitalRead(2)) {
      delay(1);
      result = result + 1;
    }
    display_Part_C();
  } else {
    lcd.setCursor(0,1);
    lcd.print("Sensor 1 Active");
    lcd.setCursor(0,2);
    lcd.print("Waiting for Sensor 2");
    lcd.setCursor(0,3);
    lcd.print("Previous: " + String(previous_result) + "Km/H");
    while (!digitalRead(3)) {
      delay(1);
      result = result + 1;
    }
    display_Part_C();
  }
}

void display_Part_C() {
  result = 30 / (result / 1000);              //Convert to Seconds
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Train Speed Scaler");
  lcd.setCursor(0,2);
  sentence = "-Recorded: " + String(int(result)) + " cm/s";
  lcd.print(sentence);
  lcd.setCursor(0,3);
  result = result / 100 * scaler;        //Convert to Meters per Second
  result = result / 1000 * 60* 60;      //Convert to Kilometers per Hour
  sentence = "-Scaled: " + String(result) + "Km/H";
  lcd.print(sentence);
  previous_result = result;
  result = 0;
  while(!digitalRead(5)) {}
  next_step();
}

void loop() {}
