//0 is top right
//1 is top
//2 is top left
//3 is middle
//4 is DP
//5 is bottom right
//6 is bottom
//7 is bottom left

const int dispPins[] = {
  21, 20, 19, 18, 17, 16, 15, 14,
  2,  3,  4,  5,  6,  7,  8,  9,
  38, 40, 42, 44, 46, 48, 50, 52,
  39, 41, 43, 45, 47, 49, 51, 53,
  22, 24, 26, 28, 30, 32, 34, 36,
  23, 25, 27, 29, 31, 33, 35, 37
};

void setup() {
  for(int i = 0; i < 6; i++) {
    turnOnDisp(i);
    delay(200);
  }
  for(int i = 0; i < 6; i++) {
    turnOffDisp(i);
    delay(200);
  }

  digitalWrite(dispPins[8],HIGH);
}

void loop() { }
