#include <LinkedList.h>

//Here we define which pins to use.
//NOTE: "transmittingMsg" must be on an interrupt pin.
#define masterLock        2
#define transmittingMsg   3
#define NetData           4
#define NetClk            5
#define AddrReqNew        6
#define AddrReqReady      7

//These are handy variables we will hold onto for later
bool isMaster = false;
LinkedList<int> allNetworkAddresses = LinkedList<int>();
LinkedList<String> receivedDataBuffer = LinkedList<String>();

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("\n\n");
  
  joinEDI2C(9600);
}

void loop() {
  handleMasterControl();
  
  digitalWrite(LED_BUILTIN,isMaster);

  //If we are not the master, then see if we have data in memory
  if (!isMaster) {
    int masterAddress = -1;
    String data = "";
    
    getNextUserData(masterAddress,data);
    
    if (masterAddress != -1) {
      Serial.println("We received data from the master on address: " + String(masterAddress));
      Serial.println(" - The data: " + String(data));
      Serial.println();
    }
  } else {
    //If we are the master, then wait 1 second and then send a message to the network
    delay(1000);

    //We want to get the address of any other device on the network.
    int otherAddress = -1;
    for (int i = 0; i < allNetworkAddresses.size(); i++) {
      if (allNetworkAddresses[i] != getMyAddress()) {
        otherAddress = allNetworkAddresses[i];
      }
    }

    //If we aren't alone on the network, say hi to the other device
    if (otherAddress != -1) {
      sendUserData("Hello Other Device!",otherAddress);
    } else {
      Serial.println("We are alone on the network :(");
    }
  }
}
