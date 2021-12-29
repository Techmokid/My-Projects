void setup() {
  Serial.begin(9600);
}

void loop() {
  float voltage = analogRead(A0) * (5.0 / 1023.0);
  Serial.println(String(voltage * 10 * 1.096) + " volts");
}
