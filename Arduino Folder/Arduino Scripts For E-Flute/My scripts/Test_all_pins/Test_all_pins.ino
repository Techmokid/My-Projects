int pin = 2;
int loops = 2;

void setup(){
  while(loops < 14){
    while (pin < 14){
      digitalWrite(pin,HIGH);
      delay(250);
      pin = pin + 1;
    }
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
    pin = loops;
    loops = loops + 1;
  }
}

void loop(){
  
}

