unsigned long prevTime = 0;


void setup() {
  Serial.begin(115200);
  Serial.println("Started");      startModem(); restartModem();
  delay(10000);
  sendCommand("AT"); Serial.println(waitForResponse());
  sendCommand("AT"); Serial.println(waitForResponse());
  sendCommand("AT"); Serial.println(waitForResponse());
  
  //sendCommand("AT+CMGL=\"ALL\"");
  sendCommand("AT+CMGF=1");
  
  String temp = waitForResponse();
  Serial.println("Test");
  delay(2000);
  Serial.println(temp);
}

void loop() {
  createSerialLoop();
}
