#include <SD.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SDComms false
#define ID1 2       //Function ID Pin A
#define ID2 3       //Function ID Pin B
#define ID3 4       //Function ID Pin C
#define In1 5       //Input Pin 1 For IR Sensor 1
#define In2 6       //Input Pin 2 For IR Sensor 2
#define prevPin 7   //Pin To See The Previous Measurement
#define distance 0.3 //Distance In Meters Between Sensors

LiquidCrystal_I2C lcd(0x3F,20,4);  // Set the LCD I2C address
File dataFile;

String scale1;
int scale2;
int progState;
float previousSpeed = 0;
float time_now = 0;
float time2;
float result = 0;

void setup() {
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  
  ReadScale();
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(20,4);
  lcd.backlight();
  
  if (SDComms) {
    dataFile = SD.open("datalog.txt", FILE_WRITE);
  }
  
  if ((digitalRead(In1)==LOW) and (digitalRead(In2)==HIGH)) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Train Speed Scaler");
    lcd.setCursor(0,2);
    lcd.print("Sensor 1 Not Found");
    while ((digitalRead(In1)==LOW) and (digitalRead(In2)==HIGH)) {}
    lcd.setCursor(0,2);
    lcd.print("Sensor 1 Was Found");
    delay(2000);
    setup();
  } else if ((digitalRead(In1)==HIGH) and (digitalRead(In2)==LOW)) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Train Speed Scaler");
    lcd.setCursor(0,2);
    lcd.print("Sensor 2 Not Found");
    while ((digitalRead(In1)==HIGH) and (digitalRead(In2)==LOW)) {}
    lcd.setCursor(0,2);
    lcd.print("Sensor 2 Was Found");
    delay(2000);
    setup();
  } else if ((digitalRead(In1)==LOW) and (digitalRead(In2)==LOW)) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Train Speed Scaler");
    lcd.setCursor(0,2);
    lcd.print("No Sensors Found");
    while ((digitalRead(In1)==LOW) and (digitalRead(In2)==LOW)) {}
    setup();
  }
}

void loop() {
  ReadScale();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Train Speed Scaler");
  lcd.setCursor(0,2);
  lcd.print("Chosen Scale: " + scale1);
  lcd.setCursor(0,3);
  lcd.print("Status: Idle");
  
  while(digitalRead(In1)==1 and digitalRead(In2)==1) {
    ReadScale();
    previous();
  }
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Train Speed Scaler");
  lcd.setCursor(0,2);
  lcd.print("Chosen Scale: " + scale1);
  lcd.setCursor(0,3);
  
  time_now = millis() / 1000;
  if (digitalRead(In1)==0) {
    lcd.print("Sensor 1 Triggered");
    while(digitalRead(In2)==1){
      previous();
    }
  } else {
    lcd.print("Sensor 2 Triggered");
    while(digitalRead(In1)==1){
      previous();
    }
  }
  
  float a = millis();
  result = a / 1000 - time_now;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Train Speed Scaler");
  lcd.setCursor(0,2);
  lcd.print("Calculating Speed...");
  
  //Still need to complete speed calculations!!!
  float RealVelocity = distance / result;
  float ScaledVelocityMS = RealVelocity * scale2 * 3.6;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Train Speed Scaler");
  lcd.setCursor(0,2);
  lcd.print("Calculated Speed:");
  lcd.setCursor(5,3);
  lcd.print(ScaledVelocityMS);
  previousSpeed = ScaledVelocityMS;
  digitalWrite(13,LOW);
  
  if (SDComms) {
    dataFile.println("Speed in Kph: " + String(ScaledVelocityMS) + "\tChosen Scale: " + String(scale1));
  }
  
  delay(3000);
}

void ReadScale() {
  bool A = digitalRead(ID1);
  bool B = digitalRead(ID2);
  bool C = digitalRead(ID3);
  if (A && B && !C) {
    scale1 = "Z-220";
    scale2 = 220;
  } else if (!A && B && !C) {
    scale1 = "N-144";
    scale2 = 144;
  } else if (A && !B && !C) {
    scale1 = "N-160";
    scale2 = 160;
  } else if (!A && !B && !C){
    scale1 = "HO-87";
    scale2 = 87;
  } else if (A && B && C){
    scale1 = "HO-72";
    scale2 = 72;
  } else if (!A && B && C){
    scale1 = "S-64";
    scale2 = 64;
  } else if (A && !B && C){
    scale1 = "O-48";
    scale2 = 48;
  } else {
    scale1 = "G-25";
    scale2 = 25;
  }
}

void previous() {
  Serial.println("ProgState: " + String(progState) + "\tDigitalRead(In1): " + String(digitalRead(In1)) + "\tDigitalRead(In2): " + String(digitalRead(In2)) + "\tPrevious Pin: " + String(digitalRead(prevPin)));
  if ((progState==0) and (digitalRead(prevPin)==1) and (millis()/1000 > time2 + 0.2)) {
    time2 = millis()/1000;
    progState = 1;
    lcd.setCursor(0,2);
    lcd.print("                    ");
    lcd.setCursor(0,2);
    lcd.print("Prior Speed: " + String(previousSpeed));
  } else if ((progState==1) and (digitalRead(prevPin)==0) and (millis()/1000 > time2 + 0.2)) {
    time2 = millis()/1000;
    progState = 0;
    lcd.setCursor(0,2);
    lcd.print("                    ");
    lcd.setCursor(0,2);
    lcd.print("Chosen Scale: " + scale1);
  }
}
