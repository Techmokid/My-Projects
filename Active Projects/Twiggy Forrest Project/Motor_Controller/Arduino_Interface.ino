void setupCom() {
  pinMode(COM_PIN_1,OUTPUT);
  pinMode(COM_PIN_2,OUTPUT);
  pinMode(COM_PIN_3,OUTPUT);
  digitalWrite(COM_PIN_1,HIGH);
  digitalWrite(COM_PIN_2,LOW);
  digitalWrite(COM_PIN_3,LOW);
}

void talkToServerInterfaceArduino(String msg) {
  if (msg == "Online") {
    digitalWrite(COM_PIN_2,LOW);
    digitalWrite(COM_PIN_3,LOW);
  } else if (msg == "Fixing Clog") {
    digitalWrite(COM_PIN_2,HIGH);
    digitalWrite(COM_PIN_3,LOW);
  } else if (msg == "Clogged") {
    digitalWrite(COM_PIN_2,LOW);
    digitalWrite(COM_PIN_3,HIGH);
  } else if (msg == "Full") {
    digitalWrite(COM_PIN_2,HIGH);
    digitalWrite(COM_PIN_3,HIGH);
  }
}