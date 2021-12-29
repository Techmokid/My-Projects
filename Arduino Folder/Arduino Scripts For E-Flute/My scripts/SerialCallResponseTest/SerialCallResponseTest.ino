int sentence = 0;
int inByte = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);   // digital sensor is on digital pin 2
}

void loop()
{
  if (Serial.available() > 0) {
    inByte = Serial.read();
    if (inByte == 69) {
      tone (2,0);
      noTone;
    }
    sentence = inByte;
    tone(2,sentence);
  }
}
