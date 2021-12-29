#include <APGameBoard.h>

APGameBoard ap;

void setup() {
  Serial.begin(9600);
  pinMode(A2,INPUT_PULLUP);
  pinMode(A3,INPUT_PULLUP);
  pinMode(A4,INPUT_PULLUP);
  pinMode(A5,INPUT_PULLUP);
}

void loop() {
  Serial.print(analogRead(A2) - 553);
  Serial.print(" ");
  Serial.print(analogRead(A3) - 547);
  Serial.print(" ");
  Serial.print(analogRead(A4) - 686);
  Serial.print(" ");
  Serial.println(analogRead(A5) - 694);
}
