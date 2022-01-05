void setup() {
  pinMode(12,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(2)==0) {
    digitalWrite(12,LOW);
  } else {
    digitalWrite(12,HIGH);
  }
}
