#include <LinkedList.h>

#define masterLock        2
#define transmittingMsg   3
#define NetData           4
#define NetClk            5
#define AddrReqNew        6
#define AddrReqReady      7

bool isMaster = false;
LinkedList<int> allNetworkAddresses = LinkedList<int>();
LinkedList<String> receivedDataBuffer = LinkedList<String>();

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("\n\n");
  
  joinEDI2C(9600);
  
  //sendRawMessage("testValue",73);
}

void loop() {
  handleMasterControl();
  
  digitalWrite(LED_BUILTIN,isMaster);
}
