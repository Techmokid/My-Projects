#define M_E 2.7182818284590452354

int Sound = 0;
int calibration = 0;
int FA = 0;
int FB = 0;
int FC = 0;
int FD = 0;
int FE = 0;
int FF = 0;
int FG = 0;
int FH = 0;
int led1 = 0;
int led2 = 0;
float Freq = 0.00;
float HandA = 0.00;
float HandB = 0.00;

void setup() {
  
}

void loop() {
  led1 = digitalRead(A3);
  led2 = digitalRead(A5);
  if (led1 == 1){
    Sound = analogRead(A0);
    calibration = analogRead(A1);
    if (Sound < calibration){
    HandA = 0;
    HandB = 0;
    FA = digitalRead(0);
    FB = digitalRead(2);
    FC = digitalRead(3);
    FD = digitalRead(4);
    FE = digitalRead(5);
    FF = digitalRead(6);
    FG = digitalRead(7);
    FH = digitalRead(8);
    if (FA = 1) {
      HandA = HandA + 1;
    }
    if (FB = 1) {
      HandA = HandA + 2;
    }
    if (FC = 1) {
      HandA = HandA + 4;
    }
    if (FD = 1) {
      HandA = HandA + 8;
    }
    if (FE = 1) {
      HandB = HandB + 1;
    }
    if (FF = 1) {
      HandB = HandB + 2;
    }
    if (FG = 1) {
      HandB = HandB + 4;
    }
    if (FH = 1) {
      HandB = HandB + 8;
    }
    if (HandA > 12) {
      HandA = 0;
      HandB = 0;
    }
    if (HandA < 1) {
      HandA = 0;
      HandB = 0;
    }
    if (HandB < 1) {
      HandA = 0;
      HandB = 0;
    }
    HandB = (HandB * 12) + HandA;
    Freq = 8.1757989 * pow(M_E,0.0577622 * HandB);
    if (HandA != 0) {
      if (HandB != 0) {
        tone(13,Freq);
      } else{
        noTone(13);
      }
    } else {
     noTone(13);
    }
    } else {
      noTone(13);
    }
  } else {
    if (led2 == 1){
      tone(13,10);
    } else {
      digitalWrite(11,HIGH);
      tone(13,9);
      delay(500);
      digitalWrite(12,HIGH);
      digitalWrite(11,LOW);
      noTone(13);
      delay(500);
      digitalWrite(12,LOW);
    }
  }
}
