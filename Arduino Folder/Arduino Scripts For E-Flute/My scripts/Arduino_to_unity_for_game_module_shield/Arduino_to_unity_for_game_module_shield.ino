#include <SPI.h>
#include <SD.h>

File myFile;

int wait = 50;
char data_a[255];
int data_b = 0;
bool buttonsOnly = false;
bool newComms = true;
String sentenceToSend;

void setup() {
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);

  if (buttonsOnly) {
    if (!SD.begin(4)) {
      return;
    }
  }
  
  Serial.begin(9600);
  if (buttonsOnly) {
    SD.begin();
  }

  Serial.setTimeout(100);
}

void loop() {
  while(digitalRead(10) == LOW){}
  
  //Directional buttons
  if (!newComms) {
    if (digitalRead(2) == LOW) {
      Serial.write(1);
      Serial.flush();
      delay(wait);
    }
    if (digitalRead(3) == LOW) {
      Serial.write(2);
      Serial.flush();
      delay(wait);
    }
    if (digitalRead(4) == LOW) {
      Serial.write(3);
      Serial.flush();
      delay(wait);
    }
    if (digitalRead(5) == LOW) {
      Serial.write(4);
      Serial.flush();
      delay(wait);
    }
  
    //Lower E and F buttons
    if (digitalRead(6) == LOW) {
      Serial.write(5);
      Serial.flush();
      delay(wait);
    }
    if (digitalRead(7) == LOW) {
      Serial.write(6);
      Serial.flush();
      delay(wait);
    }
  
    //Joystick button
    if (digitalRead(8) == LOW) {
      Serial.write(7);
      Serial.flush();
      delay(wait);
    }
  } else {
    //Pin 2 is A, Pin 3 is B, Pin 4 is C, Pin 5 is D, Pin 6 is E, and Pin 7 is F
    String buttons = String(digitalRead(2)) + "_" + String(digitalRead(3)) + "_" + String(digitalRead(4)) + "_" + String(digitalRead(5)) + "_" + String(digitalRead(6)) + "_" + String(digitalRead(7));

    //Pin 8 is the Joystick Button, and pins A0-A3 are the pins for the joysticks position
    String Joystick = String(digitalRead(8)) + "_" + String(analogRead(A0)) + "_" + String(analogRead(A1));
    sentenceToSend = buttons + "_" + Joystick + "|";
    
    //Still have to finish the  Serial.write() function. The format must be in a byte
    writeString(sentenceToSend);
    Serial.flush();
    delay(wait);
  }

  if (buttonsOnly) {
    //Joystick Position
    Serial.write(9);
    Serial.flush();
    delay(wait);
    Serial.write(analogRead(A0));
    Serial.flush();
    delay(wait);
    Serial.write(9);
    Serial.flush();
    delay(wait);
    Serial.write(analogRead(A1));
    Serial.flush();
    delay(wait);
    Serial.write(9);
    Serial.flush();
    delay(wait);

    //Save data to SD
    Serial.write(10);
    Serial.flush();
    delay(wait);

    coms();
  
    myFile = SD.open("SaveData.txt", FILE_WRITE);
    myFile.print(data_a);
    myFile.close();
  }
}

void coms(){
  data_b = Serial.read();
  
  if (data_b == 11)
  {
    Serial.readBytes(data_a, Serial.available());
  }
  if (data_b == 12)
  {
    myFile = SD.open("SaveData.txt", FILE_READ);
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close();
  }
}

void writeString(String stringData) { // Used to serially push out a String with Serial.write()

  for (int i = 0; i < stringData.length(); i++)
  {
    Serial.write(stringData[i]);   // Push each char 1 by 1 on each loop pass
  }

}

