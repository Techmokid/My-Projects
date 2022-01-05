//Pin 52 is for reset on connection activation/deactivation
//Pin 16 is for button1
//Pin 15 is for button2
//Pin 14 is for button3
//Pin 13, 12, 11, 10 are for SD card
//Pin 9 is for sound
//Pin 8 is for fan control
//Pin 7 is for bed control
//Pin 6 is for extruder control
//Pin A0 is for bed temperature reading
//Pin A1 is for extruder temperature reading

#include <SD.h>
#include <Wire.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <ButtonPress.h>

byte speaker[8] = {
  B00000,
  B00110,
  B01110,
  B11110,
  B11110,
  B01110,
  B00110,
  B00000,
};

byte speakerOff[8] = {
  B00000,
  B00000,
  B01010,
  B00100,
  B00100,
  B01010,
  B00000,
  B00000,
};

byte speakerOn[8] = {
  B00000,
  B10010,
  B01001,
  B01001,
  B01001,
  B01001,
  B10010,
  B00000,
};

float currentX = 0.000;
float currentY = 0.000;
float currentZ = 0.000;

bool isPrinting = false;
bool isUsingComputer = false;
bool usingSDCard = false;
bool soundActive = true;
bool absolutePositioning = true;
bool absoluteExtrusion = true;

int primaryFlag = 1;
int secondaryFlag = 0;
int tertiaryFlag = 0;
int prevPrimaryFlag = 1;
int prevSecondaryFlag = 0;
int desiredBedTemp = 0;
int desiredExtruderTemp = 0;

const int numberOfCachedFiles = 100;

String filenames[numberOfCachedFiles] = {};
String currentLineBeingExcecuted = "";
String currentStatus = "";

unsigned long previousMillis = 0;
unsigned long totalNumberOfLines = 0;
unsigned long currentLine = 1;

LiquidCrystal_I2C lcd(0x3F,20, 4);
File printedFile;
ButtonPress myButton;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  lcd.begin(20,4);
  lcd.backlight();
  lcd.clear();
  
  lcd.createChar(0, speaker);
  lcd.createChar(1, speakerOff);
  lcd.createChar(2, speakerOn);
  
  pinMode(53,OUTPUT);
  
  pinMode(16,INPUT);
  pinMode(15,INPUT);
  pinMode(14,INPUT);
  
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  
  MenuScreen();
  
  soundActive = EEPROM.read(0);
  
  if (soundActive) {
    tone(9,440);
    delay(100);
    tone(9,659);
    delay(100);
    noTone(9);
  }
  
  Serial.println("Hello? Are you There?");
  unsigned long currentTime = millis();
  String recievedData = "";
  while (millis() < currentTime + 200) {
    int tempVal = Serial.read();
    if (tempVal > 10) {
      recievedData += String(char(tempVal));
    }
    
    if (recievedData == "Yes, I am here Youngling") {
      isUsingComputer = true;
      Serial.println("I hear you daddy!");
      break;
    }
  }
}

void loop() {
  //char commandVal;
  char commandVal = char(Serial.read());
  bool button1Pressed = myButton.button1();
  bool button2Pressed = myButton.button2();
  bool button3Pressed = myButton.button3();
  bool commandRecieved = false;
  
  if(isUsingComputer) {
    button1Pressed = false;
    button2Pressed = false;
    button3Pressed = false;
  } else {
    commandVal = '0';
  }
  
  if ((commandVal == '0') and (!isPrinting) and (isUsingComputer)) {
    int letter = Serial.read();
    String sentence = "";
    while (char(letter) != '\n') {
      letter = Serial.read();
      if (letter > 31) {
        sentence += String(char(letter));
      }
    }
    
    isPrinting = true;
    totalNumberOfLines = atol(sentence.substring(0,sentence.indexOf('|')).c_str());
    currentLine = 1;
    tertiaryFlag = 4;
    filenames[tertiaryFlag] = sentence.substring(sentence.indexOf('|') + 1,sentence.length());
  }
  
  if (button1Pressed or (commandVal == '1')) {
    commandRecieved = true;
    commandVal = '1';
  } else if (button2Pressed or (commandVal == '2')) {
    commandRecieved = true;
    commandVal = '2';
  } else if (button3Pressed or (commandVal == '3')) {
    commandRecieved = true;
    commandVal = '3';
  }
  
  if (commandRecieved and soundActive) {
    tone(9,440);
    delay(10);
    noTone(9);
  }
  
  if ((commandVal=='2') and (primaryFlag==1) and (!isUsingComputer)) {
    //If you are on the display screen, switch to the menu screen
    primaryFlag = 0;
  } else if ((commandVal=='2') and (primaryFlag==0) and (secondaryFlag==0)) {
    primaryFlag = 1;
    previousMillis = millis();
  } else if ((commandVal=='2') and (primaryFlag==0) and (secondaryFlag==1) and (!isPrinting)) {
    printSelectionMenu();
  } else if ((commandVal=='2') and (primaryFlag==0) and (secondaryFlag==2) and (!isPrinting)) {
    Serial.println("MANUAL CONTROL");
  } else if ((commandVal=='2') and (primaryFlag==2) and (tertiaryFlag==0) and (!isPrinting)) {
    primaryFlag = 0;
  } else if ((commandVal=='2') and (primaryFlag==2) and (tertiaryFlag!=0) and (!isPrinting)) {
    deactivateReset();
    
    lcd.clear();
    lcd.setCursor(3,1);
    lcd.print("Analyzing File");
    lcd.setCursor(9,2);
    lcd.print("...");
    
    unsigned long currentTimeFromThing = millis();
    printedFile = SD.open(filenames[tertiaryFlag]);
    totalNumberOfLines = getNumberOfLines(filenames[tertiaryFlag]);
    printedFile.close();
    
    printedFile = SD.open(filenames[tertiaryFlag]);
    
    float seconds = (millis() - currentTimeFromThing) / 1000;
    Serial.println("Minutes Taken To Analyze File: " + String(float(seconds) / 60));
    Serial.println("File Selected: " + String(printedFile.name()));
    
    currentLine = 0;
    primaryFlag = 1;
    secondaryFlag = 0;
    isPrinting = true;
    commandRecieved = true;
    
    if (soundActive) {
      tone(9,440);
      delay(100);
      tone(9,659);
      delay(100);
      noTone(9);
    }
  } else if ((commandVal=='2') and (isPrinting) and (primaryFlag==0) and (secondaryFlag==2)) {
    //End Print
    printedFile.close();
    isPrinting = false;
    primaryFlag = 1;
    secondaryFlag = 0;
    tertiaryFlag = 0;
  } else if ((commandVal=='2') and (isPrinting) and (primaryFlag==0) and (secondaryFlag==1)) {
    Serial.println("REPLACE FILAMENT");
  }
  
  if ((commandVal=='3') and (secondaryFlag > 0) and (primaryFlag==0)) {
    secondaryFlag--;
  } else if ((commandVal=='3') and (tertiaryFlag > 0) and (primaryFlag==2)) {
    tertiaryFlag--;
  }
  
  if ((commandVal=='1') and (secondaryFlag < 2) and (primaryFlag==0)) {
    secondaryFlag++;
  } else if ((commandVal=='1') and (tertiaryFlag < numberOfCachedFiles - 1) and (primaryFlag==2)) {
    tertiaryFlag++;
  }
  
  if ((commandVal=='1') and (primaryFlag==1)) {
    soundActive = !soundActive;
    EEPROM.write(0,soundActive);
  } else if ((commandVal=='3') and (primaryFlag==1)) {
    soundActive = !soundActive;
    EEPROM.write(0,soundActive);
  }
  
  if ((primaryFlag!=prevPrimaryFlag) or (secondaryFlag!=prevSecondaryFlag) or (commandRecieved==true)) {
    prevPrimaryFlag = primaryFlag;
    prevSecondaryFlag = secondaryFlag;
    
    MenuScreen();
  }
  
  if (isPrinting) {
    printingFunction();
  }
  
  if ((millis() > previousMillis + 1000) and (primaryFlag == 1)) {
    //If on front screen and not printing, update once per second
    previousMillis = millis();
    MenuScreen();
  }
  
  if ((currentStatus != "Heating Extruder...") and (isPrinting)) {
    maintainExtruderTemp();
  }
  
  if ((currentStatus != "Heating Bed...") and (isPrinting)) {
    maintainBedTemp();
  }
}
