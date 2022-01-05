int randNum = 0;
int Aj = 0;

void setup() {
  pinMode(5,OUTPUT);
  randomSeed(analogRead(0));
}

void loop() {
  randNum = random(0,1000);
  Aj = random(0,1000);
  tone(5,Aj);
  delay(randNum);
}
