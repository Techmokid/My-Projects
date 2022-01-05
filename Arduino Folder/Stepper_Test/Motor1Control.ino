void stepLeft1() {
  position1++;
  if (position1==9) {position1=1;}
  updatePosition1();
}

void stepRight1() {
  position1--;
  if (position1==0) {position1=8;}
  updatePosition1();
}

void updatePosition1() {
  if (position1 == 1) {
    digitalWrite(motor1Pin1,HIGH);
    digitalWrite(motor1Pin2,LOW);
    digitalWrite(motor1Pin3,LOW);
    digitalWrite(motor1Pin4,LOW);
  } else if (position1 == 2) {
    digitalWrite(motor1Pin1,HIGH);
    digitalWrite(motor1Pin2,LOW);
    digitalWrite(motor1Pin3,HIGH);
    digitalWrite(motor1Pin4,LOW);
  } else if (position1 == 3) {
    digitalWrite(motor1Pin1,LOW);
    digitalWrite(motor1Pin2,LOW);
    digitalWrite(motor1Pin3,HIGH);
    digitalWrite(motor1Pin4,LOW);
  } else if (position1 == 4) {
    digitalWrite(motor1Pin1,LOW);
    digitalWrite(motor1Pin2,HIGH);
    digitalWrite(motor1Pin3,HIGH);
    digitalWrite(motor1Pin4,LOW);
  } else if (position1 == 5) {
    digitalWrite(motor1Pin1,LOW);
    digitalWrite(motor1Pin2,HIGH);
    digitalWrite(motor1Pin3,LOW);
    digitalWrite(motor1Pin4,LOW);
  } else if (position1 == 6) {
    digitalWrite(motor1Pin1,LOW);
    digitalWrite(motor1Pin2,HIGH);
    digitalWrite(motor1Pin3,LOW);
    digitalWrite(motor1Pin4,HIGH);
  } else if (position1 == 7) {
    digitalWrite(motor1Pin1,LOW);
    digitalWrite(motor1Pin2,LOW);
    digitalWrite(motor1Pin3,LOW);
    digitalWrite(motor1Pin4,HIGH);
  } else if (position1 == 8) {
    digitalWrite(motor1Pin1,HIGH);
    digitalWrite(motor1Pin2,LOW);
    digitalWrite(motor1Pin3,LOW);
    digitalWrite(motor1Pin4,HIGH);
  }
}
