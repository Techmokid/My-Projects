int numbers = 0;

void setup() {
  Serial.begin(9600);
  digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13,LOW);
}

void loop() {
  numbers = Serial.read();

  if(numbers = 'A'){
    digitalWrite(13,HIGH);
  }
  if(numbers = 'B'){
    digitalWrite(13,LOW);
  }
}
