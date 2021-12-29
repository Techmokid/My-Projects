#include <SoftwareSerial.h>

#include <JPEGCamera.h>

SoftwareSerial s(10,11);
JPEGCamera cam(s);
char resp[10];

void setup()
{
  Serial.begin(38400);
  
  // Wait for the serial port to be opened
  while (!Serial) delay(25);
  
  // Serial port connected to the cam
  s.begin(38400);  
}

void loop()
{
  int len;

  cam.reset();
  delay(4000);
  cam.chBaudRate(1);
  delay(50);
  s.end();
  s.begin(19200);
  delay(50);
  cam.takePicture();
  digitalWrite(13,HIGH);
  delay(25);
  while (Serial.read()!='c');
//  cam.stopPictures();
  
  cam.readData(Serial);

  while (1) {
    digitalWrite(13,HIGH);
    delay(100);
    digitalWrite(13,LOW);
    delay(100);
  }
}

