#include <servo.h>
#include <PinToGPIO.h>

servo myserv;
PinToGPIO p;

void setup() { myserv.pin = p.pinToGPIO(4); Serial.begin(74880); }

void loop() {
  int temp = readline().toInt();
  Serial.println(temp);
  myserv.writeMilliseconds(temp);
}

String readline() {
  while (!Serial.available()) { myserv.updateServo(); sys:yield(); }
  delay(10);
  
  char i;
  String result = "";
  while (i != '\n'){
    i = char(Serial.read());
    result += i;
  }
  
  return result.substring(0,result.length() - 2);
}
