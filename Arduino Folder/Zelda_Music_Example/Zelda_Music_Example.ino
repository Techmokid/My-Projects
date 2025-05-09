#include <MusicWithoutDelay.h>
#include <Tone.h>                //https://github.com/bhagman/Tone

char *Soprano  = "Zelda:o=5,b=160,f=aeb:4b,4f+8.f,16b,16b,16c1,16d1,16e1,2f1,8p,8f1,12f1,12g_1,12a1,2b1,12p,12b1,12b1,12b1,12a1,12g_1,8.a1,16g_1,2f1,4f1,8e1,16e1,16f1,2g_1,8f1,8e1,8d_1,16d_1,16e1,2f1,8e1,8d_1,8c1,16c1,16d1,2e#1,4g1,8f1,16f,16f,8f,16f,16f,8f,16f,16f,8f,8f";
char *Bass     = ":b=160,f=aeb:4d,12d,12d,12c,8.d,16d,16d,16e,16f,16g,8.a,16b,16b,16c1,16d1,16e1,4f1,12a,12b,12c1,8.d_1,16g_,16g_,16a,16b,16c1,12d_1,12p,12d_1,12d_1,12c1,12b,8.d_,16a,12a,12a,12g_,8.a,16a,12a,12g_,12a,8g_,16g_,16f,8g_,16g_,16a,4b,8a,8g_,8f,16f,16e,8f,16f,16g_,4a,8g_,8f,4e#,8e#,16e#,16f,8g,16g,16a#,8b,8c1,8a#,16a#-1,16a#-1,8a#-1,16a#-1,16a#-1,8a#-1,16a#-1,16a#-1,8a#-1,8a#-1";

MusicWithoutDelay instrument(Soprano);          //o=5 means that the instrument will play at the 5th Octave. o=4 is default
MusicWithoutDelay instrument2(Bass);          //f=aeb, means all a's, e's, and b's are flats

Tone myTone;
Tone myTone2;

void setup() {
  myTone.begin(11);
  myTone2.begin(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long cMillis = millis();
  instrument.play(cMillis, myTone);
  instrument2.play(cMillis, myTone2);
}

