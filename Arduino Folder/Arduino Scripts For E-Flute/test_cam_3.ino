//#include <SoftwareSerial.h>
#include <JPEGCamera.h>

//SoftwareSerial sserial(10,11);
JPEGCamera cam(Serial1/*sserial*/);
char resp[10];

void setup()
{
  Serial.begin(115200);
  
  // Wait for the serial port to be opened
  while (!Serial) delay(25);
  
  // Serial port connected to the cam
  /*sserial*/Serial1.begin(38400);
}

void loop()
{
  int len;

  cam.reset();
  delay(4000);
  while (/*sserial*/Serial1.available()) Serial.write(/*sserial*/Serial1.read());
  cam.chPictureSize(0);
  delay(50);
  cam.chBaudRate(4);
  delay(25);
  Serial1.end();
  delay(100);
  Serial1.begin(115200);
  /*cam.powerSaving(true);
  delay(1000);
  cam.powerSaving(false);
  delay(1000);*/
  /*cam.reset();
  delay(4000);*/
  //while (/*sserial*/Serial1.available()) Serial.write(/*sserial*/Serial1.read());  
  delay(500);
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


