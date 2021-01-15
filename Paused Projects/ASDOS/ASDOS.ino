//ASDOS - Arduino SD Operating System

#include <SD.h>

#define ERROR_LED_PIN     53
#define SD_CHIP_SELECT    4

//Do we want there to be serial output? If not, then just set SERIAL_OUTPUT to false
//It doesn't affect any other part of code. It just means that serPrintln won't send data
//This does make ASDOS faster, at the cost of not having debug data
#define DONT_LOOP         false
#define SERIAL_OUTPUT     true
#define SERIAL_BAUDRATE   115200

File boot_file;
bool firstTimeBoot;

void setup() {
  pinMode(ERROR_LED_PIN,OUTPUT);
  digitalWrite(ERROR_LED_PIN,LOW);
  
  if (SERIAL_OUTPUT) { Serial.begin(SERIAL_BAUDRATE); }
  serPrintln(F("Booting ASDOS..."));
  
  if (!SD.begin(SD_CHIP_SELECT)) { serPrintln(F("FAIL - SD detection")); while (true) { SYSTEM_errorBlink(3,F("MEDIUM")); } }
  serPrintln(F("PASS - SD detection"));
  
  SYSTEM_checkSDStability();
  if (SD.exists(F("_ASDOS/runVars/"))) { deldir(F("_ASDOS/runVars/")); }
  SYSTEM_createSystemFileDirectories();
  
  if (!self_test()) {
    serPrintln(F("ASDOS Self Test has failed! Script cannot continue."));
    serPrintln(F("Please see terminal above for more information"));
    while (true) { SYSTEM_errorBlink(1,F("SLOW")); }
  } else {
    serPrintln(F("ASDOS Self Test Success!\n"));
  }

  if (firstTimeBoot) {
    serPrintln(F("ASDOS First-time Pre-Boot Successful!"));
  } else {
    serPrintln(F("ASDOS Normal Pre-Boot Successful!"));
  }
  
  serPrintln(F("\nBooting Primary Script..."));
  
  if (!SD.exists(F("_ASDOS/boot.ard"))) {
    String sentence = F("// Here is where you would put your code to be run\n");
    sentence += F("void start() {\n");
    sentence += F("  //This is where you put code to be run once\n");
    sentence += F("  \n");
    sentence += F("}\n\n");
    sentence += F("void loop() {\n");
    sentence += F("  //This is where you put code to be run forever\n");
    sentence += F("  \n");
    sentence += F("}");
    writeall(F("_ASDOS/boot.ard"),sentence);
    
    serPrintln(F("Generated new boot file!"));
  } else { serPrintln(F("Found pre-populated boot file!")); }
  
  boot_file = SD.open(F("_ASDOS/boot.ard"));
  if (!boot_file) { serPrintln(F("NO BOOT FILE FOUND")); SYSTEM_errorBlink(1,F("MEDIUM")); }
  
  serPrintln(F("\n\n\nASDOS Boot Successful!"));
}

void loop() {
  if (DONT_LOOP) { return; }
  
  //Retrieve the next line of code and execute it
  String nextLine = "";
  char fileInput = char(boot_file.read());
  while (fileInput != '\n') {
    nextLine += fileInput;
    fileInput = char(boot_file.read());
  }
  
  //"nextLine" now contains the next line of code to be executed
  int numberOfLoops = count_chars(nextLine,';');
  for (int i = 0; i < numberOfLoops; i++) { runCommand(splitString(nextLine,';',i)); }
}
