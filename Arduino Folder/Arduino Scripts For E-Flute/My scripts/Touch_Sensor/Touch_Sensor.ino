int Mic = 0;

void setup() {
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
}

void loop() {
  Mic = digitalRead(2);
  if (Mic == 1) {
    digitalWrite(3,HIGH);
  }
  if (Mic == 0) {
    digitalWrite(3,LOW);
  }
}
