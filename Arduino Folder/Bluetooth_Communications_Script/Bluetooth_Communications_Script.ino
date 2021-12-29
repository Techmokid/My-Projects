#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial Bluetooth(5,6);      // (TXD, RXD) of HC-05

char state = 0;
String currentBuffer = "";

void setup() {
  Bluetooth.begin(9600);
  Serial.begin(9600);
}
 
void loop() {
  if(Bluetooth.available() > 0){
    state = Bluetooth.read();
    
    if (state != '\n') {
      currentBuffer += state;
    } else {
      Serial.println(currentBuffer);
      currentBuffer = "";
    }
  }
}
