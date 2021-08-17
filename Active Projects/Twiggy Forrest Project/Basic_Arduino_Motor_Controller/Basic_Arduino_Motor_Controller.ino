// The error value between the two current sensors.
// Need to put it here for some reason to prevent compilation errors. WHY DO I NEED TO DO THIS?!?!?
float currentError = 0;

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  setupMotor();
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
    if (currentError > 0.5) {
      setSpeed(0);
      while(true) {
        digitalWrite(LED_BUILTIN,HIGH); delay(100);
        digitalWrite(LED_BUILTIN,LOW); delay(100);
      }
    }
  }
}
