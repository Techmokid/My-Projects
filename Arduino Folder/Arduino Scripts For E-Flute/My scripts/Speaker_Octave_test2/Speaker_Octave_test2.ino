int pin = 2;
int Delay = 50;
int data = 0;

void setup() {
  pinMode (2,OUTPUT);
}

void loop() {
  data = digitalRead(3);
  if (data == 1) {
  Delay = analogRead(0);
  tone(pin,262);
  delay(Delay);
  Delay = analogRead(0);
  tone(pin,311);
  delay(Delay);
  Delay = analogRead(0);
  tone(pin,392);
  delay(Delay);
  Delay = analogRead(0);
  tone(pin,523);
  delay(Delay);
  Delay = analogRead(0);
  tone(pin,622);
  delay(Delay);
  Delay = analogRead(0);
  tone(pin,784);
  delay(Delay);
  Delay = analogRead(0);
  tone(pin,1047);
  delay(Delay);
  Delay = analogRead(0);
  tone(pin,1245);
  delay(Delay);
  Delay = analogRead(0);
  tone(pin,1568);
  delay(Delay);
  Delay = analogRead(0);
  tone(pin,2093);
  delay(Delay);
  }
  noTone(2);
}
