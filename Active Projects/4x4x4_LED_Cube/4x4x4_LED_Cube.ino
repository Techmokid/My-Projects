int pins1[4] = {0, 1, 2, 3};
int pins2[4] = {4, 5, 6, 7};
int pins3[4] = {8, 9, 10, 11};
int pins4[4] = {12, 13, A0, A1};

void setup() {
  setupLEDs();
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);

  unsigned long t = millis();
  while(millis() - t < 1500) {
    for(int x = 0; x < 4; x++) {
      for(int y = 0; y < 4; y++) {
        for(int z = 0; z < 4; z++) {
          setPixel(x,y,z,HIGH);
          //carefulDelay(1);
          delayMicroseconds(200);
          setupLEDs();
        }
      }
    }
  }
}

void loop() { }

void carefulDelay(unsigned long timer) {
  unsigned long prevMillis = millis();
  while(millis() - prevMillis < timer) {
    updateLEDs();
  }
}
