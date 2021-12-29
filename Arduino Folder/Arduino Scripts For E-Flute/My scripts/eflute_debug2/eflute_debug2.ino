boolean talk = true;
boolean inittest = true;
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
int MIC2 = 0;
unsigned int HERTZ = 0;
int LOOP = 0;
int thisByte = 33;

/* 
  Buttons go on pins D0 to D12 using digital sensor reading circuits excluding D1 (TX/Output only).
  A speaker goes between pins D13 and Ground.
  Pin A0 is directly grounded through a button (Foot Pedal). This selects whether or not to play/not play a note.
  Pin A1 is connected the same as Pin A0. This is for register/octave select.
  For notes above high D, register/octave select (A1) does not affect the note sound.
  
  NOTE: This circuit is very sensitive to static and touching bare wires will cause the unit to misread the buttons. This may cause undesired results.
  P.S While in the normal programming circuit, the chip will always read pin D0 (And sometime D2) as pressed, no matter the actual input.
*/

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
  if (talk == true) {
    Serial.begin(9600);
    Serial.println("");
    Serial.println("");
    Serial.println("                                                             !!!STARTING THE SCRIPT!!!");
    Serial.println("");
    Serial.println("TESTING SPEAKER...");
    Serial.println("");
  }
  tone(13,90);
  delay(500);
  noTone(13);
  delay(500);
  tone(13,90);
  delay(500);
  noTone(13);
  if (inittest == true) {
    Serial.println("SPEAKER TEST PASSED IF A SOUND WAS HEARD");
    Serial.println("");
    Serial.println("TESTING SERIAL CONNECTION...");
    Serial.println("");
    while (thisByte < 127) {
    Serial.write(thisByte);
    Serial.print(", dec: ");
    Serial.print(thisByte, DEC);
    Serial.print(", hex: ");
    Serial.print(thisByte, HEX);
    Serial.print(", oct: ");
    Serial.print(thisByte, OCT);
    Serial.print(", bin: ");
    Serial.println(thisByte, BIN);
    thisByte = thisByte + 1;
    }
    Serial.println("SERIAL CONNECTION TEST PASSED");
    Serial.println("");
    Serial.println("");
    Serial.println("STARTING");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("");
  }
  if (talk == true) {
    Serial.println("MIC & MIC2       BINARY              SECTION 1                 SECTION 2 OR 3");
    Serial.println("");
  }
}

void loop() {
  Serial.println("");
  if (talk == true) {
    LOOP = LOOP + 1;
    if (LOOP == 30) {
      LOOP = 0;
      Serial.println("");
      Serial.println("");
      Serial.println("MIC & MIC2       BINARY              SECTION 1                   SECTION 2           Section 3");
      Serial.println("");
    }
  }
  MIC = digitalRead(A0);
  MIC2 = digitalRead(A1);
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
  if (talk == true) {
    Serial.print(MIC);
    Serial.print(" ");
    Serial.print(MIC2);
    Serial.print("           ");
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
    Serial.print(Button12);
  }
  if (MIC == HIGH) {      /* This is for the notes high D and higher */
  if (talk == true) {
    Serial.print("        !!!Sector 1!!!");
  }
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
  if (MIC2 == HIGH) {                         /* This is for the notes that you have to blow harder for (Middle D to High C#) */
  if (talk == true) {
    Serial.print("              !!!Sector 2!!!");
  }
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
  } else {                                    /* This is for the notes that you have to blow softer for (Low C to Middle C#) */
  if (talk == true) {
    Serial.print("                                  !!!SECTOR 3!!!");
  }
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
}



void SDS() {
  tone(13,HERTZ);
  if (talk == true) {
    Serial.print("      !!!HERTZ = ");
    Serial.print(HERTZ);
    Serial.println("!!!");
  }
  delay(20);
  loop();
}
