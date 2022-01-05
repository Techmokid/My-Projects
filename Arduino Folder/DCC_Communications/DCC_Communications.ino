int numberOfCommandArguments;

void setup() {
  byte dataToTransmit[] = {0,1,2,4,8,16,32,64,128};
  numberOfCommandArguments = sizeof(dataToTransmit);
  Serial.begin(9600);
  
  transmitDataBytes(dataToTransmit,5,false);
}

void loop() {}
