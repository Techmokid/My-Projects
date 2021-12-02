void setup() {}

void loop() {
  setMicLED(true);  delayYield(1000);
  setMicLED(false); delayYield(1000);
  for(int y = 0; y < 5; y++) {
    //for(int x = 0; x < 5; x++) {
    //  setLED(x,y,HIGH); delayYield(100);
    //  setLED(x,y,LOW);  delayYield(100);
    //}
  }
  delayYield(1000);

  int temp[][5] = {
    {0,0,1,0,0},
    {0,1,0,1,0},
    {1,0,1,0,1},
    {0,1,0,1,0},
    {0,0,1,0,0}
  };
  
  setDisplay(temp);
  delayYield(1000);
  displayHeart();
  delayYield(1000);
  for(int i = 0; i < 10; i++) {
    displayBoxRings(); delayYield(100);
    displayBoxRingsReverse(); delayYield(100);
  }
  for(int i = 0; i < 10; i++) {
    displayChessboard(); delayYield(100);
    displayChessboardReverse(); delayYield(100);
  }
  displayFaceHappy();
  delayYield(1000);
  displayFaceNormal();
  delayYield(1000);
  displayFaceSad();
  delayYield(1000);
  displayFaceAngry();
  delayYield(1000);
  displayFaceUnhappy();
  delayYield(1000);
  displayFaceEvil();
  delayYield(1000);
  for(int i = 0; i < 10; i++) {
    int delayTimer = 75;
    rain1(); delayYield(delayTimer);
    rain2(); delayYield(delayTimer);
    rain3(); delayYield(delayTimer);
    rain4(); delayYield(delayTimer);
    rain5(); delayYield(delayTimer);
    rain6(); delayYield(delayTimer);
    rain7(); delayYield(delayTimer);
    rain8(); delayYield(delayTimer);
    rain9(); delayYield(delayTimer);
    rain10(); delayYield(delayTimer);
    rain11(); delayYield(delayTimer);
    rain12(); delayYield(delayTimer);
    rain13(); delayYield(delayTimer);
    rain14(); delayYield(delayTimer);
    rain15(); delayYield(delayTimer);
    rain16(); delayYield(delayTimer);
  }
  displayRoadHor();
  delayYield(2000);
  displayRoadVer();
  delayYield(2000);
  
  displayArrowUp();
  delayYield(1000);
  displayArrowUpRight();
  delayYield(1000);
  displayArrowRight();
  delayYield(1000);
  displayArrowDownRight();
  delayYield(1000);
  displayArrowDown();
  delayYield(1000);
  displayArrowDownLeft();
  delayYield(1000);
  displayArrowLeft();
  delayYield(1000);
  displayArrowUpLeft();
}
