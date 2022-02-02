#include<LinkedList.h>
#include<EEPROM.h>;

#define PWRKEY  6
#define RST     7
//#define DTR     8
//#define RI      9
#define TX      10
#define RX      11
#define ALRT    12

#define RUN_PIN 54
#define COM_PIN_1 53
#define COM_PIN_2 52
#define COM_PIN_3 51

//#define resetIDOnBoot

char server[] = "techmo.unity.chickenkiller.com";
//char server[] = "163.47.56.221";
int port = 80;
int ID = 0;

String serverResponse = "";
void setup() {
  Serial.begin(115200);
  
  pinMode(RUN_PIN,OUTPUT);
  pinMode(COM_PIN_1,INPUT_PULLUP);
  pinMode(COM_PIN_2,INPUT_PULLUP);
  pinMode(COM_PIN_3,INPUT_PULLUP);

#ifdef resetIDOnBoot
  Serial.println("[Arduino User Code]: Clearing ID from memory");
  writeEepromInt(0,-1);
#endif

  ID = readEepromInt(0);
  Serial.println("[Arduino User Code]: Current ID: " + String(ID));
  Serial.println(F("[Arduino User Code]: Starting Modem..."));
  
  setupModem();
  Serial.println(F("[Arduino User Code]: Modem Started!"));
  
  if (ID == -1) {
    Serial.println(F("[Arduino User Code]: Getting new ID from server"));
    //The ID hasn't been set
    getServerResponse(server, port, new String {"Newid:1"}, 1);
    String tmp = serverResponse;
    if (tmp == "") { Serial.println("[Arduino User Code]: Error getting response from server for ID"); while(true) {}}
    int strippedResp = tmp.substring(tmp.indexOf(":")+1,tmp.indexOf("}")).toInt();
    writeEepromInt(0,strippedResp);
    ID = strippedResp;
    
    Serial.println("[Arduino User Code]: Assigned ID by server: " + String(ID));
    Serial.println("[Arduino User Code]: Now configuring Variables:");
    serverSetVariable("GPSLastLat","0");  serverResponse = ""; Serial.println(" - 1/6: GPS Current Latitude");
    serverSetVariable("GPSLastLong","0"); serverResponse = ""; Serial.println(" - 2/6: GPS Current Longitude");
    serverSetVariable("GPSLastTime","0"); serverResponse = ""; Serial.println(" - 3/6: GPS Current Time");
    
    serverSetVariable("Temp","0");        serverResponse = ""; Serial.println(" - 4/6: Current Temperature");
    serverSetVariable("Status","Offline");serverResponse = ""; Serial.println(" - 5/6: Current Status");
    serverSetVariable("RunMode","STP");   serverResponse = ""; Serial.println(" - 6/6: Default Runmode to Stop");
    Serial.println("[Arduino User Code]: Finished configuring variables");
  }
  
  Serial.println("[Arduino User Code]: Started successfully with assigned ID: " + String(ID));
  while(1);
}

void writeEepromInt(int address, int number) { 
  EEPROM.write(address, number >> 8);
  EEPROM.write(address + 1, number & 0xFF);
}

int readEepromInt(int address) {
  return (EEPROM.read(address) << 8) + EEPROM.read(address + 1);
}

void loop() {
  String temp[] = {"Getinfoonid:" + (String)ID};
  getServerResponse(server, port, temp, 1);
  //String response = "<body>{ID:1,GPSLastLat:0.00,GPSLastLong:0.00,GPSLastTime:\"AWST_20:11:41_29/11/21\",Temp:23,Status:\"Online\",RunMode:\"RLS\"}</body>";
  
  checkMotorStatus();
  switch(GetRunmodeFromString()) {
    case 0:
      //We got the all clear to go
      digitalWrite(RUN_PIN,HIGH);
    case 1:
      //We got a stop code
      digitalWrite(RUN_PIN,LOW);
    case 2:
      //We did not get a code returned
      Serial.println(F("[Arduino User Code]: There was no detected RUNMODE variable in server memory. Defaulting to stop mode"));
      //{
      //  "ID":"1",
      //  "GPSLastLat":"0",
      //  "GPSLastLong":"1.0",
      //  "GPSLastTime":"AWST_20:11:41_29/11/21",
      //  "Temp":"23",
      //  "Status":"Online",
      //  "RunMode":"RUN"
      //}
      serverSetVariable("GPSLastLat","0");  serverResponse = "";
      serverSetVariable("GPSLastLong","0"); serverResponse = "";
      serverSetVariable("GPSLastTime","0"); serverResponse = "";
      serverSetVariable("Temp","0");        serverResponse = "";
      serverSetVariable("Status","0");      serverResponse = "";
      serverSetVariable("RunMode","STP");   serverResponse = "";
      delay(1000*60);
  }
}

LinkedList<String> splitString(String str, char delimiter) {
  LinkedList<String> result = LinkedList<String>();
  String currentSentence = "";
  for(int i = 0; i < str.length(); i++) {
    if (str[i] != delimiter) {
      currentSentence += str[i];
    } else {
      result.add(currentSentence);
      currentSentence = "";
    }
  }
  result.add(currentSentence);
  return result;
}

int GetRunmodeFromString() {
  //if (serverResponse.length() == 0) { restartArduino(); }
  Serial.println("[Arduino User Code INTERNAL]: IN: " + serverResponse);
  //serverResponse = serverResponse.substring(serverResponse.indexOf("<body>"),serverResponse.indexOf("</body>"));
  //serverResponse.replace("<br/>","\n");
  //serverResponse.replace("<body>","");
  
  //Here is where we would substring the incoming data
  int strStart = serverResponse.indexOf("{");
  int strEnd = serverResponse.lastIndexOf("}");
  int operationMode = -1;
  if ((strStart != -1) && (strEnd != -1)) {
    String tempStr = serverResponse.substring(strStart + 1,strEnd);
    Serial.println(tempStr);
    
    LinkedList<String> splitStr = splitString(tempStr,',');
    for (int i = 0; i < splitStr.size(); i++) {
      //splitStr[i]
      if (splitStr[i].substring(0,8) == "RunMode:") {
        if (splitStr[i].substring(9,12) == "RUN") {
          //We can operate
          return 0;
        } else if (splitStr[i].substring(9,12) == "STP") {
          //We are not allowed to move
          return 1;
        }
      }
    }
    return 2;
  } else {
    if(serverResponse.length() > 0) {
      Serial.println(F("[Arduino User Code]: ERROR: Incoming data not formatted as JSON"));
      Serial.println("[Arduino User Code]: JSON READOUT: " + serverResponse);
    } else {
      Serial.println(F("[Arduino User Code]: ERROR: Blank response from server"));
    }
  }
}

void(* resetFunc) (void) = 0;
void restartArduino() { resetFunc(); }
