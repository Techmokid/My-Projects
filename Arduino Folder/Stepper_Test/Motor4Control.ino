void stepLeft4() {
  position4++;
  if (position4==9) {position4=1;}
  updatePosition4();
}

void stepRight4() {
  position4--;
  if (position4==0) {position4=8;}
  updatePosition4();
}

void updatePosition4() {
  if (position4 == 1) {
    digitalWrite(motor4Pin1,HIGH);
    digitalWrite(motor4Pin2,LOW);
    digitalWrite(motor4Pin3,LOW);
    digitalWrite(motor4Pin4,LOW);
  } else if (position4 == 2) {
    digitalWrite(motor4Pin1,HIGH);
    digitalWrite(motor4Pin2,LOW);
    digitalWrite(motor4Pin3,HIGH);
    digitalWrite(motor4Pin4,LOW);
  } else if (position4 == 3) {
    digitalWrite(motor4Pin1,LOW);
    digitalWrite(motor4Pin2,LOW);
    digitalWrite(motor4Pin3,HIGH);
    digitalWrite(motor4Pin4,LOW);
  } else if (position4 == 4) {
    digitalWrite(motor4Pin1,LOW);
    digitalWrite(motor4Pin2,HIGH);
    digitalWrite(motor4Pin3,HIGH);
    digitalWrite(motor4Pin4,LOW);
  } else if (position4 == 5) {
    digitalWrite(motor4Pin1,LOW);
    digitalWrite(motor4Pin2,HIGH);
    digitalWrite(motor4Pin3,LOW);
    digitalWrite(motor4Pin4,LOW);
  } else if (position4 == 6) {
    digitalWrite(motor4Pin1,LOW);
    digitalWrite(motor4Pin2,HIGH);
    digitalWrite(motor4Pin3,LOW);
    digitalWrite(motor4Pin4,HIGH);
  } else if (position4 == 7) {
    digitalWrite(motor4Pin1,LOW);
    digitalWrite(motor4Pin2,LOW);
    digitalWrite(motor4Pin3,LOW);
    digitalWrite(motor4Pin4,HIGH);
  } else if (position4 == 8) {
    digitalWrite(motor4Pin1,HIGH);
    digitalWrite(motor4Pin2,LOW);
    digitalWrite(motor4Pin3,LOW);
    digitalWrite(motor4Pin4,HIGH);
  }
}
