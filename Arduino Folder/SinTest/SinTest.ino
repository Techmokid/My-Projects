void setup() {
  Serial.begin(9600);
}

void loop() {
  analogWrite(0,sinCalc(6));
}

int sinCalc(float x) {
  int result = (0.5 * sin(3.14159265358979 * (2 * x - 0.5)) + 0.5) * 255;
  return result;
}
