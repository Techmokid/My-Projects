int randNum = 0;
int LOOP = 0;
int Aj = 0;

void setup() {
  pinMode(5,OUTPUT);
  pinMode(13,OUTPUT);
  randomSeed(analogRead(0));
}

void loop() {
  digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13,LOW);
  delay(500);
  digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13,LOW);
  delay(500);
  one();
}

void one() {
  digitalWrite(13,HIGH);
  Aj = analogRead(A0);
  LOOP = LOOP + 1;
  randNum = random(1,10);
  if (LOOP == 55) {
    LOOP = 0;
    two();
  }
  if (randNum == 1) {
    tone(5,440);
    delay(Aj);
  }
  if (randNum == 2) {
    tone(5,523);
    delay(Aj);
  }
  if (randNum == 3) {
    tone(5,587);
    delay(Aj);
  }
  if (randNum == 4) {
    tone(5,622);
    delay(Aj);
  }
  if (randNum == 5) {
    tone(5,659);
    delay(Aj);
  }
  if (randNum == 6) {
    tone(5,784);
    delay(Aj);
  }
  if (randNum == 7) {
    tone(5,880);
    delay(Aj);
  }
  if (randNum == 8) {
    noTone(5);
    delay(Aj);
  }
  if (randNum == 9) {
    noTone(5);
    delay(Aj);
  }
  one();
}

void two() {
  Aj = analogRead(A0);
  LOOP = LOOP + 1;
  randNum = random(1,10);
  if (LOOP == 27) {
    LOOP = 0;
    three();
  }
  if (randNum == 1) {
    tone(5,440);
    delay(Aj);
  }
  if (randNum == 2) {
    tone(5,523);
    delay(Aj);
  }
  if (randNum == 3) {
    tone(5,587);
    delay(Aj);
  }
  if (randNum == 4) {
    tone(5,622);
    delay(Aj);
  }
  if (randNum == 5) {
    tone(5,659);
    delay(Aj);
  }
  if (randNum == 6) {
    tone(5,784);
    delay(Aj);
  }
  if (randNum == 7) {
    tone(5,880);
    delay(Aj);
  }
  if (randNum == 8) {
    noTone(5);
    delay(Aj);
  }
  if (randNum == 9) {
    noTone(5);
    delay(Aj);
  }
  two();
}

void three() {
  Aj = analogRead(A0);
  LOOP = LOOP + 1;
  randNum = random(1,10);
  if (LOOP == 27) {
    LOOP = 0;
    four();
  }
  if (randNum == 1) {
    tone(5,440);
    delay(Aj);
  }
  if (randNum == 2) {
    tone(5,523);
    delay(Aj);
  }
  if (randNum == 3) {
    tone(5,587);
    delay(Aj);
  }
  if (randNum == 4) {
    tone(5,622);
    delay(Aj);
  }
  if (randNum == 5) {
    tone(5,659);
    delay(Aj);
  }
  if (randNum == 6) {
    tone(5,784);
    delay(Aj);
  }
  if (randNum == 7) {
    tone(5,880);
    delay(Aj);
  }
  if (randNum == 8) {
    noTone(5);
    delay(Aj);
  }
  if (randNum == 9) {
    noTone(5);
    delay(Aj);
  }
  three();
}

void four() {
  Aj = analogRead(A0);
  LOOP = LOOP + 1;
  randNum = random(1,8);
  if (LOOP == 13) {
    LOOP = 0;
    five();
  }
  if (randNum == 1) {
    tone(5,440);
    delay(Aj);
  }
  if (randNum == 2) {
    tone(5,523);
    delay(Aj);
  }
  if (randNum == 3) {
    tone(5,587);
    delay(Aj);
  }
  if (randNum == 4) {
    tone(5,622);
    delay(Aj);
  }
  if (randNum == 5) {
    tone(5,659);
    delay(Aj);
  }
  if (randNum == 6) {
    tone(5,784);
    delay(Aj);
  }
  if (randNum == 7) {
    tone(5,880);
    delay(Aj);
  }
  if (randNum == 8) {
    noTone(5);
    delay(Aj);
  }
  if (randNum == 9) {
    noTone(5);
    delay(Aj);
  }
  four();
}

void five() {
  Aj = analogRead(A0);
  LOOP = LOOP + 1;
  randNum = random(1,10);
  if (LOOP == 13) {
    LOOP = 0;
    six();
  }
  if (randNum == 1) {
    tone(5,440);
    delay(Aj);
  }
  if (randNum == 2) {
    tone(5,523);
    delay(Aj);
  }
  if (randNum == 3) {
    tone(5,587);
    delay(Aj);
  }
  if (randNum == 4) {
    tone(5,622);
    delay(Aj);
  }
  if (randNum == 5) {
    tone(5,659);
    delay(Aj);
  }
  if (randNum == 6) {
    tone(5,784);
    delay(Aj);
  }
  if (randNum == 7) {
    tone(5,880);
    delay(Aj);
  }
  if (randNum == 8) {
    noTone(5);
    delay(Aj);
  }
  if (randNum == 9) {
    noTone(5);
    delay(Aj);
  }
  five();
}

void six() {
  Aj = analogRead(A0);
  LOOP = LOOP + 1;
  randNum = random(1,10);
  if (LOOP == 27) {
    noTone(5);
    finish();
  }
  if (randNum == 1) {
    tone(5,440);
    delay(Aj);
  }
  if (randNum == 2) {
    tone(5,523);
    delay(Aj);
  }
  if (randNum == 3) {
    tone(5,587);
    delay(Aj);
  }
  if (randNum == 4) {
    tone(5,622);
    delay(Aj);
  }
  if (randNum == 5) {
    tone(5,659);
    delay(Aj);
  }
  if (randNum == 6) {
    tone(5,784);
    delay(Aj);
  }
  if (randNum == 7) {
    tone(5,880);
    delay(Aj);
  }
  if (randNum == 8) {
    noTone(5);
    delay(Aj);
  }
  if (randNum == 9) {
    noTone(5);
    delay(Aj);
  }
  six();
}

void finish() {
  digitalWrite(13,LOW);
  finish();
  LOOP = digitalRead(2);
  if (LOOP == 1) {
    one();
  }
}
