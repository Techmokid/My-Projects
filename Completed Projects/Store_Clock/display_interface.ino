const int segmentMap[] = {
  1,1,1,0,0,1,1,1,  //0
  1,0,0,0,0,1,0,0,  //1
  1,1,0,1,0,0,1,1,  //2
  1,1,0,1,0,1,1,0,  //3
  1,0,1,1,0,1,0,0,  //4
  0,1,1,1,0,1,1,0,  //5
  0,1,1,1,0,1,1,1,  //6
  1,1,0,0,0,1,0,0,  //7
  1,1,1,1,0,1,1,1,  //8
  1,1,1,1,0,1,1,0,   //9
  1,1,1,1,0,1,0,1,   //A
  0,0,1,1,0,1,1,1,   //b
  0,1,1,0,0,0,1,1,   //C
  1,0,0,1,0,1,1,1,   //d
  0,1,1,1,0,0,1,1,   //E
  0,1,1,1,0,0,0,1,   //F
  0,1,1,0,0,1,1,1,   //G
  1,0,1,1,0,1,0,1,   //H
  0,0,1,0,0,0,0,1,   //I
  1,0,0,0,0,1,1,1,   //J
  0,1,1,1,0,1,0,1,   //K
  0,0,1,0,0,0,1,1,   //L
  0,0,0,0,0,0,0,0,   //M   CANNOT DO
  0,0,0,0,0,0,0,0,   //N   CANNOT DO
  1,1,1,0,0,1,1,1,   //O
  1,1,1,1,0,0,0,1,   //p
  1,1,1,1,0,1,0,0,   //q
  0,0,0,1,0,0,0,1,   //r
  0,1,1,1,0,1,1,0,   //S
  0,0,1,1,0,0,1,1,   //t
  1,0,1,0,0,1,1,1,   //U
  0,0,0,0,0,0,0,0,   //V   CANNOT DO
  0,0,0,0,0,0,0,0,   //W   CANNOT DO
  0,0,0,0,0,0,0,0,   //X   CANNOT DO
  1,0,1,1,0,1,1,0,   //y   CANNOT DO
  1,1,0,1,0,0,1,1,   //Z
};

//0 is top right
//1 is top
//2 is top left
//3 is middle
//4 is DP
//5 is bottom right
//6 is bottom
//7 is bottom left

void setDisplay(int disp,char val) {
  val = tolower(val);
  if (val > 47 && val < 58) {
    val -= 48;
  } else if (val > 96 && val < 123) {
    val -= 97 + 10;
  } else {
    turnOffDisp(disp);
    return;
  }

  for(int segmentIndex = 0; segmentIndex < 8; segmentIndex++) {
    bool displayIsDecimalPoint = (disp == 1) || (disp == 3);
    pinMode(dispPins[disp*8 + segmentIndex],OUTPUT);
    if ((segmentIndex == 4) && (displayIsDecimalPoint)) {
      //The segment index refers to the decimal point, AND the display in question is a decimal point display
      digitalWrite(dispPins[disp*8 + segmentIndex], HIGH);
    } else {
      //Just handle this display normally
      digitalWrite(dispPins[disp*8 + segmentIndex], segmentMap[val*8 + segmentIndex]);
    }
  }
}

void turnOffDisp(int disp) {
  int startPos = disp*8;
  for(int i = 0; i < 8; i++) {
    digitalWrite(dispPins[startPos + i],LOW);
  }
}

void turnOnDisp(int disp) {
  int startPos = disp*8;
  for(int i = 0; i < 8; i++) {
    pinMode(dispPins[startPos + i],OUTPUT);
    digitalWrite(dispPins[startPos + i],HIGH);
  }
}

void identifyDisplays() {
  setDisplay(0,'1');
  setDisplay(1,'2');
  setDisplay(2,'3');
  setDisplay(3,'4');
  setDisplay(4,'5');
  setDisplay(5,'6');
}

void displayTest() {
  for(int i = 0; i < 6; i++) {
    turnOnDisp(i);
    delay(250);
  }

  delay(1000);
  
  for(int i = 0; i < 6; i++) {
    turnOffDisp(i);
    delay(250);
  }
  
  for(int x = 0; x < 8; x++) {
    for(int i = 0; i < 6; i++) {
      digitalWrite(dispPins[i*8 + x],HIGH);
    }
    
    delay(1000);

    for(int i = 0; i < 6; i++) {
      digitalWrite(dispPins[i*8 + x],LOW);
    }
  }
}

void displayTime(int h, int m, int s) {
  if (!militaryTime && h > 12) { h -= 12; }

  int dispHrs1 = 0;
  int dispHrs2 = 0;
  int dispMins1 = 0;
  int dispMins2 = 0;
  int dispSecs1 = 0;
  int dispSecs2 = 0;
  dispHrs1 = floor(float(h) / 10);
  dispHrs2 = h - 10*dispHrs1;
  dispMins1 = floor(float(m) / 10);
  dispMins2 = m - 10*dispMins1;
  dispSecs1 = floor(float(s) / 10);
  dispSecs2 = s - 10*dispSecs1;
  setDisplay(2,String(dispHrs1)[0]);
  setDisplay(3,String(dispHrs2)[0]);
  setDisplay(4,String(dispMins1)[0]);
  setDisplay(5,String(dispMins2)[0]);
  setDisplay(0,String(dispSecs1)[0]);
  setDisplay(1,String(dispSecs2)[0]);
}
