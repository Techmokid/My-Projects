#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial Bluetooth(5,6);      // (TXD, RXD) of HC-05

int looper = 0;
char state = 0;
String currentBuffer = "";
float previous = 0;

void setup () {
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
  
  if (millis() > previous + 1000) {
    previous = millis();
    runFunction();
  }
}

void runFunction() {
  looper++;
  Bluetooth.print("Hello! " + String(looper) + "\n");
}

