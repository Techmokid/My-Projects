#include <LiquidCrystal.h>

//This is just a fancy way to declare pins like variables. I can explain this later if you would like!
#define rotary_A1_Pin 0
#define rotary_B1_Pin 1
#define rotary_A2_Pin 2
#define rotary_B2_Pin 3

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//Rotary encoder variables
unsigned long previousSensorTime_1 = millis();
unsigned long previousSensorTrigger_1 = 0;      //This is the magic number. This is the milliseconds elapsed between the last 2 triggers
unsigned long previousSensorTime_2 = millis();
unsigned long previousSensorTrigger_2 = 0;      //This is the magic number. This is the milliseconds elapsed between the last 2 triggers

//Display timing variables
unsigned long previousRefreshTime = 0;

//Sensor calibration variables (I don't know the sensor or your setup, so I'm just using your old code for this part)
float Tcal = 60000;             // number of pulses
float dia = 1.33;               // diameter of track
float divs = 40;                // number of segments on pickup ring
float Lcal = 0.5;               // Liters/min per pulse
float Tcal2 = 60000;            // number of pulses

//These variables you change as you please
int timeout = 3000;
int refresh = 250;

void setup() {
  lcd.begin(16,2);                                        //initialize LCD
  pinMode(rotary_A1_Pin,INPUT);
  pinMode(rotary_B1_Pin,INPUT);
  pinMode(rotary_A2_Pin,INPUT);
  pinMode(rotary_B2_Pin,INPUT);
  
  //By ignoring if it's falling or rising, we can get double the accuracy out of the rotary encoder
  attachInterrupt(digitalPinToInterrupt(rotary_A1_Pin),rotaryTrigger_1,CHANGE);
  attachInterrupt(digitalPinToInterrupt(rotary_B1_Pin),rotaryTrigger_1,CHANGE);
  attachInterrupt(digitalPinToInterrupt(rotary_A2_Pin),rotaryTrigger_2,CHANGE);
  attachInterrupt(digitalPinToInterrupt(rotary_B2_Pin),rotaryTrigger_2,CHANGE);
  
  lcd.setCursor(0,0);
  lcd.print("WA Stabilising");
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("Hybrid 6100   ");
  lcd.setCursor(0,1);
  lcd.print("v6.7");
  delay(2000);
}

void loop() {
  //Was the timeout tripped?
  if (millis() - previousSensorTime_1 > timeout) {
     previousSensorTrigger_1 = -1;
  }
  if (millis() - previousSensorTime_2 > timeout) {
     previousSensorTrigger_2 = -1;
  }

  //Refresh the screen
  if (millis() - previousRefreshTime > refresh) {
    previousRefreshTime = millis();
    
    //Calculate flow rate
    lcd.setCursor(0,0);
    if (previousSensorTrigger_2 == -1) {                                  //The sensor timed out
      lcd.print("    0");
    } else {                                                              //The sensor didn't time out, so we can actually calculate the required values!
      float flow = Tcal2 / previousSensorTrigger_2 * Lcal;
      lcd.print("    " + String(flow));
    }
    lcd.print("  L/min   ");

    //Calculate rpm
    lcd.setCursor(0,1);
    if (previousSensorTrigger_1 == -1) {                                  //The sensor timed out
      lcd.print("    0");
    } else {                                                              //The sensor didn't time out, so we can actually calculate the required values!
      //float meters = (Tcal / previousSensorTrigger) * (dia / divs);     // What it looks like you maybe meant?
      float meters = Tcal / previousSensorTrigger_1 * dia / divs;         // Your original formula
      
      lcd.print("    " + String(meters));
    }
    lcd.print("  M/min   ");
    lcd.print("   ");
  }
}

void rotaryTrigger_1() {
  previousSensorTrigger_1 = millis() - previousSensorTime_1;
  previousSensorTime_1 = millis();
}

void rotaryTrigger_2() {
  previousSensorTrigger_2 = millis() - previousSensorTime_2;
  previousSensorTime_2 = millis();
}
