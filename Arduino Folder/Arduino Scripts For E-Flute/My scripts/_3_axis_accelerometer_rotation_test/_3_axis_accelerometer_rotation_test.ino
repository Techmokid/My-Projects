int x = 0;
int y = 0;
int z = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  x = round(analogRead(A2)/10);
  y = round(analogRead(A3)/10);
  z = round(analogRead(A4)/10);
  String sentence = "x = " + String(x) + " \t\ty = " + String(y) + "\t\tz = " + String(z);
  Serial.println(sentence);
}
