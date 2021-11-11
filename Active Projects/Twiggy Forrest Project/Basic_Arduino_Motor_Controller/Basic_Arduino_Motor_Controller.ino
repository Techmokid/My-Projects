// The error value between the two current sensors.
// Need to put it here for some reason to prevent compilation errors. WHY DO I NEED TO DO THIS?!?!?
float currentError = 0;
bool enableAmpSensorErrorDetection = false;

#define SKIP_MOTOR_TEST
//#define SKIP_MODEM_TEST

void setup() {
  //Initialize everything
  Serial.begin(115200);
  
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.println("Starting Motor..."); setupMotor();
  Serial.println("Starting Modem..."); setupModem();
  Serial.println("Fully Operational!");

  //Motor test code
#ifndef SKIP_MOTOR_TEST
  Serial.println("Running Motor Test Code...");
  warningBuzz();
  setSpeed(1);    carefulDelay(5000);
  setSpeed(0);    carefulDelay(5000);

  warningBuzz();
  setSpeed(-1);   carefulDelay(5000);
  setSpeed(0);    carefulDelay(5000);
#else
  Serial.println("Skipping Motor Test");
#endif

#ifndef SKIP_MODEM_TEST
  //SIM7000 test code
  Serial.println("Running SIM7000 Test Code...");
  char server[] = "techmo.unity.chickenkiller.com";
  int port = 80;
  
  String response = getServerResponse(server, port);
  if (response.length() == 0) { restartArduino(); }
  
  response = response.substring(response.indexOf("<body>"),response.indexOf("</body>"));
  response.replace("<br/>","\n");
  response.replace("<body>","");
  Serial.println("|----------------------------------------------------|");
  Serial.println(response);
#else
  Serial.println("Skipping Modem Test");
#endif
  
  Serial.println("Done");
}

void loop() { }

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

void warningBuzz() {
  setSpeed(0.5);  carefulDelay(500); setSpeed(0);carefulDelay(500);
  setSpeed(0.5);  carefulDelay(500); setSpeed(0);carefulDelay(500);
  setSpeed(0.5);  carefulDelay(500); setSpeed(0);carefulDelay(500);
}
