int Button1 = 0;
int Button2 = 0;
int Button3 = 0;
int MIC = 0;
int MIC2 = 0;
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
  MIC = digitalRead(A0);
  MIC2 = digitalRead(A1);
  Button1 = digitalRead(0);
  Button2 = digitalRead(2);
  Button3 = digitalRead(3);
  Serial.print(MIC);
  Serial.print(" ");
  Serial.print(MIC2);
  Serial.print("           ");
  Serial.print(Button1);
  Serial.print(Button2);
  Serial.println(Button3);
  if (MIC == HIGH) {      /* This is for the notes high D and higher */
    Serial.println("        !!!Sector 1!!!");
    if (Button1 == HIGH) {
      if (Button2 == HIGH) {
        if (Button3 == LOW) {
          HERTZ = 1175;
          SDS();
    }}}
  } else {
    noTone(13);
  }
}

void SDS() {
  tone(13,HERTZ);
  Serial.print("      !!!Hertz = ");
  Serial.print(HERTZ);
  Serial.println("!!!");
  delay(50);
  loop();
}
