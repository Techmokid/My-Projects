#include "Python.h"
#include <Arduino.h>

void Python::writeLine(String dataToWrite) { Serial.println(dataToWrite); }

String Python::readLine() {
  String result;
  char temp = char(Serial.read());
  
  while (temp != '\n') {
    if (temp > 0) { result += temp; }
    temp = char(Serial.read());
  }
  
  return result;
}