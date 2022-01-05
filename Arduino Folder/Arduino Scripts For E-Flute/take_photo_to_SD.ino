#include <SoftwareSerial.h>
#include <SD.h>
#include <JPEGCamera.h>

int counter = 0;
File testFile;
SoftwareSerial s(9,10);
JPEGCamera cam(s);
char filename[10];
int num = 1;
int fileCount = 0;
boolean started = false;

void setup()
{
  Serial.begin(19200);
  
  // Wait for the serial port to be opened
  while (!Serial) delay(25);

  //check SD
  if (!SD.begin(4)) 
    Serial.println("Error:SD initialization failed,");
  else
    Serial.println("Info:SD Initialization complete,");
  // Serial port connected to the cam
  s.begin(38400);
  delay(50);
  //reset cam and wait.
  cam.reset();
  delay(3000);
  //change baud rate to work at 3.3v
  cam.chBaudRate(1);
  delay(50);
  //change serial to match new camera baud rate
  s.end();
  s.begin(19200);
  delay(50);
}


void loop()
{
  if(!started)
  {
    takePic();
    started = true;
  }
}

void takePic()
{
  //must call stopPictures before a new photo is taken.
  cam.stopPictures();
  delay(50);
  //take photo
  cam.takePicture();
  delay(50);
  
  do {
    //create a filename to store photo at
    sprintf(filename, "images/pic%i.jpg", num++);
  }
  while(SD.exists(filename)); //loop if it exists already

  // Create file  
  testFile = SD.open(filename, FILE_WRITE);
  //if it opens ok
  if(testFile)
  {
    //save to file
    Serial.println("Info:Writing to SD,");
    cam.readData(testFile);
  }
  else //else it didn't open ok
    Serial.println("Error:Error opening file on SD,");
    
  //must close file to finish writing.
  testFile.close();
}

