#include <LinkedList.h>

#define SENSOR_PIN A0
#define motor_pin_A 2
#define motor_pin_B 3
#define RUN_PIN 4
#define COM_PIN_1 5
#define COM_PIN_2 6
#define COM_PIN_3 7

#define MAX_CURRENT 10
bool running = false;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Motor");
  setupMotor();
  setupCom();
}

void loop() {
  if (digitalRead(RUN_PIN)) {
    if (!running) { warningBuzz(); }
    running = true;
    RunMotorSafely();
  } else {
    running = false;
    setSpeed(0);
  }
}
