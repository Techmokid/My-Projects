void transmitDataBytes(byte data,byte AddressDataByte,bool reverseBits) { transmitDataBytes({data},AddressDataByte,reverseBits); }
void transmitDataBytes(byte data[],byte AddressDataByte,bool reverseBits) {
  //Convert the data byte to a string for processing
  String dataString = "";
  for (int i=0;i<numberOfCommandArguments;i++){
    for (int j=0;j<8;j++){
      if (reverseBits) {
        dataString += String(bitRead(data[i],7-j));
      } else {
        dataString += String(bitRead(data[i],j));
      }
    }
  }
  
  //Convert the address data byte to a string for processing
  String addressString = "";
  for (int j=0;j<8;j++){
    if (reverseBits) {
      addressString += bitRead(AddressDataByte,7-j);
    }else{
      addressString += bitRead(AddressDataByte,j);
    }
  }
  
  //Put the sentence together in the correct order for DCC communications
  String sentence = "111111111111110" + String(addressString) + "0" + String(dataString) + "1";
  
  //Iterate over the resulting sentence and transmit every single bit seperately
  Serial.println(sentence);
  for(unsigned int i = 0; i < sentence.length(); i++) {
    if (sentence[i]=='0') { turnPinOff(); delayMicroseconds(50); turnPinOn(); delayMicroseconds(50);
    } else if (sentence[i]=='1') { turnPinOff(); delayMicroseconds(100); turnPinOn(); delayMicroseconds(100); }
  }
  
  turnPinOn();
}

void turnPinOn() {}
void turnPinOff() {}
