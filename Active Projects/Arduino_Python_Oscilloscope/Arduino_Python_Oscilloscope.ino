void setup() {
  Serial.begin(115200);
}

void loop() {
  float in1 = analogRead(0);
  float in2 = analogRead(1);
  Serial.println(in1+in2);
}
