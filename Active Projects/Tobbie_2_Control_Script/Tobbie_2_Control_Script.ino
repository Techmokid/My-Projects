#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

void setup() {
  clearDisplay();
  updateDisplay();
}

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

  //int melody[] = { NOTE_C4, NOTE_G3, 0, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4 };
  //int noteDurations[] = { 4, 8, 16, 16, 4, 4, 4, 4, 4 };
  int melody[] = { NOTE_A3, NOTE_F4, NOTE_C5 };
  int noteDurations[] = {24, 24, 24};
  playMelody(melody,noteDurations,3);
  delayYield(1000);

  displayFaceEcstatic();
  walkForwards(true);
  delayYield(1000);
  walkForwards(false);
  turnLeft(true);
  delayYield(1000);
  turnLeft(false);
  walkForwards(true);
  delayYield(1000);
  walkForwards(false);
  turnRight(true);
  delayYield(1000);
  turnRight(false);
  walkBackwards(true);
  delayYield(1000);
  walkBackwards(false);
  
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
