#include <EEPROM.h>

void setup() {
  Serial.begin(9600);
  while (!Serial) { }
  delay(100);
  Serial.println();
  
  EEPROM_Writer("CONFIG:0:40:cm");
  EEPROM_Writer("CONFIG:1:22:cm");
  EEPROM_Writer("CONFIG:2:7.6:cm");
  EEPROM_Writer("CONFIG:3:4.625:cm");
  EEPROM_Writer("CONFIG:4:14.5:mm"); EEPROM_Reader();
}

String getValue(String data, char separator, int index) {
    int found = 0; int strIndex[] = { 0, -1 }; int maxIndex = data.length() - 1;
    for (int i = 0; i <= maxIndex && found <= index; i++) { if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
    } } return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void EEPROM_Writer(String in) {
  in = in.substring(in.indexOf(':') + 1,in.length());
  if (in[in.length()-1] == '\n') { in.remove(in.length()-1); }
  
  int key      = getValue(in,':',0).toInt(); if (key > 7) { return; } //Invalid key
  float val    = getValue(in,':',1).toFloat();
  String units = getValue(in,':',2);
  
  if (units == "m") { val *= 1000; }
  if (units == "cm") { val *= 10; }
  
  int eeAddress = sizeof(float) * key;
  writeValueToEEPROM(eeAddress,val);
  
  Serial.println("Saved " + String(val) + " to EEPROM address \"" + String(key) + "\"" + " at position \"" + String(eeAddress) + "\"");
  return;
}

void EEPROM_Reader() {
  Serial.println("-----------------------------------------------------------------");
  for (int i = 0; i < 5; i++) {
    int eeAddress = sizeof(float) * i;
    float temp = readValueFromEEPROM(eeAddress);
    Serial.println("Value: " + String(temp) + " found at address " + String(i) + " at position " + String(eeAddress));
  }
  
  Serial.println("EEPROM Reader Finished");
  return;
}

float readValueFromEEPROM(int addr) {
  float in = 0.00;
  EEPROM.begin(512);
  EEPROM.get(addr, in);
  EEPROM.commit();
  EEPROM.end();
  return in;
}

void writeValueToEEPROM(int addr,float val) {
  EEPROM.begin(512);
  EEPROM.put(addr,val);
  EEPROM.end();
}

void loop() {}
