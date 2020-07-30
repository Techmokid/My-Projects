#include <SPI.h>
#include <DMD2.h>
#include <fonts/Arial14.h>

// Set Width to the number of displays wide you have
const int WIDTH = 1;
const uint8_t *FONT = Arial14;
const char *MESSAGE = "\"";

SoftDMD dmd(WIDTH,1);  // DMD controls the entire display
DMD_TextBox box(dmd);  // "box" provides a text box to automatically write to/scroll the display

// the setup routine runs once when you press reset:
void loop() { }
void setup() {
  dmd.setBrightness(255);
  dmd.selectFont(FONT);
  dmd.begin();
  
  const char *next = MESSAGE;
  while(*next) {
    box.print(*next);
    digitalWrite(LED_BUILTIN,HIGH); delay(50); digitalWrite(LED_BUILTIN,LOW);
    next++;
  }
  while(true);
}
