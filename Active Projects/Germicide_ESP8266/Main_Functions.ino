void handleMainFunctions() {
  if (digitalRead(p.pinToGPIO(PIR_Pin)) && running) {
    Serial.println("Detected Movement!");
    stopProcess();
    digitalWrite(LED_BUILTIN,HIGH);
  }

  if ((millis() - timer >= flashInterval * 1000) && running) {
    Serial.println("Cleaning cycle complete!");
    stopProcess();
  }
}

void stopProcess() {
  if (!running) { return; }
  running = false;
  digitalWrite(p.pinToGPIO(Strobe_Pin),LOW);
  digitalWrite(p.pinToGPIO(Relay_Pin),LOW);
  Serial.println("Stopped");
}

void startProcess() {
  Serial.println("Starting...");
  
  running = true;
  digitalWrite(p.pinToGPIO(Strobe_Pin),HIGH);
  getRoomSize();
  digitalWrite(p.pinToGPIO(Relay_Pin),HIGH);
  
  timer = millis();
  Serial.println("Started");
}

void getRoomSize() {
  
}
