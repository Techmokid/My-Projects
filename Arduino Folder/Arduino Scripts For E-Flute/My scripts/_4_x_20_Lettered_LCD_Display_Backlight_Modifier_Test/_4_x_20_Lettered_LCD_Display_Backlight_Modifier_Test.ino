void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("LCD Off");
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  delay(1500);

  Serial.println("LCD on Low");
  digitalWrite(2,HIGH);
  delay(1500);

  Serial.println("LCD on High");
  digitalWrite(3,HIGH);
  delay(1500);

  Serial.println();
}
