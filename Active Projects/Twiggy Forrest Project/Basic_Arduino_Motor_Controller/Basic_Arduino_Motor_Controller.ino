// The error value between the two current sensors.
// Need to put it here for some reason to prevent compilation errors. WHY DO I NEED TO DO THIS?!?!?
float currentError = 0;
bool enableAmpSensorErrorDetection = false;

void setup() {
  Serial.begin(115200);
  Serial.print("Starting...");
  
  pinMode(LED_BUILTIN,OUTPUT);
  setupMotor();
  
  Serial.println("Fully Operational!");
}

void loop() {
  setSpeed(0);    blink(1); carefulDelay(3000);
  setSpeed(0.5);  blink(2); carefulDelay(3000);
  setSpeed(1);    blink(3); carefulDelay(3000);
  setSpeed(0.5);  blink(2); carefulDelay(3000);
  setSpeed(0);    blink(1); carefulDelay(3000);
  setSpeed(-0.5); blink(2); carefulDelay(3000);
  setSpeed(-1);   blink(3); carefulDelay(3000);
  setSpeed(-0.5); blink(2); carefulDelay(3000);
  setSpeed(0);    blink(1); carefulDelay(3000);
  restartArduino();
  while(true) {}
}

void blink(int count) {
  while (count > 0) {
    digitalWrite(LED_BUILTIN,HIGH); delay(100);
    digitalWrite(LED_BUILTIN,LOW);  delay(100);
    count--;
  }
}

void carefulDelay(unsigned long wait) {
  unsigned long prevMillis = millis();
  while(millis() - prevMillis < wait) {
    readTotalCurrent();
    if ((currentError > 0.5) && enableAmpSensorErrorDetection) {
      Serial.println("ERROR: Amp Readings Inconsistant. Turning Off Motor And Turning To Emergency Mode");
      setSpeed(0);
      while(true) {
        digitalWrite(LED_BUILTIN,HIGH); delay(100);
        digitalWrite(LED_BUILTIN,LOW); delay(100);
      }
    }
  }
}
