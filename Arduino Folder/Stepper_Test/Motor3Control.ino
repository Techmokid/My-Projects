void stepLeft3() {
  position3++;
  if (position3==9) {position3=1;}
  updatePosition3();
}

void stepRight3() {
  position3--;
  if (position3==0) {position3=8;}
  updatePosition3();
}

void updatePosition3() {
  if (position3 == 1) {
    digitalWrite(motor3Pin1,HIGH);
    digitalWrite(motor3Pin2,LOW);
    digitalWrite(motor3Pin3,LOW);
    digitalWrite(motor3Pin4,LOW);
  } else if (position3 == 2) {
    digitalWrite(motor3Pin1,HIGH);
    digitalWrite(motor3Pin2,LOW);
    digitalWrite(motor3Pin3,HIGH);
    digitalWrite(motor3Pin4,LOW);
  } else if (position3 == 3) {
    digitalWrite(motor3Pin1,LOW);
    digitalWrite(motor3Pin2,LOW);
    digitalWrite(motor3Pin3,HIGH);
    digitalWrite(motor3Pin4,LOW);
  } else if (position3 == 4) {
    digitalWrite(motor3Pin1,LOW);
    digitalWrite(motor3Pin2,HIGH);
    digitalWrite(motor3Pin3,HIGH);
    digitalWrite(motor3Pin4,LOW);
  } else if (position3 == 5) {
    digitalWrite(motor3Pin1,LOW);
    digitalWrite(motor3Pin2,HIGH);
    digitalWrite(motor3Pin3,LOW);
    digitalWrite(motor3Pin4,LOW);
  } else if (position3 == 6) {
    digitalWrite(motor3Pin1,LOW);
    digitalWrite(motor3Pin2,HIGH);
    digitalWrite(motor3Pin3,LOW);
    digitalWrite(motor3Pin4,HIGH);
  } else if (position3 == 7) {
    digitalWrite(motor3Pin1,LOW);
    digitalWrite(motor3Pin2,LOW);
    digitalWrite(motor3Pin3,LOW);
    digitalWrite(motor3Pin4,HIGH);
  } else if (position3 == 8) {
    digitalWrite(motor3Pin1,HIGH);
    digitalWrite(motor3Pin2,LOW);
    digitalWrite(motor3Pin3,LOW);
    digitalWrite(motor3Pin4,HIGH);
  }
}
