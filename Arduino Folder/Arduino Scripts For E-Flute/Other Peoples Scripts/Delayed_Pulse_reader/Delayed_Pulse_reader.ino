int timing = 0;

void setup() {
  Serial.begin(9600);
  delay(100);
  digitalWrite(2,HIGH);
  digitalWrite(13,LOW);
}

void loop() {
  delay(1);
  Serial.println(timing);
  timing = timing + 1;
  if (digitalRead(3) == 1){
    Serial.print("Timing = ");
    Serial.println(timing);
  }
  if (timing > 100){
    timing = 0;
    digitalWrite(2,LOW);
    delay(5);
    digitalWrite(2,HIGH);
  }
}
