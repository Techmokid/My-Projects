int pin = 2;
int Delay = 400;

void setup() {
  pinMode (2,OUTPUT);
}

void loop() {
  Delay = Delay - 25;
  while(!Serial) {
    
  }
  tone(pin,262);
  delay(Delay);
  tone(pin,311);
  delay(Delay);
  tone(pin,392);
  delay(Delay);
  if (Delay == 0) {
    Delay = 400;
  }
}
