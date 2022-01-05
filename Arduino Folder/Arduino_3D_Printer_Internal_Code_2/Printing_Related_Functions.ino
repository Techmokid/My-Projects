void printingFunction() {
  delay(5);
  setNextLine();
  Serial.println(currentLineBeingExcecuted);
}

void finishPrint() {
  if (soundActive) {
    tone(9,440);
    delay(150);
    tone(9,554);
    delay(150);
    tone(9,659);
    delay(150);
    tone(9,880);
    delay(300);
    noTone(9);
  }
  
  printedFile.close();
  currentLine = 1;
  totalNumberOfLines = 0;
  isPrinting = false;
  primaryFlag = 1;
  secondaryFlag = 0;
  tertiaryFlag = 0;
  previousMillis = millis();
  MenuScreen();
}

void setNextLine() {
  currentLineBeingExcecuted = readNextLine(false);
  currentLine++;
}

float bedTemp() {
  return 24.00;
}

float extruderTemp() {
  return 24.00;
}

float progress() {
  return 100 * float(currentLine) / float(totalNumberOfLines);
}

String readNextLine(bool firstScan) {
  char letter = printedFile.read();
  String sentence = "";
  
  while (letter != '\n') {
    sentence += String(letter);
    letter = printedFile.read();
  }
  
  sentence.replace(" ", "");
  
  if (firstScan) {
    emptySerialBuffer();
    
    if (sentence.indexOf(";EndofGcode") > -1) {
      return "";
    }
  } else {
    if (sentence.indexOf(";EndofGcode") > -1) {
      finishPrint();
      return "";
    }
    
    if (sentence.indexOf(";") > -1) {
      //If you want the next command to execute but it has a semi-colon in it
      if (sentence.indexOf(";") == 0) {
        currentLine++;
        return readNextLine(firstScan);
      } else {
        sentence = sentence.substring(0, sentence.indexOf(";"));
      }
    }
    
    if (sentence.indexOf("M117") > -1) {
      currentLine++;
      return readNextLine(firstScan);
    }
    
    if (sentence.indexOf("T0") > -1) {
      currentLine++;
      return readNextLine(firstScan);
    }
  }
  
  return sentence;
}
