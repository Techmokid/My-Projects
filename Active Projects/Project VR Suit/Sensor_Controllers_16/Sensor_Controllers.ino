int sensorDataArr[128];

void setup() {
  Serial.begin(1000000);
  setupSensors();
}

unsigned long prevMillis = 0;
void loop() {
  updateSensors();

  for(int i = 0; i < 128; i++) {
  //  Serial.print(char(sensorDataArr[i]));
  //  Serial.print(',');
  }
  
  float timeDiff = micros() - prevMillis;
  float secondsPerIteration = timeDiff/1000000;
  float refreshRate = 1/secondsPerIteration;
  Serial.println(String(refreshRate) + " Hz");
  prevMillis = micros();
}
