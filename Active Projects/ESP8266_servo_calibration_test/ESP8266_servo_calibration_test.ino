#include <servo.h>
#include <PinToGPIO.h>

servo serX;
servo serY;

PinToGPIO p;

void setup() {
  Serial.begin(115200);
  
  serX.startValOffset = 0;
  serX.endValOffset = 1000;
  serY.startValOffset = 350;
  serY.endValOffset = -700;

  serX.pin = p.pinToGPIO(4);
  serY.pin = p.pinToGPIO(3);

  serY.offset90 = true;

  serX.write(90);
  serY.write(0);
}

//YS = 350
//YL = -700
void loop() {
  delay(0);
  serX.updateServo();
  
  delay(0);
  serY.updateServo();
  
  if (Serial.available()) {
    Serial.println("Receiving data from terminal...");
    String temp = Serial.readString();
    String servoAxis = temp.substring(0,2);
    int val = temp.substring(2).toInt();
    
    if ((servoAxis == "XS") || (servoAxis == "xs")) { serX.startValOffset = val;  Serial.println("Set servo X start to:" + String(val)); }
    if ((servoAxis == "XL") || (servoAxis == "xl")) { serX.endValOffset = val;    Serial.println("Set servo X finsh to:" + String(val)); }
    if ((servoAxis == "YS") || (servoAxis == "ys")) { serY.startValOffset = val;  Serial.println("Set servo Y start to:" + String(val)); }
    if ((servoAxis == "YL") || (servoAxis == "yl")) { serY.endValOffset = val;    Serial.println("Set servo Y finsh to:" + String(val)); }
    
    String secondTemp = temp.substring(0,4);
    int secondVal = temp.substring(4).toInt();
    if (secondTemp == "SETX") { serX.write(secondVal); Serial.println("Set servo X to:" + String(secondVal)); }
    if (secondTemp == "SETY") { serY.write(secondVal); Serial.println("Set servo Y to:" + String(secondVal)); }
  }
  
  //serY.write(0); unsigned long temp = millis(); while (millis() - temp < 1000) { serY.updateServo(); } RunYield();
  //serY.write(45); temp = millis(); while (millis() - temp < 1000) { serY.updateServo(); } RunYield();
  //serY.write(90); temp = millis(); while (millis() - temp < 1000) { serY.updateServo(); } RunYield();
  //serY.write(45); temp = millis(); while (millis() - temp < 1000) { serY.updateServo(); } RunYield();
}

