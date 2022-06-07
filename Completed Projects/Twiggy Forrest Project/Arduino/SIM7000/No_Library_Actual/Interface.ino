#include <SoftwareSerial.h>

#define PWRKEY  6
#define RST     7
//#define DTR     8
//#define RI      9
#define TX      10
#define RX      11
#define ALRT    12

String modemName;
String modemID;

SoftwareSerial ss(TX,RX);
LinkedList<String> ServerResponses = LinkedList<String>();

String incompleteSSResponse = "";

void printModemResponses() {
  for(int i = 0; i < ServerResponses.size(); i++) {
    Serial.println(ServerResponses[i]);
  }
}

void sendCommand (String command) { ss.print(command + "\r"); delay(10); }
void startSerial() { ss.begin(9600); Serial.begin(9600); Serial.println(); }
void serialLoop() {
  while (Serial.available()){
    ss.write(Serial.read());
    delay(5);
  }
  while (ss.available()){
    Serial.write(ss.read());
  }
}

void updateServerResponses() {
  while (ss.available()) {
    char i = ss.read();
    if (i == '\n') {
      //Serial.println(incompleteSSResponse);
      ServerResponses.add(incompleteSSResponse);
      incompleteSSResponse = "";
    } else if (((i > 31) && (i < 128)) || (i == '\r')) {
      incompleteSSResponse += i;
    }
  }

  //Now trim the input data of blank responses
  for(int i = 0; i < ServerResponses.size(); i++) {
    if (ServerResponses[i] == "") {
      ServerResponses.remove(i);
      i--;
    }
  }
}

void clearCacheMemory() {
  ss.flush();
  ServerResponses.clear();
}

int waitForResponse(double timer) {
  unsigned long prevTimer = millis();
  while(millis() - prevTimer < timer) {
    updateServerResponses();
    for(int i = 0; i < ServerResponses.size(); i++) {
      if ((ServerResponses[i].indexOf("OK") > -1) ||
          (ServerResponses[i].indexOf("DATA ACCEPT:") > -1) ||
          (ServerResponses[i].indexOf("+CPIN: READY") > -1))
        return 0;
      if (ServerResponses[i].indexOf("+CME ERROR: operation not allowed") > -1)
        return 1;
      if (ServerResponses[i].indexOf("ERROR") > -1)
        return 2;
    }
  }
  
  return -1;
}

int sendCommandAndWaitForResponse(String command, int waitTimer) {
  sendCommand(command);
  int i = waitForResponse(waitTimer);
  while(i != 0) { sendCommand(command); i = waitForResponse(waitTimer); }
}

void startModem() {
  clearCacheMemory();

  //Is the modem awake?
  printInterface1("1 /10 - Checking modem response");
  printInterfaceHandler(sendCommandAndWaitForResponse("AT",1000));
  clearCacheMemory();
  
  printInterface1("2 /10 - Checking modem response");
  printInterfaceHandler(sendCommandAndWaitForResponse("ATE0",1000));
  clearCacheMemory();

  //If we made it to here, the modem is responding
  printInterface1("3 /10 - Resetting Modem");
  printInterfaceHandler(sendCommandAndWaitForResponse("AT+CFUN=0",1000));
  clearCacheMemory();

  printInterface1("4 /10 - Configuring CFUN");
  printInterfaceHandler(sendCommandAndWaitForResponse("AT+CFUN=1,1",1000));
  clearCacheMemory();

  printInterface1("5 /10 - Configuring CMEE");
  printInterfaceHandler(sendCommandAndWaitForResponse("AT+CMEE=2",1000));
  clearCacheMemory();

  //Check the SIM status
  printInterface1("10/10 - Checking SIM");
  printInterfaceHandler(sendCommandAndWaitForResponse("AT+CPIN?",1000));

  unsigned long prevMillis = millis();
  bool isRunning = true;
  while(isRunning) {
    if (millis() - prevMillis > 5000) { isRunning = false; }
    updateServerResponses();
    for(int i = 0; i < ServerResponses.size(); i++) {
      if (ServerResponses[i].indexOf("PSUTTZ") >= 0) {
        //Serial.println("Date and Time: " + ServerResponses[i]);
        isRunning = false;
        break;
      }
    }
  }
  delay(1000);
  updateServerResponses();
  clearCacheMemory();
}

int responseTargetLength = 45;
int stringLen = 0;
void printInterface1(String x) {
  Serial.print("[SIM7000G INTERFACE]: " + x);
  stringLen = x.length();
}
void printInterface2(String x) {
  for(int i = 0; i < responseTargetLength - stringLen; i++) { Serial.print("."); }
  Serial.println(x);
}

void printInterfaceHandler(int x) {
  if (x == 0) {
    printInterface2("Pass");
  } else { printInterface2("Fail"); }
}

String getServerResponse(String serverAddress, String port, String headers[], int headerCount) {
  //https://electronics.stackexchange.com/questions/231224/posting-to-php-server-using-sim900-gprs-with-at-commands
  //http://www.raviyp.com/sim900-gprs-http-at-commands/
  printInterface1("Closing any pre-existing connections");
  printInterfaceHandler(sendCommandAndWaitForResponse("AT+CIPSHUT",1000));
  clearCacheMemory();

  printInterface1("Attaching to new GPRS service");
  printInterfaceHandler(sendCommandAndWaitForResponse("AT+CGATT=1",1000));
  clearCacheMemory();

  printInterface1("1/1 - Setting SAPBR IP settings");
  printInterfaceHandler(sendCommandAndWaitForResponse("AT+SAPBR=3,1,\"Contype\",\"GPRS\"",1000));
  clearCacheMemory();

  printInterface1("2/2 - Setting SAPBR IP settings");
  printInterfaceHandler(sendCommandAndWaitForResponse("AT+SAPBR=3,1,\"APN\",\"telstra.wap\"",1000));
  clearCacheMemory();

  printInterface1("3/3 - Setting SAPBR IP settings");
  printInterfaceHandler(sendCommandAndWaitForResponse("AT+SAPBR=1,1",1000));
  clearCacheMemory();
  
  printInterface1("4/4 - Setting SAPBR IP settings");
  printInterfaceHandler(sendCommandAndWaitForResponse("AT+SAPBR=2,1",1000));
  // HANDLE RESPONSE OF IP ADDRESS
  clearCacheMemory();

  printInterface1("Starting HTTP connection");
  printInterfaceHandler(sendCommandAndWaitForResponse("AT+HTTPINIT",1000));
  clearCacheMemory();
  
  printInterface1("Starting HTTP connection");
  printInterfaceHandler(sendCommandAndWaitForResponse("AT+HTTPPARA=\"CID\",1",1000));
  clearCacheMemory();

  printInterface1("Starting HTTP connection");
  printInterfaceHandler(sendCommandAndWaitForResponse("AT+HTTPPARA=\"URL\",\"" + serverAddress + "\"",1000));
  clearCacheMemory();

  printInterface1("Starting HTTP connection");
  printInterfaceHandler(sendCommandAndWaitForResponse("AT+HTTPPARA=\"CONTENT\",\"application/x-www-form-urlencoded\"",1000));
  clearCacheMemory();
  
  printInterface1("Starting HTTP connection");
  String sentence = "";
  sendCommand("AT+HTTPDATA=" + String(sentence.length()) + ",10000"); delay(100);
  sendCommand(sentence);
  clearCacheMemory();

  sendCommand("AT+HTTPACTION=0");   //0 is read, 1 is post, 2 is head
  sendCommand("AT+HTTPREAD");

  //Now close the connection
  sendCommand("AT+HTTPTERM");
  sendCommand("AT+SAPBR=0,1");
}
