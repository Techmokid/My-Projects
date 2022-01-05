#define PWRKEY  6
#define RST     7
//#define DTR     8
//#define RI      9
#define TX      10
#define RX      11
#define ALRT    12

#include <SoftwareSerial.h>
SoftwareSerial SimComSS = SoftwareSerial(TX,RX);
bool firstBoot = true;
unsigned long prevTime = 0;

void startModem() {
  pinMode(PWRKEY,OUTPUT);
  digitalWrite(PWRKEY,HIGH);
  delay(200);
  digitalWrite(PWRKEY,LOW);
  
  if (firstBoot) {
    SimComSS.begin(9600);
    firstBoot = false;
  }
}

void restartModem() {
  pinMode(RST,OUTPUT);
  digitalWrite(RST,HIGH);
  delay(260);
  digitalWrite(RST,LOW);
  pinMode(RST,INPUT);
}

bool connectToInternet() {
  sendCommand("AT+SAPBR=1,1");

  String tempRes = waitForResponse(1000).response;
  return (tempRes.substring(0,5) != "ERROR");
}

void setToSMSMode() {
  sendCommand("AT+CMGF=1");
}

void createSerialLoop() {
  if (SimComSS.available()) { delay(50); while (SimComSS.available() > 0) { Serial.write(SimComSS.read()); } }
  if (Serial.available())   { delay(50); while (Serial.available() > 0)   { SimComSS.write(Serial.read()); } }
}

void sendCommand(String command) { SimComSS.print(command + "\r"); }

responseClass waitForResponse() { waitForResponse(30000); }
responseClass waitForResponse(unsigned long userTimeout) {
  responseClass result;
  
  unsigned long timeout = millis() + userTimeout;
  while(millis() < timeout) {
    if(SimComSS.available()) {
      delay(150);
      String cmd = "";
      String msg = "";
      bool firstHalf = true;
      while(SimComSS.available()) {
        if (firstHalf) {
          char i = SimComSS.read();
          if (i == '\n') {
            firstHalf = false;
          } else {
            cmd += i;
          }
        } else {
          msg += char(SimComSS.read());
        }
      }
      result.command = cmd;
      result.response = msg;
      return result;
    }
  }
  return result;
}

bool waitForModemReady() { return waitForModemReady(20000); }
bool waitForModemReady(int waitTime) {
  unsigned long prevTime = millis();
  while (prevTime + waitTime > millis()) {
    sendCommand("AT");
    String temp = waitForResponse(1000).response;
    if (temp.substring(0,temp.length()-2) == "OK") {
      return true;
    }
  }
  
  return false;
}

void updateATList() {
  while(SimComSS.available()) { char t = SimComSS.read(); }
}
