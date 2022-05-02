void setupMotor() {
  pinMode(motor_pin_A,OUTPUT);
  pinMode(motor_pin_B,OUTPUT);
  
  digitalWrite(motor_pin_A,LOW);
  digitalWrite(motor_pin_B,LOW);
}

void setSpeed(float input_speed) {
  input_speed = clamp(input_speed,1,-1);
  
  if (input_speed == 0) {
    digitalWrite(motor_pin_A,LOW);
    digitalWrite(motor_pin_B,LOW);
  } else if (input_speed == 1) {
    digitalWrite(motor_pin_B,LOW);
    digitalWrite(motor_pin_A,HIGH);
  } else if (input_speed == -1) {
    digitalWrite(motor_pin_A,LOW);
    digitalWrite(motor_pin_B,HIGH);
  } else if (input_speed > 0) {
    digitalWrite(motor_pin_B,LOW);
    analogWrite(motor_pin_A,input_speed*255);
  } else if (input_speed < 0) {
    digitalWrite(motor_pin_A,LOW);
    analogWrite(motor_pin_B,(-input_speed)*255);
  } else {
    Serial.println("ERROR");
  }
}

float clamp(float in, float A, float B) {
  if (A > B) {
    if (in > A) { return A; }
    if (in < B) { return B; }
    return in;
  } else if (A < B) {
    if (in > B) { return B; }
    if (in < A) { return A; }
    return in;
  } else { return A; }
}

void RunMotorSafely() {
  #ifdef USE_CURRENT_SENSOR
  if (readAverageCurrent() > MAX_CURRENT) {
    if(!tryToUnclog(6)) {
      unsigned long prevMillis = millis();
      while(millis() - prevMillis < 1000 * 60 * 60 * 30) {
        digitalWrite(LED_BUILTIN,HIGH); delay(100);
        digitalWrite(LED_BUILTIN,LOW); delay(100);
        warningBuzz();
      }
    }
  } else { setSpeed(1); }
  #else
  setSpeed(1);
  #endif
}

bool tryToUnclog(int tries) {
  if (tries == 0) {
    setSpeed(0);  
    talkToServerInterfaceArduino("Clogged");
    return false;
  }

  setSpeed(0);
  delay(1500);
  talkToServerInterfaceArduino("Fixing Clog");
  
  //Back off
  setSpeed(-1);
  delay(5000);
  setSpeed(0);
  delay(2000);
  
  //Clear the average current values
  for (int i = 0; i < 10; i++) { readAverageCurrent(); }
  
  //Try again
  setSpeed(1);
  delay(1500);
  unsigned long prevMillis = millis();
  while(millis() - prevMillis < 8000) {
    delay(200);
    if (readAverageCurrent() > MAX_CURRENT) {
      return tryToUnclog(tries - 1);
    }
  }

  talkToServerInterfaceArduino("Online");
  return true;
}

void warningBuzz() {
  setSpeed(0.5);  delay(500); setSpeed(0); delay(500);
  setSpeed(0.5);  delay(500); setSpeed(0); delay(500);
  setSpeed(0.5);  delay(500); setSpeed(0); delay(500);
}
