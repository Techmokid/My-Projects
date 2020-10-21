//AT+INIT
//AT+INQ
//delay(10000);
//AT+INQC

void setup() {
  Serial.begin(38400);
  Serial1.begin(38400);
  delay(1000);
  
  setATModeToReceiever("Test Bluetooth Transmition Node",true);
  //while(Serial1.available() > 0) { Serial.print(char(Serial1.read())); }
  while(Serial1.available() > 0) { Serial1.read(); }
}

void loop() { }

void setATModeToReceiever(String name, bool reset) {
  name = makeStringSafe(name);
  sendATCommand("AT");
  sendATCommand("AT");
  sendATCommand("AT+ORGL");
  sendATCommand("AT+RMAAD");
  sendATCommand("AT+CLASS=0");
  sendATCommand("AT+NAME=\"" + name + "\"");
  sendATCommand("AT+ADDR?");
  if (reset) sendATCommand("AT+RESET");
}

void setATModeToTransmitter(String name, bool reset) {
  name = makeStringSafe(name);
  sendATCommand("AT");
  sendATCommand("AT+ORGL");
  sendATCommand("AT+RMAAD");
  sendATCommand("AT+NAME=\"" + name + "\"");
  sendATCommand("AT+ROLE=1");
  sendATCommand("AT+ADDR?");
  if (reset) sendATCommand("AT+RESET");
}

void sendATCommand(String command) { Serial1.print(command + "\r\n"); delay(200); }

String makeStringSafe(String in) {
  String out = "";
  for (int i = 0; i<in.length(); i++) {
    int val = (int)in[i];
    if (valueIsBetween(val,48,57) || valueIsBetween(val,65,90) || valueIsBetween(val,97,122) || (val == 32)) {
      out += char(in[i]);
    }
  }

  return out;
}

bool valueIsBetween(int testing, int lower, int upper) { return ((testing <= upper) && (testing >= lower)); }
