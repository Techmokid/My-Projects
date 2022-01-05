#include <MusicWithoutDelay.h>
#include <Tone.h>

char *melody = ":o=5,b=180,d=8:4f,e,f,4d,4f,e,f,4d,4f,e,f,4d,4f,e,f,4d,4f,e,f,4d,4f,e,f,4d,4f,e,d,4c#,4f,e,d,4c#";
char *triad1 = ":b=180,d=8:2.d1,2.d1,2.c1,2.c1,2.b_,2.b_,2.a,2.a";

MusicWithoutDelay instrument1(melody);
MusicWithoutDelay instrument2(triad1);

Tone myTone1;
Tone myTone2;

void setup() {
  myTone1.begin(11);
  myTone2.begin(10);
}

void loop() {
  unsigned long cMillis = millis();
  instrument1.play(cMillis, myTone1);
  instrument2.play(cMillis, myTone2);
}
