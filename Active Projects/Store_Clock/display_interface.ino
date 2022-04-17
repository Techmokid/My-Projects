void setDisplay(int disp,int val) {
  if (val == 0) {
    
  } else if (val == 1) {
    
  } else if (val == 2) {
    
  } else if (val == 3) {
    
  } else if (val == 4) {
    
  } else if (val == 5) {
    
  } else if (val == 6) {
    
  } else if (val == 7) {
    
  } else if (val == 8) {
    
  } else if (val == 9) {
    
  } else {
    turnOffDisp(disp);
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

