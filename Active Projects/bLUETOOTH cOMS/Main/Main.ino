//AT+INIT
//AT+INQ
//delay(10000);
//AT+INQC

#define mySerial Serial1

void setup() {
  Serial.begin(38400);
  mySerial.begin(38400);
  delay(1000);
  
  setATModeToTransmitter("Test Bluetooth Transmition Node",true);
  while(mySerial.available() > 0) { Serial.print(char(mySerial.read())); }
  //while(mySerial.available() > 0) { mySerial.read(); }
}

void loop() { }

void setATModeToReceiever(String name, bool reset) {
  name = makeStringSafe(name);
  sendATCommand("AT");
  sendATCommand("AT");
  sendATCommand("AT+ORGL");
  sendATCommand("AT+RMAAD");
  sendATCommand("AT+CMODE=0");
  sendATCommand("AT+NAME=\"" + name + "\"");
  sendATCommand("AT+ADDR?");
  if (reset) sendATCommand("AT+RESET");
}

void setATModeToTransmitter(String name, bool reset) { setATModeToTransmitter(name, reset, ""); }
void setATModeToTransmitter(String name, bool reset, String bindAddress) {
  name = makeStringSafe(name);
  sendATCommand("AT");
  sendATCommand("AT+ORGL");
  sendATCommand("AT+RMAAD");
  sendATCommand("AT+NAME=\"" + name + "\"");
  //sendATCommand("AT+ROLE=1");
  sendATCommand("AT+CMODE=1");
  if (bindAddress != "") { sendATCommand("AT+BIND=" + bindAddress); }
  
  sendATCommand("AT+ADDR?");
  if (reset) sendATCommand("AT+RESET");
}

void sendATCommand(String command) { mySerial.print(command + "\r\n"); delay(200); }

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
