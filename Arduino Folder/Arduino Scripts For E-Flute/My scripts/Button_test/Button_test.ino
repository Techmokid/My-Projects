int Mic = 0;

void setup() {Serial.begin(9600);}

void loop() {
  Mic = digitalRead(2);
  Serial.println(Mic);
}
