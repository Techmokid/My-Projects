char var[] = {""};
const int chipSelect = 4;

void setup() {
  Serial.begin(9600);
  Serial.print("arduino.test0");
  Serial.print("w0");
  Serial.print("This is a test from the arduino IDE test program0");
  delay(2000);
  Serial.print("arduino.test0");
  Serial.print("a0");
  Serial.print("This is also a test from thhe arduino IDE0");
  delay(2000);
  Serial.print("arduino.test0");
  Serial.print("r0");
}

void loop() {
}
