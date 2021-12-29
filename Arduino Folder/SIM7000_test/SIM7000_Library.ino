#define PWRKEY  6
#define RST     7
#define DTR     8
#define RI      9
#define TX      10
#define RX      11
#define ALRT    12

#include "Adafruit_FONA.h"
#include <SoftwareSerial.h>
SoftwareSerial SimComSS = SoftwareSerial(TX,RX);

//ADAFRUIT FONA THINGS-------------------------------------------------------------------------------
SoftwareSerial *SimComSerial = &SimComSS;
char replybuffer[255];
Adafruit_FONA_3G fona = Adafruit_FONA_3G(RST);
uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0);
uint8_t type;
//ADAFRUIT FONA THINGS-------------------------------------------------------------------------------

//This apparently opens up HTTP and gives the SIM7000 internet access?
//AT+SAPBR=1,1

//And then this gives you back your IP address?
//AT+SAPBR=2,1


void startModem() {
  pinMode(PWRKEY,INPUT);
  delay(2000);
  digitalWrite(PWRKEY,LOW);
  delay(2000);
  pinMode(PWRKEY,OUTPUT);
  digitalWrite(PWRKEY,HIGH);
  delay(500);
  digitalWrite(PWRKEY,LOW);
  delay(8000);
  
  SimComSerial->begin(9600);
  if (!fona.begin(*SimComSerial)) {
    Serial.println("Could not communicate with SIM7000 module");
  } else { isModemRunning = true; }
  fona.setNetworkSettings(F("telstra.iph"));
  fona.enableRTC(true);
}

void sendCommand(String command) {
  SimComSS.println(command);
}

String receiveCommand() {
  String msg = "";
  while(SimComSS.available()) {
    msg += char(SimComSS.read());
  }
  SimComSS.flush();
  return msg;
}
