int pausetime = 100;
int pin = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("D0-13 = ");
  
  while(pin < 14) {
    Serial.print(digitalRead(pin));
    Serial.print(" ");
    pin = pin + 1;
  }

  pin = 0;
  
  Serial.print("                    A0-5 = ");
  
  while(pin < 6) {
    Serial.print(analogRead(pin));
    Serial.print(" ");
    pin = pin + 1;
  }

  pin = 0;
  Serial.println();
  delay(pausetime);
}
