int MIC = 0;
int MIC2 = 0;
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
unsigned int HERTZ = 0;

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
  pinMode(A1,INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.print(MIC);
  Serial.print(" ");
  Serial.print(MIC2);
  Serial.print(" ");
  Serial.print(Button1);
  Serial.print(Button2);
  Serial.print(Button3);
  Serial.print(Button4);
  Serial.print(" ");
  Serial.print(Button5);
  Serial.print(Button6);
  Serial.print(Button7);
  Serial.print(Button8);
  Serial.print(" ");
  Serial.print(Button9);
  Serial.print(Button10);
  Serial.print(Button11);
  Serial.println(Button12);
  MIC = analogRead(A0);
  MIC2 = analogRead(A1);
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
  if (MIC == 1) {
  if (MIC2 == 1) {
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
    HERTZ = 297;
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
  HERTZ = 189;
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
  HERTZ = 1175;
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
  noTone(13);
  }
  }
}

void SDS() {
  tone(13,HERTZ);
  delay(20);
  loop();
}
