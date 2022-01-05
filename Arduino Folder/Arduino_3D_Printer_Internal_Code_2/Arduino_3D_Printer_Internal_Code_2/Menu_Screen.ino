void MenuScreen() {
  if (primaryFlag==0) {
    //Show Menu Screen
    if (!isPrinting) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("MENU SCREEN: ");
      lcd.setCursor(0,1);
      if (secondaryFlag==0) {
        lcd.print("*Back To Display");
        lcd.setCursor(0,2);
        lcd.print("Print File");
        lcd.setCursor(0,3);
        lcd.print("Manual Motor Ctrl");
      } else if (secondaryFlag==1) {
        lcd.print("Back To Display");
        lcd.setCursor(0,2);
        lcd.print("*Print File");
        lcd.setCursor(0,3);
        lcd.print("Manual Motor Ctrl");
      } else if (secondaryFlag==2) {
        lcd.print("Back To Display");
        lcd.setCursor(0,2);
        lcd.print("Print File");
        lcd.setCursor(0,3);
        lcd.print("*Manual Motor Ctrl");
      }
    } else {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("PRINTING MENU: ");
      lcd.setCursor(0,1);
      if (secondaryFlag==0) {
        lcd.print("*Back To Display");
        lcd.setCursor(0,2);
        lcd.print("Replace Filament");
        lcd.setCursor(0,3);
        lcd.print("End Print");
      } else if (secondaryFlag==1) {
        lcd.print("Back To Display");
        lcd.setCursor(0,2);
        lcd.print("*Replace Filament");
        lcd.setCursor(0,3);
        lcd.print("End Print");
      } else if (secondaryFlag==2) {
        lcd.print("Back To Display");
        lcd.setCursor(0,2);
        lcd.print("Replace Filament");
        lcd.setCursor(0,3);
        lcd.print("*End Print");
      }
    }
    
    lcd.setCursor(18,3);
    lcd.write(byte(0));
    if (!soundActive) {
      lcd.write(byte(1));
    } else {
      lcd.write(byte(2));
    }
  } else if (primaryFlag==1) {
    //Show Front Screen
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Bed Temp: " + String(bedTemp()));
    lcd.setCursor(0,1);
    lcd.print("Ext Temp: " + String(extruderTemp()));
    
    if (isPrinting) {
      if (!isUsingComputer) {
        lcd.setCursor(0,0);
        lcd.print("Bed Temp: " + String(bedTemp()) + "/" + desiredBedTemp);
        lcd.setCursor(0,1);
        lcd.print("Ext Temp: " + String(bedTemp()) + "/" + desiredExtruderTemp);
        lcd.setCursor(0,2);
        lcd.print(progress() + "%");
        lcd.setCursor(0,3);
        lcd.print("Printing: " + String(stripDirectoryFromFilename(filenames[tertiaryFlag]).substring(0,9)));
        lcd.setCursor(18,3);
        lcd.write(byte(0));
        if (!soundActive) {
          lcd.write(byte(1));
        } else {
          lcd.write(byte(2));
        }
      } else {
        lcd.setCursor(0,0);
        lcd.print("Bed Temp: " + String(bedTemp()) + "/" + desiredBedTemp);
        lcd.setCursor(0,1);
        lcd.print("Ext Temp: " + String(bedTemp()) + "/" + desiredExtruderTemp);
        lcd.setCursor(0,3);
        lcd.print("  Printing From PC");
      }
    } else {
      lcd.setCursor(0,0);
      lcd.print("Bed Temp: " + String(bedTemp()));
      lcd.setCursor(0,1);
      lcd.print("Ext Temp: " + String(bedTemp()));
      lcd.setCursor(0,3);
      lcd.print("Not Printing");
      lcd.setCursor(18,3);
      lcd.write(byte(0));
      if (!soundActive) {
        lcd.write(byte(1));
      } else {
        lcd.write(byte(2));
      }
    }
  } else if (primaryFlag==2) {
    //Show Print Selection Menu------------------------------------------------------------------------------------------------------------------------------------------------------
    if (filenames[tertiaryFlag] == "") {
      tertiaryFlag--;
    }
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("*" + StringToLast19Letters(stripDirectoryFromFilename(filenames[tertiaryFlag])));
    lcd.setCursor(0,1);
    lcd.print(StringToLast19Letters(stripDirectoryFromFilename(filenames[tertiaryFlag + 1])));
    lcd.setCursor(0,2);
    lcd.print(StringToLast19Letters(stripDirectoryFromFilename(filenames[tertiaryFlag + 2])));
    lcd.setCursor(0,3);
    lcd.print(StringToLast19Letters(stripDirectoryFromFilename(filenames[tertiaryFlag + 3])));
    lcd.setCursor(18,3);
    lcd.write(byte(0));
    if (!soundActive) {
      lcd.write(byte(1));
    } else {
      lcd.write(byte(2));
    }
  } else if (primaryFlag==3) {
    //Show Manual Control Menu
    
  }
}

void printSelectionMenu() {
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Searching for SD...");
  
  SDCheck();
  
  lcd.clear();
  if (!usingSDCard) {
    primaryFlag = 0;
    MenuScreen();
  } else {
    //Actually display print selection menu
    for (int x = 0; x < sizeof(filenames) / sizeof(filenames[0]); x++) {filenames[x] = "";}
    
    File listDirectories = SD.open("/");
    listDirectory(listDirectories,"/");
    listDirectories.close();
    
    for(int i = (sizeof(filenames)/sizeof(filenames[0]))-1; i > 0; i--) {
      filenames[i] = filenames[i-1];
    }
    
    primaryFlag = 2;
    tertiaryFlag = 0;
    filenames[0] = "Return To Main Menu";
    MenuScreen();
  }
}

String StringToLast19Letters(String val) {
  int StringLength = val.length();
  if (StringLength <= 18) {
    return val;
  }
  
  String result = val.substring(StringLength-19,StringLength);
  return result;
}

String StringToFirst10Letters(String val) {
  int StringLength = val.length();
  if (StringLength < 10) {
    return val;
  }
  
  String result = val.substring(0,9);
  return result;
}
