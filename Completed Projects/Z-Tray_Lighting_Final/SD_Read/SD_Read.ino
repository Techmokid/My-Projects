#include <SPI.h>
#include "SdFat.h"
#include "sdios.h"

using namespace sdfat;

const uint8_t chipSelect = SS;

SdFat sd;
SdFile root;
SdFile file;
File myFile;

void setup() {
  sdInit();
  
}

void loop() {}

void sdInit() {
  Serial.begin(115200);
  while (!Serial) { SysCall::yield(); } delay(100);
  
  Serial.print("\n\nInitialising SD...");
  //if (!sd.begin(chipSelect, SD_SCK_MHZ(50))) { sd.initErrorHalt(); }
  if (!sd.begin(chipSelect, SD_SCK_MHZ(50))) {
    sd.initErrorHalt();
    Serial.println("ERROR: Could not initialise SD!");
    while(true) {SysCall::yield();};
  }
  
  Serial.println("Initialised SD!");
}
