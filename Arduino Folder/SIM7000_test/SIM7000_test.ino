bool isModemRunning = false;

void setup() {
  Serial.begin(115200);

  Serial.println("Starting Modem...");  startModem();
  Serial.println("Sending Command \"AT\"");    sendCommand("AT");
  Serial.println("AT: ");           Serial.println(receiveCommand()); delay(1000);
  Serial.println("AT: ");           Serial.println(receiveCommand()); delay(1000);
  Serial.println("AT: ");           Serial.println(receiveCommand()); delay(1000);
  Serial.println("AT: ");           Serial.println(receiveCommand()); delay(1000);
  Serial.println("Test Complete!");
}

void loop() {
  
}
