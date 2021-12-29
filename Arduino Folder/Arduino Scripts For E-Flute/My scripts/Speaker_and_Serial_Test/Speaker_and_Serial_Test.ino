boolean SERA = false;
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int Delay = 0;
int Delay1 = 50;
int Delay2 = 50;
int serial = 0;

void setup() {
  pinMode(2,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (SERA == false) {
    serial = serial + 1;
    Serial.println(serial);
    tone(2,serial);
    delay(Delay);
    a = Serial.parseInt();
    if (a == 1) {
      SERA = true;
    }
  } else {
    while (Serial.available() > 0) {
      a = Serial.parseInt();
      c = Serial.parseInt();
      b = Serial.parseInt();
      d = Serial.parseInt();
      Serial.println(a);
      tone(2,-1);
    }
    Serial.print("a = ");
    Serial.println(a);
    tone(2,a);
    delay(Delay1);
    tone(2,-1);
    delay(Delay2);
    if (a == 9999) {
      SERA = false;
      serial = 0;
    }
  }
}
