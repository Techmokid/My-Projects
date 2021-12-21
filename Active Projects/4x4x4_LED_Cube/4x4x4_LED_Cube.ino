int pins1[4] = {0, 1, 2, 3};
int pins2[4] = {4, 5, 6, 7};
int pins3[4] = {8, 9, 10, 11};
int pins4[4] = {12, 13, A0, A1};

void setup() { setupLEDs(); }

void loop() {
  
}

void carefulDelay(unsigned long timer) {
  unsigned long prevMillis = millis();
  while(millis() - prevMillis < timer) {
    updateLEDs();
  }
}
