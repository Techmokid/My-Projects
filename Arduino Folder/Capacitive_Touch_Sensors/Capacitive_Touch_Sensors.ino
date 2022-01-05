#include <CapacitiveButtonRead.h>

CapacitiveButtonRead myLib;

void setup() {
  Serial.begin(9600);
  Serial.println("\n\nSerial COnnection Established");
  Serial.println();
  delay(2000);
}

void loop() {
  String sentence = String(myLib.ReadPin2()) + "|" + String(myLib.ReadPin3()) + "|" + String(myLib.ReadPin4()) + "|" + String(myLib.ReadPin5()) + "|" + String(myLib.ReadPin6()) + "|" + String(myLib.ReadPin7()) + "|" + String(myLib.ReadPin8()) + "|" + String(myLib.ReadPin9()) + "|" + String(myLib.ReadPin10()) + "|" + String(myLib.ReadPin11()) + "|" + String(myLib.ReadPin12()) + "|" + String(myLib.ReadPin13());
  Serial.println(sentence);
}
