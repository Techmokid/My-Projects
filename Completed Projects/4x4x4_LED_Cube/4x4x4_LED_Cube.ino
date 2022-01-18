bool LED_MEM[4][4][4];
int pins1[4] = {0, 1, 2, 3};
int pins2[4] = {4, 5, 6, 7};
int pins3[4] = {8, 9, 10, 11};
int pins4[4] = {12, 13, A0, A1};

void setup() {
  setupLEDs();
}

void loop() {
  int posX = random(0,4);
  int posY = random(0,4);
  setPixel(posX,3,posY,HIGH);
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
    for (int z = 0; z < 4; z++) {
      LED_MEM[x][0][z] = LED_MEM[x][1][z];
      LED_MEM[x][1][z] = LED_MEM[x][2][z];
      LED_MEM[x][2][z] = LED_MEM[x][3][z];
      LED_MEM[x][3][z] = 0;
    }
  }
}
