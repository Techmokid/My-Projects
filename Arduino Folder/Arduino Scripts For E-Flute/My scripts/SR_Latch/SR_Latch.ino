int Mic1 = 0;
int Mic2 = 0;

void setup() {
  pinMode(5,INPUT);
  pinMode(4,INPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
}

void loop() {
  Mic1 = digitalRead(4);
  Mic2 = digitalRead(5);
  if (Mic1 == 1) {
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
  }
  if (Mic2 == 1) {
    digitalWrite(3,HIGH);
    digitalWrite(2,LOW);
  }
  if (Mic1 == 0) {
    if (Mic2 == 0) {
      digitalWrite(6,LOW);
    } else {
      digitalWrite(7,HIGH);
    }
  } else {
    digitalWrite(7,HIGH);
  }
}
