void SDCheck() {
  if (SD.begin(10)) {
    File testFile = SD.open("test.ard", FILE_WRITE);
    if (!testFile) {
      lcd.clear();
      lcd.setCursor(6,1);
      lcd.print("SD CARD");
      lcd.setCursor(6,2);
      lcd.print("UNSTABLE");
      usingSDCard = false;
      delay(1500);
    } else {
      usingSDCard = true;
    }
    testFile.close();
    SD.remove("test.ard");
  } else {
    lcd.clear();
    lcd.setCursor(6,1);
    lcd.print("SD CARD");
    lcd.setCursor(4,2);
    lcd.print("NOT DETECTED");
    usingSDCard = false;
    delay(1500);
  }
}

void listDirectory(File dir, String identifier) {
  while (true) {
    File entry = dir.openNextFile();
    
    if (!entry) {break;}
    if (!entry.isDirectory()) {
      if (endsInGCODE(identifier + String(entry.name()))) {
        addToFilenames(identifier + String(entry.name()));
      } else {
        listDirectory(dir,identifier);
      }
    } else {
      identifier += String(entry.name()) + "/";
      listDirectory(entry,identifier);
      identifier = "/";
    }
    entry.close();
  }
}

void addToFilenames(String val) {
  int a = 0;
  while (a < numberOfCachedFiles) {
    if (filenames[a] == "") {
      filenames[a] = val;
      break;
    }
    a++;
  }
}

unsigned long getNumberOfLines(String directory) {
  String line = readNextLine(true);
  unsigned long i = 0;
  
  while (line != "") {
    i++;
    line = readNextLine(true);
  }
  
  return i;
}

String stripDirectoryFromFilename(String dir) {
  String filename = dir.substring(0,dir.indexOf("."));
  
  int i = 0;
  String result = "";
  
  while (i < filename.length()) {
    if (filename.charAt(i) == '/') {result = "";} else {result += filename.charAt(i);}
    i++;
  }
  
  return result;
}

bool endsInGCODE(String sentence) {
  int sentenceLength = sentence.length();
  String ending = sentence.substring(sentenceLength - 4, sentenceLength);
  if (ending == ".GCO") {
    return true;
  }
  return false;
}

void emptySerialBuffer() {
  while (Serial.read() > -1) {}
}
