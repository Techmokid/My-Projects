#include <SoftwareSerial.h>

SoftwareSerial SerialCom(3,4);

void setup() {
  Serial.begin(9600);
  SerialCom.begin(4800);
  delay(200);
  
  pinMode(2,OUTPUT);
  pinMode(13,OUTPUT);

  digitalWrite(2,HIGH);
  digitalWrite(13,HIGH);
  delay(1000);
  
  SerialCom.write("S");
  delay(200);
}

void loop() {
  TransmitFlashTest();
}

void TransmitFlashTest() {
  SerialCom.write("1B0H");
  delay(200);
  SerialCom.write("1B0L");
  delay(200);
}

void ReceiveTest() {
  digitalWrite(13,LOW);
  SerialCom.write("1B0A");

  while (SerialCom.available() <= 0) {}
  digitalWrite(13,HIGH);
  Serial.println(SerialCom.read());
}
