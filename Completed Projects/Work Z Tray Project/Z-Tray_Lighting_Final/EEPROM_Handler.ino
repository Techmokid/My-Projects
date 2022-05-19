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
  
  int key      = getValue(in,':',0).toInt(); //if (key > 10) { return; } //Invalid key
  float val    = getValue(in,':',1).toFloat();
  String units = getValue(in,':',2);
  
  if (units == "M") { val *= 1000; }
  if (units == "CM") { val *= 10; }
  
  writeValueToEEPROM(key,val);
  
  Serial.println("Saved " + String(val,4) + " to EEPROM address \"" + String(key) + "\"");
  client.println("Saved " + String(val,4) + " to EEPROM address \"" + String(key) + "\"");
  delay(50); return;
}

void EEPROM_Reader() {
  Serial.println("Reading EEPROM off to client");
  for (int i = 0; i < 15; i++) {
    client.println("Value: " + String(readValueFromEEPROM(i),4) + " found at address " + String(i));
  }
  
  delay(50);
  return;
}

float readValueFromEEPROM(int addr) {
  float in = 0.00;
  EEPROM.begin(512);
  EEPROM.get(sizeof(float)*addr, in);
  EEPROM.commit();
  EEPROM.end();
  return in;
}

void writeValueToEEPROM(int addr,float val) {
  EEPROM.begin(512);
  EEPROM.put(sizeof(float)*addr,val);
  EEPROM.end();
}
