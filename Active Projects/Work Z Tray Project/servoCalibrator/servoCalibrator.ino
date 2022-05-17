#define verServPin 3
#define horServPin 4

#define TIMER_INTERRUPT_DEBUG 1
#define ISR_SERVO_DEBUG 1
#include "ESP8266_ISR_Servo.h"
#include <EEPROM.h>
#define MIN_MICROS 700
#define MAX_MICROS 2450

struct servo {
  float offset0Deg = 1000;
  float offset180Deg = 2000;
  bool offset90 = false;
  bool oneTimeActive = false;
  int servoIndex = -1;
  int pin = 0;

  unsigned long previousTrigTimer = 0;
  bool onHalfOfSignal = false;
  int onTime = 1500;

  void setPin(int pin) {
    servoIndex = ISR_Servo.setupServo(pin, MIN_MICROS, MAX_MICROS);
  }

  float radToDeg(float x) {
    return map(x,0,3.14159265358979323846264338,0,180);
  }
  
  //void writeMicroseconds(int x) {  }
  void write(int x) {
    //ISR_Servo.setPosition(servoIndex, 10 + x);
    ISR_Servo.setPosition(servoIndex, map(0,180,offset0Deg,offset180Deg,x + 90*offset90));
  }

  float clamp(float x, float a, float b) {
    if (a==b) {return a;}
    if (a>b) { return min(a,max(b,x)); }
    return min(b,max(a,x));
  }
  
  void updateServo() { return; }

  float map(float startIn, float startOut, float endIn, float endOut, float val) {
    val -= startIn;               // Starting values are just offsets
    val /= startOut - startIn;    // Now get the percentage between the two points that val is
    val *= (endOut - endIn);      // Extrapolate that percentage onto the new bounding parameters
    return val + endIn;           // Return the result, adding on the starting offset value
    // return ((val - startIn) / (startOut - startIn)) * (endOut - endIn) + endIn;
  }
};

servo serX,serY;

void setup() {
  serX.setPin(pinToGPIO(horServPin)); serX.write(90);
  serY.setPin(pinToGPIO(verServPin)); serY.offset90 = true; serY.write(0);
}

void loop() {
  serX.write(90);  serY.write(0);   delayCheck(3000);
  serX.write(0);   serY.write(0);   delayCheck(3000);
  serX.write(90);  serY.write(0);   delayCheck(3000);
  serX.write(180); serY.write(0);   delayCheck(3000);
  serX.write(90);  serY.write(0);   delayCheck(3000);
  serX.write(90);  serY.write(-90); delayCheck(3000);
  serX.write(90);  serY.write(0);   delayCheck(3000);
  serX.write(90);  serY.write(90);  delayCheck(3000);
  serX.write(90);  serY.write(0);   delayCheck(3000);
}

void writeValueToEEPROM(int addr,float val) {
  EEPROM.begin(512);
  EEPROM.put(sizeof(float)*addr,val);
  EEPROM.end();
}

void delayCheck(int delayTimer) {
  unsigned long prevTime = millis();
  while(millis() - prevTime < delayTimer) {
    if (Serial.available()) {
      char i = Serial.read();
      String msg = "";
      while(i != '\n') {
        msg += i;
        i = Serial.read();
      }

      //We have the completed message from the serial terminal
      if (msg.substring(0,6) == "STARTX") {
        serX.offset0Deg = msg.substring(6).toFloat();
      } else if (msg.substring(0,6) == "STARTY"){
        serY.offset0Deg = msg.substring(6).toFloat();
      } else if (msg.substring(0,4) == "ENDX"){
        serX.offset180Deg = msg.substring(4).toFloat();
      } else if (msg.substring(0,4) == "ENDY"){
        serY.offset180Deg = msg.substring(4).toFloat();
      } else if (msg.substring(0,5) == "WRITE"){
        writeValueToEEPROM(11,serX.offset0Deg);
        writeValueToEEPROM(12,serX.offset180Deg);
        writeValueToEEPROM(13,serY.offset0Deg);
        writeValueToEEPROM(14,serY.offset180Deg);
      }
    }
  }
}

int pinToGPIO(int x) {
  if (x == 0) {return 16;}
  if (x == 1) {return 5;}
  if (x == 2) {return 4;}
  if (x == 3) {return 0;}
  if (x == 4) {return 2;}
  if (x == 5) {return 14;}
  if (x == 6) {return 12;}
  if (x == 7) {return 13;}
  if (x == 8) {return 15;}
  return -1;
}
