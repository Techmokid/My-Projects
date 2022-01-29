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

#define resetIDOnBoot

char server[] = "techmo.unity.chickenkiller.com";
int port = 80;
int ID = 0;

String serverResponse = "";
void setup() {
  while(1);
  Serial.begin(115200);
  
  pinMode(RUN_PIN,OUTPUT);
  pinMode(COM_PIN_1,INPUT_PULLUP);
  pinMode(COM_PIN_2,INPUT_PULLUP);
  pinMode(COM_PIN_3,INPUT_PULLUP);

#ifdef resetIDOnBoot
  writeEepromInt(0,-1);
#endif

  ID = readEepromInt(0);
  
  Serial.println(F("Starting Modem...")); setupModem();
  
  if (ID == -1) {
    //The ID hasn't been set
    getServerResponse(server, port, new String {"Newid:1"}, 1);
    String tmp = serverResponse;
    if (tmp == "") { Serial.println("Error getting response from server for ID"); while(true) {}}
    
    int strippedResp = tmp.substring(tmp.indexOf(":")+1,tmp.indexOf("}")).toInt();
    writeEepromInt(0,strippedResp);
    ID = strippedResp;
    
    Serial.println("Assigned ID by server: " + String(ID));
  } else {
    Serial.println("Unit ID: " + String(ID));
  }
}

void writeEepromInt(int location, int value){
  EEPROM.write(location, value);
  EEPROM.write(location + 1, value >> 8);
}

int readEepromInt(int location){
  int val;

  val = (EEPROM.read(location + 1) << 8);
  val |= EEPROM.read(location);

  return val;
}

void loop() {
  String temp[] = {"Getinfoonid:" + (String)ID};
  getServerResponse(server, port, temp, 1); String response = serverResponse;
  //String response = "<body>{ID:1,GPSLastLat:0.00,GPSLastLong:0.00,GPSLastTime:\"AWST_20:11:41_29/11/21\",Temp:23,Status:\"Online\",RunMode:\"RLS\"}</body>";
  
  checkMotorStatus();
  switch(GetRunmodeFromString(response)) {
    case 0:
      //We got the all clear to go
      digitalWrite(RUN_PIN,HIGH);
    case 1:
      //We got a stop code
      digitalWrite(RUN_PIN,LOW);
    case 2:
      //We did not get a code returned
      Serial.println(F("Potential error has occured. Trying again..."));
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

int GetRunmodeFromString(String response) {
  if (response.length() == 0) { restartArduino(); }

  response = response.substring(response.indexOf("<body>"),response.indexOf("</body>"));
  response.replace("<br/>","\n");
  response.replace("<body>","");
  
  //Here is where we would substring the incoming data
  int strStart = response.indexOf("{");
  int strEnd = response.lastIndexOf("}");
  int operationMode = -1;
  if ((strStart != -1) && (strEnd != -1)) {
    String tempStr = response.substring(strStart + 1,strEnd);
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
    if(response.length() > 0) {
      Serial.println(F("ERROR: Incoming data not formatted as JSON"));
      Serial.println("JSON READOUT: " + response);
    } else {
      Serial.println(F("ERROR: Blank response from server"));
    }
  }
}

void(* resetFunc) (void) = 0;
void restartArduino() { resetFunc(); }
