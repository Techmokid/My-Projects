void updateSerial() {
  
}

String readLine() {
  String msg = "";
  if(Serial.available()) {
    while(true) {
      char i = Serial.read();
      if (i != '\n') {
        if (i > 20 && i < 127) {
          msg += i;
        }
      } else { return msg; }
    }
  }
  return "";
}
