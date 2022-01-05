int Mic = 0;

void setup() {
  pinMode(A0,INPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(Mic);
  Mic = analogRead(A0);
  if (Mic == 0) {
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
  }
  if (Mic > 1020) {
    digitalWrite(3,HIGH);
    digitalWrite(2,LOW);
    digitalWrite(4,LOW);
  }
  if (Mic > 2) {
    if (Mic < 1021) {
      digitalWrite(2,LOW);
      digitalWrite(3,LOW);
      digitalWrite(4,HIGH);
    }
  }
}
