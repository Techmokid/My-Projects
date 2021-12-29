long randNumber = 0;
int Loop = 0;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  randNumber = random(0,2);
  Serial.print(randNumber);
  Loop = Loop + 1;
  if (Loop == 20) {
    Loop = 0;
    Serial.println();
  }
}
