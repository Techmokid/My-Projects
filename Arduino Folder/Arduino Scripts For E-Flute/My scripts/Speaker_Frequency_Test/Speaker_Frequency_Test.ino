int gap = 0;
long sounda = 0;
long soundb = 0;

void setup() {
}

void loop() {
  tone(2,sounda);
  sounda = sounda + 1;
  delay(gap);
  noTone(2);
  tone(3,soundb);
  soundb = sounda - 2000;
  delay(gap);
  noTone(3);
}
