void stepLeft2() {
  position2++;
  if (position2==9) {position2=1;}
  updatePosition2();
}

void stepRight2() {
  position2--;
  if (position2==0) {position2=8;}
  updatePosition2();
}

void updatePosition2() {
  if (position2 == 1) {
    digitalWrite(motor2Pin1,HIGH);
    digitalWrite(motor2Pin2,LOW);
    digitalWrite(motor2Pin3,LOW);
    digitalWrite(motor2Pin4,LOW);
  } else if (position2 == 2) {
    digitalWrite(motor2Pin1,HIGH);
    digitalWrite(motor2Pin2,LOW);
    digitalWrite(motor2Pin3,HIGH);
    digitalWrite(motor2Pin4,LOW);
  } else if (position2 == 3) {
    digitalWrite(motor2Pin1,LOW);
    digitalWrite(motor2Pin2,LOW);
    digitalWrite(motor2Pin3,HIGH);
    digitalWrite(motor2Pin4,LOW);
  } else if (position2 == 4) {
    digitalWrite(motor2Pin1,LOW);
    digitalWrite(motor2Pin2,HIGH);
    digitalWrite(motor2Pin3,HIGH);
    digitalWrite(motor2Pin4,LOW);
  } else if (position2 == 5) {
    digitalWrite(motor2Pin1,LOW);
    digitalWrite(motor2Pin2,HIGH);
    digitalWrite(motor2Pin3,LOW);
    digitalWrite(motor2Pin4,LOW);
  } else if (position2 == 6) {
    digitalWrite(motor2Pin1,LOW);
    digitalWrite(motor2Pin2,HIGH);
    digitalWrite(motor2Pin3,LOW);
    digitalWrite(motor2Pin4,HIGH);
  } else if (position2 == 7) {
    digitalWrite(motor2Pin1,LOW);
    digitalWrite(motor2Pin2,LOW);
    digitalWrite(motor2Pin3,LOW);
    digitalWrite(motor2Pin4,HIGH);
  } else if (position2 == 8) {
    digitalWrite(motor2Pin1,HIGH);
    digitalWrite(motor2Pin2,LOW);
    digitalWrite(motor2Pin3,LOW);
    digitalWrite(motor2Pin4,HIGH);
  }
}
