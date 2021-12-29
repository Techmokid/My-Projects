boolean analog = true;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (analog == false) {
  Serial.print(" DIGITAL ");
  Serial.print(digitalRead(0));
  Serial.print(" ");
  Serial.print(digitalRead(2));
  Serial.print(" ");
  Serial.print(digitalRead(3));
  Serial.print(" ");
  Serial.print(digitalRead(4));
  Serial.print(" ");
  Serial.print(digitalRead(5));
  Serial.print(" ");
  Serial.print(digitalRead(6));
  Serial.print(" ");
  Serial.print(digitalRead(7));
  Serial.print(" ");
  Serial.print(digitalRead(8));
  Serial.print(" ");
  Serial.print(digitalRead(9));
  Serial.print(" ");
  Serial.print(digitalRead(10));
  Serial.print(" ");
  Serial.print(digitalRead(11));
  Serial.print(" ");
  Serial.println(digitalRead(12));
  } else {
  Serial.print(" ANALOG ");
  Serial.print(analogRead(0));
  Serial.print(" ");
  Serial.print(analogRead(2));
  Serial.print(" ");
  Serial.print(analogRead(3));
  Serial.print(" ");
  Serial.print(analogRead(4));
  Serial.print(" ");
  Serial.print(analogRead(5));
  Serial.print(" ");
  Serial.print(analogRead(6));
  Serial.print(" ");
  Serial.print(analogRead(7));
  Serial.print(" ");
  Serial.print(analogRead(8));
  Serial.print(" ");
  Serial.print(analogRead(9));
  Serial.print(" ");
  Serial.print(analogRead(10));
  Serial.print(" ");
  Serial.print(analogRead(11));
  Serial.print(" ");
  Serial.println(analogRead(12));
  }
  Serial.println();
}
