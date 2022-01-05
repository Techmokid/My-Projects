#include <SPI.h>
#include <SD.h>

File file;

void setup() {
  Serial.begin(9600);
  if (!SD.begin()) {
    Serial.println("begin failed");
    return;
  }
  file = SD.open("TEST_SD.TXT", FILE_WRITE);
  file.println("Arduino Uno R3 Board: Hello from virtual reality!");
  file.close();
  Serial.println("Done");
}

void loop() {}
