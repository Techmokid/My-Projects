#include<servo.h>
#include<PinToGPIO.h>

servo servo_1,servo_2;
int prevTimer_1,state_1,prevTimer_2,state_2 = 0;
PinToGPIO p;

void setup() {
  Serial.begin(74880);
  servo_1.pin = p.pinToGPIO(1); servo_1.write(45);
  servo_2.pin = p.pinToGPIO(2); servo_2.write(45);
}

void loop() {
  if (millis() - prevTimer_1 > 1020) {  prevTimer_1 = millis(); switch (state_1) {
      case 0: servo_1.write(0); state_1 = 1; Serial.println(0); break;
      case 1: servo_1.write(90); state_1 = 0; Serial.println(90); break;
      //case 2: servo_1.position(1700); state_1 = 3; break;
      //case 3: servo_1.position(1350); state_1 = 0; break;
  } }

  if (millis() - prevTimer_2 > 1000) { prevTimer_2 = millis(); switch (state_2) {
      case 0: servo_2.write(0); state_2 = 1; break;
      case 1: servo_2.write(90); state_2 = 0; break;
      //case 2: servo_2.position(1700); state_2 = 3; break;
      //case 3: servo_2.position(1350); state_2 = 0; break;
  } }
  
  servo_1.updateServo();
  servo_2.updateServo();
}
