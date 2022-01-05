int serial = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(200);
  serial = digitalRead(A1);
  if (serial == 1) {
    Serial.println("Button 1  has been pressed (C)");
  }
  serial = digitalRead(2);
  if (serial == 1) {
    Serial.println("Button 2  has been pressed (A)");
  }
  serial = digitalRead(3);
  if (serial == 1) {
    Serial.println("Button 3  has been pressed (G)");
  }
  serial = digitalRead(4);
  if (serial == 1) {
    Serial.println("Button 4  has been pressed (F)");
  }
  serial = digitalRead(5);
  if (serial == 1) {
    Serial.println("Button 5  has been pressed (E)");
  }
  serial = digitalRead(6);
  if (serial == 1) {
    Serial.println("Button 6  has been pressed (D)");
  }
  serial = digitalRead(7);
  if (serial == 1) {
    Serial.println("Button 7  has been pressed (E Flat)");
  }
  serial = digitalRead(8);
  if (serial == 1) {
    Serial.println("Button 8  has been pressed (Low C)");
  }
  serial = digitalRead(9);
  if (serial == 1) {
    Serial.println("Button 9  has been pressed (Low C#)");
  }
  serial = digitalRead(10);
  if (serial == 1) {
    Serial.println("Button 10 has been pressed (B)");
  }
  serial = digitalRead(11);
  if (serial == 1) {
    Serial.println("Button 11 has been pressed (B Flat)");
  }
  serial = digitalRead(12);
  if (serial == 1) {
    Serial.println("Button 12 has been pressed (G# OR the banana key)");
  }
  Serial.println("");
}
