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

char server[] = "techmo.unity.chickenkiller.com";
int port = 80;
int ID = 0;

void setup() {
  Serial.begin(115200);
  
  pinMode(RUN_PIN,OUTPUT);
  pinMode(COM_PIN_1,INPUT_PULLUP);
  pinMode(COM_PIN_2,INPUT_PULLUP);
  pinMode(COM_PIN_3,INPUT_PULLUP);
  
  ID = EEPROM.read(0);
  
  Serial.println("Starting Modem..."); setupModem();
  //if (ID == -1) {
  if(true) {
    //The ID hasn't been set
    String serverResp = getServerResponse(server, port, {"Newid:1"});
    Serial.println("|"+serverResp+"|");
    //The response is going to look like {"ID":"13"}
    
    int strippedResp = 0;
    //EEPROM.write(0,strippedResp);
    while(true);
  }
}

void loop() {
  String temp[] = {"Getinfoonid:" + (String)ID};
  String response = getServerResponse(server, port, temp);
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
      Serial.println("Potential error has occured. Trying again...");
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
    Serial.println("ERROR: Incoming data not formatted as JSON");
    Serial.println("JSON READOUT: " + response);
  }
}

void(* resetFunc) (void) = 0;
void restartArduino() { resetFunc(); }
