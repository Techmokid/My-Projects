int serial = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  serial = Serial.parseInt();
  Serial.println(serial);
}
