#include <Servo.h>

Servo myservo;

void setup() {
  myservo.attach(3);
  Serial.begin(9600);
}

void loop() {
  myservo.write(7);
  delay(400);
  myservo.write(180);
  delay(400);
}
