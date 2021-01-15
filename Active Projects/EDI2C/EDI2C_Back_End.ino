int my_EDI2C_Address = -1;
int baudrate = 9600;
int maxAddress = 255;

//This variable is juust so the system can note on startup if a new message came in while doing stuff
//Obviously if this sets to true, there is a master on the network
bool masterDetectedTemp = false;
bool ignoreInputData = false;
bool potentialMasterLoss = false;
LinkedList<int> masterAddresses = LinkedList<int>();

//Join the network:
// - If there is no master detected, it declares itself master
// - If there is a master detected, then it asks for a new address
void joinEDI2C() { joinEDI2C(9600); }
void joinEDI2C(int _baudrate) {
  pinMode(masterLock, INPUT);
  pinMode(transmittingMsg, INPUT);
  pinMode(NetData, INPUT);
  pinMode(NetClk, INPUT);
  pinMode(AddrReqNew, INPUT);
  pinMode(AddrReqReady, INPUT);
  
  Serial.println("[No Role][No Addr]: Joining network");
  Serial.println("[No Role][No Addr]: Adding random offset for master-clash avoidance");
  
  randomSeed(analogRead(0));
  delayMicroseconds(random(200,5000));
  
  ignoreInputData = true;
  
  // Here we are starting the message "Listening" routine, but since ignoreInputData is true, it will ignore incoming data
  attachInterrupt(digitalPinToInterrupt(transmittingMsg),receiveMessage,RISING);
  baudrate = _baudrate;

  //Try to locate a master on the network by the master lock (Alternatively, if a message comes in, that will also trigger this via the "masterDetectedTemp" variable)
  bool masterDetected = digitalRead(masterLock) || masterDetectedTemp;
  if (!masterDetected) {
    Serial.println("[No Role][No Addr]: No master detected. Waiting for switch over event...");
    
    // There is no current master
    unsigned long currentTime = micros();
    while(micros() - currentTime < 1000) {
      masterDetected |= masterDetectedTemp;
      if (digitalRead(masterLock) && (!masterDetected)) {
        Serial.println("[Slave][No Addr]: Switch over event detected! Setting self to slave device");
        masterDetected = true;
        isMaster = false;
      }
    }
  }
  
  if (masterDetected || masterDetectedTemp) {
    //There is a master on the network. Simply get it's attention, then it will give us an address
    isMaster = false;
    int connectionAttempts = 5;
    while (true) {
      Serial.println("[Slave][No Addr]: Master detected on network. Waiting for other devices to release masters attention");
      randomSeed(analogRead(0));
      
      int temp = random(500,5000);
      unsigned long currentTime = micros();
      while(micros() - currentTime < temp) {
        if (digitalRead(AddrReqReady) || digitalRead(AddrReqNew)) {
          currentTime = micros();
        }
      }
      
      Serial.println("[Slave][No Addr]: Capturing masters attention");
      digitalWrite(AddrReqNew,HIGH);
      ignoreInputData = false;
      while(!digitalRead(AddrReqReady)) {}
      Serial.println("[Slave][No Addr]: Captured masters attention");
      digitalWrite(AddrReqNew,LOW);
      while(receivedDataBuffer.size() == 0) {}  // Here is where the master would trigger the "dataReceived" interrupt
      
      //We have received the data that contains our shiny new address
      String tempData = receivedDataBuffer.shift();
      if ((tempData.substring(0,2) == "-1") && (tempData.substring(3,5) == "NA")) {
        my_EDI2C_Address = tempData.substring(6,tempData.length()).toInt();
        break;
      } else {
        //For some reason, the incoming data is not a valid response. Either the master is corrupt, or there are 2 masters on the network both talking
        connectionAttempts--;

        if (connectionAttempts != 0) {
          Serial.println("[Slave][No Addr]: ERROR - Corrupt addressing data. Trying again...");
        } else {
          Serial.println("[Slave][No Addr]: ERROR - Run out of connection attempts. Shutting down");
          while(true){};
        }
      }
    }
    
    if (my_EDI2C_Address == -2) {
      Serial.println("[Slave][No Addr]: The network is full. Cannot continue, shutting down");
      while(true){};
    }
    
    Serial.println("[Slave][" + String(my_EDI2C_Address) + "]: New address recorded internally!");
  } else {
    ignoreInputData = false;
    Serial.println("[Master][0]: No master detected on network. Declaring self as master");
    // We declare ourselves the new master
    digitalWrite(masterLock,HIGH);
    isMaster = true;
    my_EDI2C_Address = 0;
    allNetworkAddresses.add(0);
  }
}

void sendRawMessage(String data, int address) {
  delayMicroseconds(500);
  digitalWrite(transmittingMsg,HIGH);
  
  String completeData = String(address) + "|" + data;
  for(int i = 0; i < completeData.length(); i++) { transmitByte(byte(completeData[i])); }
  transmitByte(byte("\n"));
  
  digitalWrite(transmittingMsg,LOW);
}

void transmitByte(byte x) {
  //  - D4: Network Data line
  //  - D5: Network Clock line
  int clockTimingVariable = 1000000 / baudrate;
  
  digitalWrite(NetData,bitRead(x,0)); delayMicroseconds(clockTimingVariable);
  digitalWrite(NetClk,HIGH); delayMicroseconds(clockTimingVariable);
  digitalWrite(NetClk,LOW); delayMicroseconds(clockTimingVariable);
  
  digitalWrite(NetData,bitRead(x,1));
  digitalWrite(NetClk,HIGH); delayMicroseconds(clockTimingVariable);
  digitalWrite(NetClk,LOW); delayMicroseconds(clockTimingVariable);
  
  digitalWrite(NetData,bitRead(x,2));
  digitalWrite(NetClk,HIGH); delayMicroseconds(clockTimingVariable);
  digitalWrite(NetClk,LOW); delayMicroseconds(clockTimingVariable);
  
  digitalWrite(NetData,bitRead(x,3));
  digitalWrite(NetClk,HIGH); delayMicroseconds(clockTimingVariable);
  digitalWrite(NetClk,LOW); delayMicroseconds(clockTimingVariable);
  
  digitalWrite(NetData,bitRead(x,4));
  digitalWrite(NetClk,HIGH); delayMicroseconds(clockTimingVariable);
  digitalWrite(NetClk,LOW); delayMicroseconds(clockTimingVariable);
  
  digitalWrite(NetData,bitRead(x,5));
  digitalWrite(NetClk,HIGH); delayMicroseconds(clockTimingVariable);
  digitalWrite(NetClk,LOW); delayMicroseconds(clockTimingVariable);
  
  digitalWrite(NetData,bitRead(x,6));
  digitalWrite(NetClk,HIGH); delayMicroseconds(clockTimingVariable);
  digitalWrite(NetClk,LOW); delayMicroseconds(clockTimingVariable);
  
  digitalWrite(NetData,bitRead(x,7));
  digitalWrite(NetClk,HIGH); delayMicroseconds(clockTimingVariable);
  digitalWrite(NetClk,LOW); delayMicroseconds(clockTimingVariable);
  
  digitalWrite(NetData,LOW); delayMicroseconds(clockTimingVariable);
}

void receiveMessage() {
  int timeOutPeriod = 10000;
  masterDetectedTemp = true;
  if (ignoreInputData){return;}
  
  if (isMaster){return;}
  if ((my_EDI2C_Address != -1) && ( digitalRead(AddrReqNew))) { return; }
  if ((my_EDI2C_Address == -1) && (!digitalRead(AddrReqNew))) { return; }
  
  //We are a slave and a master just contacted us
  String msg = "";
  while (digitalRead(transmittingMsg)) {
    unsigned long msgStartTime = micros();
    while(!digitalRead(NetClk)) {
      if(!digitalRead(transmittingMsg)){
        potentialMasterLoss = true;
        return;
      }

//      if (micros() - msgStartTime > timeOutPeriod) {
//        potentialMasterLoss = true;
//        return;
//      }
    }
    bool bit_1 = digitalRead(NetData);

    msgStartTime = micros();
    while(!digitalRead(NetClk)) {
      if(!digitalRead(transmittingMsg)){
        potentialMasterLoss = true;
        return;
      }

//      if (micros() - msgStartTime > timeOutPeriod) {
//        potentialMasterLoss = true;
//        return;
//      }
    }
    bool bit_2 = digitalRead(NetData);

    msgStartTime = micros();
    while(!digitalRead(NetClk)) {
      if(!digitalRead(transmittingMsg)){
        potentialMasterLoss = true;
        return;
      }

//      if (micros() - msgStartTime > timeOutPeriod) {
//        potentialMasterLoss = true;
//        return;
//      }
    }
    bool bit_3 = digitalRead(NetData);

    msgStartTime = micros();
    while(!digitalRead(NetClk)) {
      if(!digitalRead(transmittingMsg)){
        potentialMasterLoss = true;
        return;
      }

//      if (micros() - msgStartTime > timeOutPeriod) {
//        potentialMasterLoss = true;
//        return;
//      }
    }
    bool bit_4 = digitalRead(NetData);

    msgStartTime = micros();
    while(!digitalRead(NetClk)) {
      if(!digitalRead(transmittingMsg)){
        potentialMasterLoss = true;
        return;
      }

//      if (micros() - msgStartTime > timeOutPeriod) {
//        potentialMasterLoss = true;
//        return;
//      }
    }
    bool bit_5 = digitalRead(NetData);

    msgStartTime = micros();
    while(!digitalRead(NetClk)) {
      if(!digitalRead(transmittingMsg)){
        potentialMasterLoss = true;
        return;
      }

//      if (micros() - msgStartTime > timeOutPeriod) {
//        potentialMasterLoss = true;
//        return;
//      }
    }
    bool bit_6 = digitalRead(NetData);

    msgStartTime = micros();
    while(!digitalRead(NetClk)) {
      if(!digitalRead(transmittingMsg)){
        potentialMasterLoss = true;
        return;
      }

//      if (micros() - msgStartTime > timeOutPeriod) {
//        potentialMasterLoss = true;
//        return;
//      }
    }
    bool bit_7 = digitalRead(NetData);

    msgStartTime = micros();
    while(!digitalRead(NetClk)) {
      if(!digitalRead(transmittingMsg)){
        potentialMasterLoss = true;
        return;
      }

//      if (micros() - msgStartTime > timeOutPeriod) {
//        potentialMasterLoss = true;
//        return;
//      }
    }
    bool bit_8 = digitalRead(NetData);
    
    byte tempByte = bit_1 | (bit_2 << 1) | (bit_3 << 2) | (bit_4 << 3) | (bit_5 << 4) | (bit_6 << 5) | (bit_7 << 6) | (bit_8 << 7);
    
    if (char(tempByte) != '\n') {
      msg += String(tempByte);
    } else {
      receivedDataBuffer.add(msg);
      msg = "";
    }
  }

  
  if (digitalRead(masterLock)) { potentialMasterLoss = false; }
  if (potentialMasterLoss) {
    //There is no master on the network. Using your address as a timer, first to jump in gets to be "Master"
    int tempTime = my_EDI2C_Address * 100;
    unsigned long currentTime = micros();
    while (micros() - currentTime < tempTime) {
      if (digitalRead(masterLock)) { return; }
    }

    digitalWrite(masterLock,HIGH);
    isMaster = true;
    sendRawMessage("MS",my_EDI2C_Address);
  }
}

String getBlankAddress() {
  for(int addr = 0; addr <= maxAddress; addr++) {
    bool addrIsAvailable = true;
    for(int i = 0; i < allNetworkAddresses.size(); i++) {
      if (allNetworkAddresses.get(i) == addr) {
        addrIsAvailable = false;
        break;
      }
    }

    if (addrIsAvailable) {
      return String(addr);
    }
  }

  return "";
}

void releaseMaster() {
  if (!isMaster){return;}
  
  // We just need to get a list of the devices that haven't been master yet, then give control to them. If there are none left, we reset the master list
  int newAddr = -1;
  if (masterAddresses.size() == allNetworkAddresses.size()) { masterAddresses.clear(); }
  
  for (int netAddrIndex = 0; netAddrIndex < allNetworkAddresses.size(); netAddrIndex++) {
    bool hasBeenMaster = false;
    for (int masterIndex = 0; masterIndex < masterAddresses.size(); masterIndex++) {
      if (allNetworkAddresses.get(netAddrIndex) == masterAddresses.get(masterIndex)) {
        hasBeenMaster = true;
        break;
      }
    }

    if (!hasBeenMaster) {
      newAddr = allNetworkAddresses.get(netAddrIndex);
      sendRawMessage("MS",newAddr);
      isMaster = false;
      digitalWrite(masterLock,LOW);
      
      unsigned long startTime = micros();
      while (micros() - startTime < 10000) {
        if (digitalRead(masterLock)) {
          masterAddresses.add(newAddr);
          break;
        }
      }

      digitalWrite(masterLock,HIGH);
    }
  }
}

void handleMasterControl() {
  if (digitalRead(AddrReqNew) && isMaster) {
    // A new device wants to join the network
    digitalWrite(AddrReqReady,HIGH);
    while(digitalRead(AddrReqNew)) {}

    String newSlaveAddress = getBlankAddress();
    if (newSlaveAddress == "") { newSlaveAddress = "-2";}
    sendRawMessage("NA:" + newSlaveAddress,-1);
    allNetworkAddresses.add(newSlaveAddress.toInt());
    digitalWrite(AddrReqReady,LOW);
    
    //Now we just give it a copy of our "allNetworkAddresses" and "masterAddresses" variables
    sendRawMessage("UA:" + getAllUsedAddressesList(),newSlaveAddress.toInt());
    sendRawMessage("PM:" + getAllPreviousMastersList(),newSlaveAddress.toInt());
  }
  
  for (int i = 0; i < receivedDataBuffer.size(); i++) {
    String completeCommand = receivedDataBuffer.get(i);
    int addr = completeCommand.substring(0,completeCommand.indexOf('|')).toInt();
    
    String command = "";
    String commandParams = "";
    if (completeCommand.indexOf(':') < 0) {
      command = completeCommand.substring(completeCommand.indexOf('|') + 1, completeCommand.length());
    } else {
      command = completeCommand.substring(completeCommand.indexOf('|') + 1, completeCommand.indexOf(':'));
      commandParams = completeCommand.substring(completeCommand.indexOf(':') + 1, completeCommand.length());
    }

    if (addr == -1) {
      // A new device was added to the network
      allNetworkAddresses.add(commandParams.toInt());
      receivedDataBuffer.remove(i);
    } else if (command == "MS") {
      masterAddresses.add(addr);
      if (addr == my_EDI2C_Address) {
        // We have just been given the status of master
        while(digitalRead(masterLock)) {}
        
        isMaster = true;
        digitalWrite(masterLock,HIGH);
      }
      
      receivedDataBuffer.remove(i);
    } else if ((command == "UA") && (addr == my_EDI2C_Address)) {
      int count = 0;
      for (int x = 0; x < commandParams.length(); x++) {
        if (commandParams[x] == ',') { count++; }
      }
      
      for (int x = 0; x < count; x++) {
        bool isInList = false;
        for (int y = 0; y < allNetworkAddresses.size(); y++) {
          if (allNetworkAddresses[y] == commandParams[x]) { isInList = true; }
        }
        
        if (!isInList) {
          allNetworkAddresses.add(splitString(commandParams,',',x).toInt());
        }
      }
      
      receivedDataBuffer.remove(i);
    } else if ((command == "PM") && (addr == my_EDI2C_Address)) {
      int count = 0;
      for (int x = 0; x < commandParams.length(); x++) {
        if (commandParams[x] == ',') { count++; }
      }
      
      for (int x = 0; x < count; x++) {
        bool isInList = false;
        for (int y = 0; y < masterAddresses.size(); y++) {
          if (masterAddresses[y] == commandParams[x]) { isInList = true; }
        }
        
        if (!isInList) {
          masterAddresses.add(splitString(commandParams,',',x).toInt());
        }
      }
      
      receivedDataBuffer.remove(i);
    }
  }
  
  unsigned long tempTime = micros();
  while (!digitalRead(masterLock)) {
    if (micros() - tempTime > 12000) {
      //There is no detected master on the network. Panic!
      //-------------------------------------------------------------------------------------------------INCOMPLETE-------------------------------------------------------------------------------------------------
      digitalWrite(masterLock,HIGH);
      isMaster = true;
      sendRawMessage("MS",my_EDI2C_Address);
    }
  }
}

String getAllPreviousMastersList() {
  String result = "";
  for (int i = 0; i < masterAddresses.size(); i++) {
    result += String(masterAddresses.get(i));
    if (i != masterAddresses.size() - 1) { result += ","; }
  }
  return result;
}

String getAllUsedAddressesList() {
  String result = "";
  for (int i = 0; i < allNetworkAddresses.size(); i++) {
    result += String(allNetworkAddresses.get(i));
    if (i != allNetworkAddresses.size() - 1) { result += ","; }
  }
  return result;
}

String splitString(String data, char separator, int index) {
  //I do not know how this works, it's the only copy and pasted thing I have done
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
