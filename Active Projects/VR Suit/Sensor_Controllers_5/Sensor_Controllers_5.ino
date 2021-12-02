int sensorDataArr[48];

void setup() {
  Serial.begin(115200);
  setupSensors();
}

unsigned long prevMillis = 0;
void loop() {
  updateSensors();

  String msg = "";
  for(int i = 0; i < 32; i++) {
    msg += String(sensorDataArr[i]);
    msg += ',';
  }
  
  float timeDiff = micros() - prevMillis;
  float secondsPerIteration = timeDiff/1000000;
  float refreshRate = 1/secondsPerIteration;
  Serial.println(String(refreshRate) + " Hz");
  prevMillis = micros();
}
