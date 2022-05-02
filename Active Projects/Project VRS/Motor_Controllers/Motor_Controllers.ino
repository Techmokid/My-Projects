// This script runs on an Arduino Due

void setup() {
  Serial.begin(115200);
  setupMotors();
}

unsigned long prevMillis = 0;
void loop() {
  for (int i = 0; i < 25; i++) {
    setMotorSpeed(i,255);
  }

  
  float timeDiff = micros() - prevMillis;
  float secondsPerIteration = timeDiff/1000000;
  float refreshRate = 1/secondsPerIteration;
  Serial.println(String(refreshRate) + " Hz");
  prevMillis = micros();
}
