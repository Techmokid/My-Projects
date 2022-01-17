bool LED_MEM[4][4][4];
int pins1[4] = {0, 1, 2, 3};
int pins2[4] = {4, 5, 6, 7};
int pins3[4] = {8, 9, 10, 11};
int pins4[4] = {12, 13, A0, A1};

void setup() { setupLEDs(); }

void loop() {
  int posX = random(0,4);
  int posY = random(0,4);
  setPixel(posX,posY,3,HIGH);
  carefulDelay(250);
  moveDisplayDown();
}

void carefulDelay(unsigned long timer) {
  unsigned long prevMillis = millis();
  while(millis() - prevMillis < timer) {
    updateLEDs();
  }
}

void moveDisplayDown() {
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      LED_MEM[x][y][0] = LED_MEM[x][y][1];
      LED_MEM[x][y][1] = LED_MEM[x][y][2];
      LED_MEM[x][y][2] = LED_MEM[x][y][3];
      LED_MEM[x][y][3] = 0;
    }
  }
}

