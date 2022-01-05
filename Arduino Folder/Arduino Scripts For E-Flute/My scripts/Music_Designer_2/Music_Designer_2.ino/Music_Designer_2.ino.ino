int count = 0;
int randNum = 0;
int Aj = 0;

void setup() {
  pinMode(5,OUTPUT);
  pinMode(13,OUTPUT);
  randomSeed(analogRead(0));
  Serial.begin(9600);
}

void loop() {
  count = count + 1;
  digitalWrite(13,HIGH);
  Aj = analogRead(A0);
  randNum = random(1,10);
  Serial.print(randNum);
  if (count == 181) {
    Serial.println("");
    count = 0;
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
  Stir();
}

void Stir() {
  digitalWrite(13,LOW);
  noTone(5);
  Aj = digitalRead(2);
  if (Aj > 0) {
    loop();
  } else {
    Stir();
  }
}
