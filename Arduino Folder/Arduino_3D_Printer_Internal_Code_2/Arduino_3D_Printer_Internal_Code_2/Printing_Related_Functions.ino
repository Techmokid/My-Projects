//Still to do!
//G28 homes axis

void printingFunction() {
  if (currentLineBeingExcecuted.indexOf("M104S") > -1) {
    desiredExtruderTemp = currentLineBeingExcecuted.substring(5,currentLineBeingExcecuted.length()).toInt();
    setNextLine();
  } else if (currentLineBeingExcecuted.indexOf("M140S") > -1) {
    desiredBedTemp = currentLineBeingExcecuted.substring(5,currentLineBeingExcecuted.length()).toInt();
    setNextLine();
  } else if (currentLineBeingExcecuted.indexOf("M109S") > -1) {
    currentStatus = "Heating Extruder...";
    desiredExtruderTemp = currentLineBeingExcecuted.substring(5,currentLineBeingExcecuted.length()).toInt();
    if (extruderTemp() >= desiredExtruderTemp) {
      currentStatus = "";
      setNextLine();
    } else {
      turnOnExtruder();
    }
  } else if (currentLineBeingExcecuted.indexOf("M190S") > -1) {
    currentStatus = "Heating Bed...";
    desiredBedTemp = currentLineBeingExcecuted.substring(5,currentLineBeingExcecuted.length()).toInt();
    if (bedTemp() >= desiredBedTemp) {
      currentStatus = "";
      setNextLine();
    } else {
      turnOnBed();
    }
  } else if (currentLineBeingExcecuted.indexOf("M107") > -1) {
    currentLineBeingExcecuted = "M106S0";
  } else if (currentLineBeingExcecuted.indexOf("M106S") > -1) {
    analogWrite(8,currentLineBeingExcecuted.substring(5,currentLineBeingExcecuted.length()).toInt());
    setNextLine();
  } else if (currentLineBeingExcecuted.indexOf("M82") > -1) {
    absoluteExtrusion = true;
    setNextLine();
  } else if (currentLineBeingExcecuted.indexOf("G90") > -1) {
    absolutePositioning = true;
    setNextLine();
  } else if (currentLineBeingExcecuted.indexOf("M83") > -1) {
    absoluteExtrusion = false;
    setNextLine();
  } else if (currentLineBeingExcecuted.indexOf("G91") > -1) {
    absolutePositioning = false;
    setNextLine();
  } else if (currentLineBeingExcecuted.indexOf("G21") > -1) {
    Serial.println("Set to metric");
    setNextLine();
  } else {
    if ((currentStatus!="Heating Extruder...") and (currentStatus!="Heating Bed...")) {
      //IF THE COMMAND IS NOT RECOGNISED AND IT IS NOT WAITING FOR IT TO HEAT UP, THE CODE COMES HERE
      setNextLine();
    }
  }
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
  
  if (!isUsingComputer) {
    printedFile.close();
  } else {
    Serial.println("File Complete");
  }
  currentLine = 1;
  totalNumberOfLines = 0;
  isPrinting = false;
  primaryFlag = 1;
  secondaryFlag = 0;
  tertiaryFlag = 0;
  previousMillis = millis();
  
  turnOffExtruder();
  turnOffBed();
  activateReset();
  MenuScreen();
}

void setNextLine() {
  currentStatus = "";
  currentLineBeingExcecuted = readNextLine(false);
}

float bedTemp() {
  return analogRead(A0);
}

float extruderTemp() {
  return analogRead(A1);
}

String progress() {
  if ((currentStatus != "Heating Extruder...") and (currentStatus != "Heating Bed...")) {
    currentStatus = "Progress: " +  String(100 * float(currentLine) / float(totalNumberOfLines));
  }
  
  return currentStatus;
}

String readNextLine(bool firstScan) {
  char letter;
  String sentence = "";
  currentLine++;
  
  if (!isUsingComputer) {
    letter = printedFile.read();
    while (letter != '\n') {
      sentence += String(letter);
      letter = printedFile.read();
    }
  } else {
    Serial.println("Request next line");
    while (letter != '\n') {
      if (letter > 10) {
        sentence += String(letter);
      }
      letter = Serial.read();
    }
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
        return readNextLine(firstScan);
      } else {
        sentence = sentence.substring(0, sentence.indexOf(";"));
      }
    }
    
    if (sentence.indexOf("M117") > -1) {
      return readNextLine(firstScan);
    }
    
    if (sentence.indexOf("T0") > -1) {
      return readNextLine(firstScan);
    }
  }
  
  return sentence;
}

void maintainExtruderTemp() {
  if (extruderTemp() >= desiredExtruderTemp) {
    turnOffExtruder();
  } else {
    turnOnExtruder();
  }
}

void maintainBedTemp() {
  if (bedTemp() >= desiredBedTemp) {
    turnOffBed();
  } else {
    turnOnBed();
  }
}

void turnOnBed() {
  digitalWrite(7,HIGH);
}

void turnOffBed() {
  digitalWrite(7,LOW);
}

void turnOnExtruder() {
  digitalWrite(6,HIGH);
}

void turnOffExtruder() {
  digitalWrite(6,LOW);
}

void activateReset() {
  digitalWrite(53,LOW);
}
void deactivateReset() {
  digitalWrite(53,HIGH);
}
