void setDisplay(int disp,int val) {
  if (val == 0) {
    digitalWrite(dispPins[disp*8 + 0],HIGH);
    digitalWrite(dispPins[disp*8 + 1],HIGH);
    digitalWrite(dispPins[disp*8 + 2],HIGH);
    digitalWrite(dispPins[disp*8 + 3],LOW);
    digitalWrite(dispPins[disp*8 + 4],(disp == 1 || disp == 3);
    digitalWrite(dispPins[disp*8 + 5],HIGH);
    digitalWrite(dispPins[disp*8 + 6],HIGH);
    digitalWrite(dispPins[disp*8 + 7],HIGH);
  } else if (val == 1) {
    digitalWrite(dispPins[disp*8 + 0],HIGH);
    digitalWrite(dispPins[disp*8 + 1],LOW);
    digitalWrite(dispPins[disp*8 + 2],LOW);
    digitalWrite(dispPins[disp*8 + 3],LOW);
    digitalWrite(dispPins[disp*8 + 4],(disp == 1 || disp == 3);
    digitalWrite(dispPins[disp*8 + 5],HIGH);
    digitalWrite(dispPins[disp*8 + 6],LOW);
    digitalWrite(dispPins[disp*8 + 7],LOW);
  } else if (val == 2) {
    digitalWrite(dispPins[disp*8 + 0],HIGH);
    digitalWrite(dispPins[disp*8 + 1],HIGH);
    digitalWrite(dispPins[disp*8 + 2],LOW);
    digitalWrite(dispPins[disp*8 + 3],HIGH);
    digitalWrite(dispPins[disp*8 + 4],(disp == 1 || disp == 3);
    digitalWrite(dispPins[disp*8 + 5],LOW);
    digitalWrite(dispPins[disp*8 + 6],HIGH);
    digitalWrite(dispPins[disp*8 + 7],HIGH);
  } else if (val == 3) {
    digitalWrite(dispPins[disp*8 + 0],HIGH);
    digitalWrite(dispPins[disp*8 + 1],HIGH);
    digitalWrite(dispPins[disp*8 + 2],LOW);
    digitalWrite(dispPins[disp*8 + 3],HIGH);
    digitalWrite(dispPins[disp*8 + 4],(disp == 1 || disp == 3);
    digitalWrite(dispPins[disp*8 + 5],HIGH);
    digitalWrite(dispPins[disp*8 + 6],HIGH);
    digitalWrite(dispPins[disp*8 + 7],LOW);
  } else if (val == 4) {
    digitalWrite(dispPins[disp*8 + 0],HIGH);
    digitalWrite(dispPins[disp*8 + 1],LOW);
    digitalWrite(dispPins[disp*8 + 2],HIGH);
    digitalWrite(dispPins[disp*8 + 3],HIGH);
    digitalWrite(dispPins[disp*8 + 4],(disp == 1 || disp == 3);
    digitalWrite(dispPins[disp*8 + 5],HIGH);
    digitalWrite(dispPins[disp*8 + 6],LOW);
    digitalWrite(dispPins[disp*8 + 7],LOW);
  } else if (val == 5) {
    digitalWrite(dispPins[disp*8 + 0],LOW);
    digitalWrite(dispPins[disp*8 + 1],HIGH);
    digitalWrite(dispPins[disp*8 + 2],HIGH);
    digitalWrite(dispPins[disp*8 + 3],HIGH);
    digitalWrite(dispPins[disp*8 + 4],(disp == 1 || disp == 3);
    digitalWrite(dispPins[disp*8 + 5],HIGH);
    digitalWrite(dispPins[disp*8 + 6],HIGH);
    digitalWrite(dispPins[disp*8 + 7],LOW);
  } else if (val == 6) {
    digitalWrite(dispPins[disp*8 + 0],LOW);
    digitalWrite(dispPins[disp*8 + 1],HIGH);
    digitalWrite(dispPins[disp*8 + 2],HIGH);
    digitalWrite(dispPins[disp*8 + 3],HIGH);
    digitalWrite(dispPins[disp*8 + 4],(disp == 1 || disp == 3);
    digitalWrite(dispPins[disp*8 + 5],HIGH);
    digitalWrite(dispPins[disp*8 + 6],HIGH);
    digitalWrite(dispPins[disp*8 + 7],HIGH);
  } else if (val == 7) {
    digitalWrite(dispPins[disp*8 + 0],HIGH);
    digitalWrite(dispPins[disp*8 + 1],HIGH);
    digitalWrite(dispPins[disp*8 + 2],LOW);
    digitalWrite(dispPins[disp*8 + 3],LOW);
    digitalWrite(dispPins[disp*8 + 4],(disp == 1 || disp == 3);
    digitalWrite(dispPins[disp*8 + 5],HIGH);
    digitalWrite(dispPins[disp*8 + 6],LOW);
    digitalWrite(dispPins[disp*8 + 7],LOW);
  } else if (val == 8) {
    digitalWrite(dispPins[disp*8 + 0],HIGH);
    digitalWrite(dispPins[disp*8 + 1],HIGH);
    digitalWrite(dispPins[disp*8 + 2],HIGH);
    digitalWrite(dispPins[disp*8 + 3],HIGH);
    digitalWrite(dispPins[disp*8 + 4],(disp == 1 || disp == 3);
    digitalWrite(dispPins[disp*8 + 5],HIGH);
    digitalWrite(dispPins[disp*8 + 6],HIGH);
    digitalWrite(dispPins[disp*8 + 7],HIGH);
  } else if (val == 9) {
    digitalWrite(dispPins[disp*8 + 0],HIGH);
    digitalWrite(dispPins[disp*8 + 1],HIGH);
    digitalWrite(dispPins[disp*8 + 2],HIGH);
    digitalWrite(dispPins[disp*8 + 3],HIGH);
    digitalWrite(dispPins[disp*8 + 4],(disp == 1 || disp == 3);
    digitalWrite(dispPins[disp*8 + 5],HIGH);
    digitalWrite(dispPins[disp*8 + 6],HIGH);
    digitalWrite(dispPins[disp*8 + 7],LOW);
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
