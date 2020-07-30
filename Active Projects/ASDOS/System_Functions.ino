//These are all system functions used by ASDOS and should not be called by the boot code

void SYSTEM_errorBlink(String blinkType, int numberOfBlinks) { SYSTEM_errorBlink(numberOfBlinks,blinkType); }
void SYSTEM_errorBlink(int numberOfBlinks, String blinkType) {
  serPrint(F("ERROR: ")); serPrint(String(blinkType) + String(numberOfBlinks) + "\n");
  
  int blinkLength;
  if (blinkType == "SLOW") {
    blinkLength = 1000;
  } else if (blinkType == "MEDIUM") {
    blinkLength = 500;
  } else if (blinkType == "FAST") {
    blinkLength = 200;
  } else if (blinkType == "STROBE") {
    blinkLength = 100;
  } else { while (true) { SYSTEM_errorBlink(1,"MEDIUM"); } }
  
  for (int i = 0; i < numberOfBlinks; i++) {
    digitalWrite(ERROR_LED_PIN,HIGH);
    delay(blinkLength);
    digitalWrite(ERROR_LED_PIN,LOW);
    delay(blinkLength);
  }

  delay(3000);
}

void SYSTEM_checkSDStability() {
  if (SD.exists(F("SysStbl.txt"))) { SD.remove(F("SysStbl.txt")); }
  
  File f = SD.open(F("SysStbl.txt"),FILE_WRITE);
  if (f == false) { while (true) { SYSTEM_errorBlink(3,F("FAST")); } }
  f.print(F("System Stability Test.\nIf the user ever reads this, then the stability test has failed"));
  f.close();
  
  //Check has so-far succeeded. Now to read back the data we saved
  String file_contents = readall(F("SysStbl.txt"));
  if (file_contents != F("System Stability Test.\nIf the user ever reads this, then the stability test has failed")) {
    serPrintln(F("FAIL - SD stability check"));
    while (true) { SYSTEM_errorBlink(3,"FAST"); }
  }
  
  SD.remove(F("SysStbl.txt"));
  serPrintln(F("PASS - SD stability check"));
}

void SYSTEM_createSystemFileDirectories() {
  firstTimeBoot = createDir(F("_ASDOS/cmplr"));
  firstTimeBoot = firstTimeBoot and createDir(F("_ASDOS/runVars/int"));
  firstTimeBoot = firstTimeBoot and createDir(F("_ASDOS/runVars/float"));
  firstTimeBoot = firstTimeBoot and createDir(F("_ASDOS/runVars/bool"));
  firstTimeBoot = firstTimeBoot and createDir(F("_ASDOS/runVars/string"));
  firstTimeBoot = firstTimeBoot and createDir(F("_ASDOS/sysData"));
  firstTimeBoot = firstTimeBoot and createDir(F("_ASDOS/progData"));
  serPrintln(F("PASS - System file creation"));
}
