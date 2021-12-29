#include <pcmConfig.h>
#include <pcmRF.h>
#include <TMRpcm.h>
#include<SPI.h>
#include <SD.h>
TMRpcm tmrpcm;

void setup() {
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  
  tmrpcm.speakerPin = 9;
  if (!SD.begin(10)) {Serial.println("SD fails"); return;}
  tmrpcm.setVolume(4);
  
  tmrpcm.play("FNAFFR~1.WAV"); flickerEyes();
}

void loop() {}

void flickerEyes() {
  digitalWrite(8,HIGH);
  int randomVal = random(20,100);
  delay(randomVal);
  
  digitalWrite(8,LOW);
  randomVal = random(0,500);
  delay(randomVal);
}
