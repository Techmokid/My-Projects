int Button1 = 0;
int Button2 = 0;
int Button3 = 0;
int Button4 = 0;
int Button5 = 0;
int Button6 = 0;
int Button7 = 0;
int Button8 = 0;
int Button9 = 0;
int Button10 = 0;
int Button11 = 0;
int Button12 = 0;
int MIC = 0;
int HERTZ = 0;
double e = 2.71828182846;
boolean led1 = 0;
boolean led2 = 0;

void setup() {
  pinMode(0,INPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(11,INPUT);
  pinMode(12,INPUT);
  pinMode(13,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A3,INPUT);
  pinMode(A5,INPUT);
  tone(13,90);
  delay(500);
  noTone(13);
  delay(500);
  tone(13,90);
  delay(500);
  noTone(13);
}

void loop() {
  led1 = digitalRead(A3);
  led2 = digitalRead(A5);
  MIC = analogRead(A0);
  Button1 = digitalRead(0);
  Button2 = digitalRead(2);
  Button3 = digitalRead(3);
  Button4 = digitalRead(4);
  Button5 = digitalRead(5);
  Button6 = digitalRead(6);
  Button7 = digitalRead(7);
  Button8 = digitalRead(8);
  Button9 = digitalRead(9);
  Button10 = digitalRead(10);
  Button11 = digitalRead(11);
  Button12 = digitalRead(12);
  if (led1 == true) {
  if (MIC > 700) {
  if (Button1 == LOW) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1175;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == LOW) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1175;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == LOW) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 1175;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == LOW) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1175;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == LOW) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1175;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == LOW) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 1175;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == HIGH) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == HIGH) {
  HERTZ = 1245;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == HIGH) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == HIGH) {
  HERTZ = 1245;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == HIGH) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == HIGH) {
  HERTZ = 1245;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 1397;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1397;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1397;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 1397;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1397;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1397;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1319;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1319;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 1319;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1319;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1319;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 1319;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == HIGH) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 1480;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == HIGH) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1480;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == HIGH) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1480;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == HIGH) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 1480;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == HIGH) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1480;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == HIGH) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1480;
  SDS();
  }}}}}}}}}}}}
 if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 1568;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1568;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1568;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 1568;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1568;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1568;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == HIGH) {
  HERTZ = 1661;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == HIGH) {
  HERTZ = 1661;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == HIGH) {
  HERTZ = 1661;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == HIGH) {
  HERTZ = 1661;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == HIGH) {
  HERTZ = 1661;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == HIGH) {
  HERTZ = 1661;
  SDS();
  }}}}}}}}}}}}
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == HIGH) {
  HERTZ = 1661;
  SDS();
  }}}}}}}}}}}
  if (Button1 == LOW) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 1760;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == LOW) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1760;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == LOW) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1760;
  SDS();
  }}}}}}}}}}}}
if (Button1 == LOW) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 1760;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == LOW) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1760;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == LOW) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1760;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == LOW) {
  if (Button2 == LOW) {
  if (Button3 == LOW) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1860;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == LOW) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1860;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 1976;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == LOW) {
  if (Button12 == HIGH) {
  HERTZ = 2093;
  SDS();
  }}}}}}}}}}}}
  if (MIC > 800) {
  if (Button1 == LOW) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == HIGH) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 587;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == LOW) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == HIGH) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 587;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == LOW) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == HIGH) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 587;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == LOW) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == HIGH) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 622;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == LOW) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == HIGH) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 622;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == LOW) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == HIGH) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 622;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 659;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 659;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 659;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 659;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 659;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 659;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 698;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 698;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 698;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 698;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 698;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 698;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == HIGH) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 740;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == HIGH) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 740;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == HIGH) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 740;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == HIGH) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 740;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == HIGH) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 740;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == HIGH) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 740;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 784;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 784;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 784;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 784;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 784;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 784;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == HIGH) {
  HERTZ = 831;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == HIGH) {
  HERTZ = 831;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == HIGH) {
  HERTZ = 831;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == HIGH) {
  HERTZ = 831;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == HIGH) {
  HERTZ = 831;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == HIGH) {
  HERTZ = 831;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 880;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 880;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 880;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 880;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 880;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 880;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == LOW) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 932;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 932;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 932;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == LOW) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 932;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 932;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 932;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 988;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 988;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == LOW) {
  if (Button2 == LOW) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 1109;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == LOW) {
  if (Button2 == LOW) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 1109;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 1047;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == 1) {
  if (Button2 == 0) {
  if (Button3 == 0) {
  if (Button4 == 0) {
  if (Button5 == 0) {
  if (Button6 == 0) {
  if (Button7 == 0) {
  if (Button8 == 0) {
  if (Button9 == 0) {
  if (Button10 == 0) {
  if (Button11 == 0) {
  if (Button12 == 0) {
  HERTZ = 1047;
  SDS();
  }}}}}}}}}}}}
  } else {
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == HIGH) {
  if (Button7 == LOW) {
  if (Button8 == HIGH) {
  if (Button9 == HIGH) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 262;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == HIGH) {
  if (Button7 == LOW) {
  if (Button8 == HIGH) {
  if (Button9 == HIGH) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 262;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == HIGH) {
  if (Button7 == LOW) {
  if (Button8 == HIGH) {
  if (Button9 == HIGH) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 262;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == HIGH) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == HIGH) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 277;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == HIGH) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == HIGH) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 277;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == HIGH) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == HIGH) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 277;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == HIGH) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 294;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == HIGH) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 294;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == HIGH) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 294;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == HIGH) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 311;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == HIGH) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 311;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == HIGH) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 311;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 330;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 330;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 330;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 330;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 330;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 349;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 349;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 349;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 349;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == HIGH) {
  if (Button5 == HIGH) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 349;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == HIGH) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 370;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == HIGH) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 370;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == HIGH) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 370;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == HIGH) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 370;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == HIGH) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 370;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 392;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 392;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 392;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 392;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 392;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == HIGH) {
  HERTZ = 415;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == HIGH) {
  HERTZ = 415;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == HIGH) {
  HERTZ = 415;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == HIGH) {
  HERTZ = 415;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == HIGH) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == HIGH) {
  HERTZ = 415;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 440;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 440;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 440;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 440;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == HIGH) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 440;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == HIGH) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 466;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == LOW) {
  if (Button4 == HIGH) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 466;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 494;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == HIGH) {
  if (Button12 == LOW) {
  HERTZ = 494;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == 1) {
  if (Button2 == 0) {
  if (Button3 == 0) {
  if (Button4 == 0) {
  if (Button5 == 0) {
  if (Button6 == 0) {
  if (Button7 == 0) {
  if (Button8 == 0) {
  if (Button9 == 0) {
  if (Button10 == 0) {
  if (Button11 == 0) {
  if (Button12 == 0) {
  HERTZ = 523;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == HIGH) {
  if (Button2 == LOW) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 523;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == LOW) {
  if (Button2 == LOW) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == LOW) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 554;
  SDS();
  }}}}}}}}}}}}
  if (Button1 == LOW) {
  if (Button2 == LOW) {
  if (Button3 == LOW) {
  if (Button4 == LOW) {
  if (Button5 == LOW) {
  if (Button6 == LOW) {
  if (Button7 == HIGH) {
  if (Button8 == LOW) {
  if (Button9 == LOW) {
  if (Button10 == LOW) {
  if (Button11 == LOW) {
  if (Button12 == LOW) {
  HERTZ = 554;
  SDS();
  }}}}}}}}}}}}
  }
  }
  noTone(13);
  } else {
    if (led2 == true) {
      tone(4)
    }
  }
}



void SDS() {
  MIC = analogRead(A1);
  MIC = MIC / 10;
  MIC = (8.1739 * pow(e,(0.0578*HERTZ))) - 50;
  HERTZ = HERTZ + MIC;
  tone(13,HERTZ);
  delay(20);
  loop();
}
