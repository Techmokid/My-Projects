void getSMS() {
  // Array to hold the number a SMS is retreived from
  char senderNumber[20];
  char c;
  if (sms.available()) {
    //Serial.println("Message received from:");
    
    // Get remote number
    sms.remoteNumber(senderNumber, 20);
    //Serial.println(senderNumber);
    
    // An example of message disposal
    // Any messages starting with # should be discarded
    if (sms.peek() == '#') {
      //Serial.println("Discarded SMS");
      sms.flush();
    }
    
    // Read message bytes and print them
    while (c = sms.read()) {
      //Serial.print(c);
    }
    
    //Serial.println("\nEND OF MESSAGE");
    
    // Delete message from modem memory
    sms.flush();
    //Serial.println("MESSAGE DELETED");
  }
}

int readSerial(char result[]) {
  int i = 0;
  while (1) {
    while (Serial.available() > 0) {
      char inChar = Serial.read();
      if (inChar == '\n') {
        result[i] = '\0';
        Serial.flush();
        return 0;
      }
      if (inChar != '\r') {
        result[i] = inChar;
        i++;
      }
    }
  }
}

void sendSMS(String msgString, String numberString) {
  int str_len = numberString.length() + 1;
  char numberArray[str_len];
  numberString.toCharArray(numberArray, str_len);
  readSerial(numberArray);
  
  sms.beginSMS(numberArray);
  sms.print(msgString);
  sms.endSMS();
}
