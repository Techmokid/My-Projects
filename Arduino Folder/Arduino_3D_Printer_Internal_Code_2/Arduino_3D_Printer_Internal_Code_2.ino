#include <SD.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

float currentX = 0.000;
float currentY = 0.000;
float currentZ = 0.000;

bool isPrinting = false;
bool usingSDCard = false;
bool soundActive = true;

int primaryFlag = 1;
int secondaryFlag = 0;
int tertiaryFlag = 0;
int prevPrimaryFlag = 1;
int prevSecondaryFlag = 0;
int desiredBedTemp = 0;
int desiredExtruderTemp = 0;

const int numberOfCachedFiles = 500;
String filenames[numberOfCachedFiles] = {};
String currentLineBeingExcecuted = "";
unsigned long previousMillis = 0;
unsigned long totalNumberOfLines = 0;
unsigned long currentLine = 1;

LiquidCrystal_I2C lcd(0x3F,20, 4);
File printedFile;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  lcd.begin(20,4);
  lcd.backlight();
  lcd.clear();
  
  pinMode(9,OUTPUT);
  
  MenuScreen();
  
  if (soundActive) {
    tone(9,440);
    delay(100);
    tone(9,659);
    delay(100);
    noTone(9);
  }
}

void loop() {
  char commandVal = char(Serial.read());
  bool commandRecieved = false;
  
  if (commandVal=='1') {
    commandRecieved = true;
  } else if (commandVal=='2') {
    commandRecieved = true;
  } else if (commandVal=='3') {
    commandRecieved = true;
  }
  
  if (commandRecieved and soundActive) {
    tone(9,440);
    delay(10);
    noTone(9);
  }
  
  if ((commandVal=='2') and (primaryFlag==1)) {
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
  } else if ((commandVal=='3') and (primaryFlag==1)) {
    soundActive = !soundActive;
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
}
