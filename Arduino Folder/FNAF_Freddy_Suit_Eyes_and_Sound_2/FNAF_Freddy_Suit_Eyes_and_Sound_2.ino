#include <SimpleSDAudio.h>

void setup() {
  Serial.begin(9600);
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);
  
  SdPlay.setSDCSPin(4); // sd card cs pin

  if (!SdPlay.init(SSDA_MODE_FULLRATE | SSDA_MODE_MONO | SSDA_MODE_AUTOWORKER)) {
    Serial.println("SD could not be initialised");
  }
  
  if(!SdPlay.setFile("FNAFFR~3.WAV")) { Serial.println("File could not be set"); }
  
  SdPlay.play(); // play music
  
  float glitchedFinishTime = 46000;
  float startTime = millis();
  while(!SdPlay.isStopped()) {
    digitalWrite(8,HIGH);
    int randomVal = random(20,100);
    delay(randomVal);
    
    digitalWrite(8,LOW);
    randomVal = random(0,500);
    delay(randomVal);
    
    if (startTime + glitchedFinishTime < millis()) { SdPlay.stop(); }
  }
  
  digitalWrite(9,LOW);
}

void loop() {}
