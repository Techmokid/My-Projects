#include <SoftwareSerial.h>

#include <JPEGCamera.h>

//SoftwareSerial s(10,11);
JPEGCamera cam(Serial1);
char resp[10];

void setup()
{
  Serial.begin(38400);
  
  // Wait for the serial port to be opened
  while (!Serial) delay(25);
  
  // Serial port connected to the cam
  Serial1.begin(38400);
  delay(25);
  cam.reset();
  delay(4000);
}

void loop()
{
  int len;

  
  /*cam.powerSaving(true);
  delay(1000);
  cam.powerSaving(false);
  delay(100);*/
  //cam.chPictureSize(2);
  delay(50);
  cam.takePicture();
  digitalWrite(13,HIGH);
  delay(25);
  while (Serial.read()!='c');
  
  cam.readData(Serial);
  delay(100);
  cam.stopPictures();
  while (Serial.read()!='c') {
    digitalWrite(13,HIGH);
    delay(100);
    digitalWrite(13,LOW);
    delay(100);
  }
}

