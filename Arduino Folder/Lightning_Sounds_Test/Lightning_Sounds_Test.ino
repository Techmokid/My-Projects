#include <pcmConfig.h>
#include <pcmRF.h>
#include <TMRpcm.h>
#include<SPI.h>
#include <SD.h>
TMRpcm tmrpcm;

bool previousOutput = false;

void setup() {
  randomSeed(analogRead(A0));
  
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  
  tmrpcm.speakerPin = 9;
  if (!SD.begin(10)) {Serial.println("SD fails"); return;}
  tmrpcm.setVolume(4);
  
  play();
}

void play() {
  tmrpcm.play("LIGHTN~2.WAV");
  return;
}

void loop() {
  if (tmrpcm.isPlaying()) {
    digitalWrite(8,HIGH);
  } else {
    digitalWrite(8,LOW);
    
    unsigned long var = random(0,60)* 1000;
    Serial.println(var);
    delay(var);
    
    flash();
    
    var = random(2,10);
    delay(var * 1000);
    play();
  }
}

void flash() {
  int numberOfFlashes = random(1,7);
  int currentNumber = 0;
  while (currentNumber < numberOfFlashes) {
    delay(random(20,250));
    digitalWrite(7,HIGH);
    delay(random(10,100));
    digitalWrite(7,LOW);
    currentNumber++;
  }
}

