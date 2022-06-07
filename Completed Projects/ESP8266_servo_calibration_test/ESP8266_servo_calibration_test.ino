#ifndef ESP8266
  #error This code is designed to run on ESP8266 platform! Please check your Tools->Board setting.
#endif

#define TIMER_INTERRUPT_DEBUG       1
#define ISR_SERVO_DEBUG             1

#include "ESP8266_ISR_Servo.h"

#define MIN_MICROS      700  //544
#define MAX_MICROS      2450

#define NUM_SERVOS    2

typedef struct
{
  int     servoIndex;
  uint8_t servoPin;
} ISR_servo_t;

ISR_servo_t ISR_servo[NUM_SERVOS] =
{
  { -1, 0 },
  { -1, 0 }
};

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println("Initializing");
  
  //serX.offset0Deg = 700;
  //serX.offset180Deg = 2400;
  //serY.offset0Deg = 600;
  //serY.offset180Deg = 2200;

  ISR_servo[0] = {-1, pinToGPIO(3)};
  ISR_servo[1] = {-1, pinToGPIO(4)};
  
  for (int index = 0; index < NUM_SERVOS; index++) {
    ISR_servo[index].servoIndex = ISR_Servo.setupServo(ISR_servo[index].servoPin, MIN_MICROS, MAX_MICROS);

    if (ISR_servo[index].servoIndex != -1) {
      Serial.print(F("Setup OK Servo index = ")); Serial.println(ISR_servo[index].servoIndex);
    } else {
      Serial.print(F("Setup Failed Servo index = ")); Serial.println(ISR_servo[index].servoIndex);
    }
  }
  Serial.println("Completed startup. Entering program loop");
}

void loop() {
  ISR_Servo.setPosition(ISR_servo[0].servoIndex, 0);
  delay(1000);
  ISR_Servo.setPosition(ISR_servo[0].servoIndex, 100);
  delay(1000);
  ISR_Servo.setPosition(ISR_servo[0].servoIndex, 190);
  delay(1000);
  ISR_Servo.setPosition(ISR_servo[0].servoIndex, 100);
  delay(3000);
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
