#include <EEPROM.h>

void setup() {
  Serial.begin(115200);
  EEPROM_Handler("CONFIG:0:40:cm");  Serial.println();
  EEPROM_Handler("CONFIG:1:22:cm");  Serial.println();
  EEPROM_Handler("CONFIG:2:213:cm"); Serial.println();
  EEPROM_Handler("CONFIG:3:185:cm"); Serial.println();
}

void loop() { }

String getValue(String data, char separator, int index) {
    int found = 0; int strIndex[] = { 0, -1 }; int maxIndex = data.length() - 1;
    for (int i = 0; i <= maxIndex && found <= index; i++) { if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
    } } return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void EEPROM_Handler(String in) {
  in = in.substring(in.indexOf(':') + 1,in.length());
  if (in[in.length()-1] == '\n') { in.remove(in.length()-1); }
  
  int key      = getValue(in,':',0).toInt(); if (key > 7) { return; } //Invalid key
  float val    = getValue(in,':',1).toFloat();
  String units = getValue(in,':',2);
  
  if (units == "m") { val *= 1000; }
  if (units == "cm") { val *= 10; }
  
  EEPROM.put(key,val);
}
