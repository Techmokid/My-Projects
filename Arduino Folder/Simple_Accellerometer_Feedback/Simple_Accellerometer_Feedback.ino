String sentence = "";
int x = 0;
int y = 0;
int z = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  x = analogRead(0);
  y = analogRead(1);
  z = analogRead(2);
  
  sentence = "X: " + String(x);
  sentence += "\tY: " + String(y);
  sentence += "\tZ: " + String(z);
  
  Serial.println(sentence);
  delay (50);
}
