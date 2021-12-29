int cheese = 0;
int reader = 0;

void setup() {
}

void loop() {
  reader = analogRead(A0);
  tone(2,cheese);
  delay(reader);
  cheese = cheese + 1;
}
