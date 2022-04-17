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
  1,1,1,1,0,1,1,0   //9
};

//digitalWrite(dispPins[disp*8 + 4],(disp == 1 || disp == 3);
void setDisplay(int disp,int val) {
  if (disp < 0 || disp > 9) { turnOffDisp(disp); return; }

  for(int segmentIndex = 0; segmentIndex < 8; segmentIndex++) {
    bool displayIsDecimalPoint = (disp == 1) || (disp == 3);
    if ((segmentIndex != 4) || (!displayIsDecimalPoint)) {
      digitalWrite(dispPins[disp*8 + segmentIndex], segmentMap[val*8 + segmentIndex]);
    } else {
      //The segment index refers to the decimal point, AND the display in question is a decimal point display
      digitalWrite(dispPins[disp*8 + segmentIndex],HIGH);
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
