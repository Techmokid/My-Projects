#include <servo.h>
#include <PinToGPIO.h>

servo serX;
servo serY;

PinToGPIO p;

void setup() {
  serX.startValOffset = 0;
  serX.endValOffset = 0;
  serY.startValOffset = 0;
  serY.endValOffset = 180000;

  serX.pin = p.pinToGPIO(4);
  serY.pin = p.pinToGPIO(3);

  serY.offset90 = true;
}

void loop() {
  serY.write(0); unsigned long temp = millis(); while (millis() - temp < 1000) { serY.updateServo(); } RunYield();
  serY.write(45); temp = millis(); while (millis() - temp < 1000) { serY.updateServo(); } RunYield();
  serY.write(90); temp = millis(); while (millis() - temp < 1000) { serY.updateServo(); } RunYield();
  serY.write(45); temp = millis(); while (millis() - temp < 1000) { serY.updateServo(); } RunYield();
}

void RunYield() {
  delay(0);
}

