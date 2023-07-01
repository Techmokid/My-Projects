bool looping = true;
int currentIndex = 0;
int currentIndex_2 = 0;
unsigned long timer = 0;
bool running = false;

void start() { running = true; currentIndex = 0; currentIndex_2 = 0; }
byte updateScrollingDisplay(const uint8_t *font) {
  if (!running) { return 0; }
  if (millis() - timer < scrollSpeed) { return 0; } timer = millis();
  
  shiftDisplayLeft();
  getNextCharSlice(font);
}

void shiftDisplayLeft() {
  for (int x = 0; x < dmd.width - 1; x++) {
    for (int y = 0; y < dmd.height; y++) { dmd.setPixel(x,y,dmd.getPixel(x+1,y)); }
  }
  
  for (int y = 0; y < dmd.height; y++) { dmd.setPixel(dmd.width-1,y,false); }
}

void getNextCharSlice(const uint8_t* font) {
  if (currentIndex_2 != charWidth(font,sentence[currentIndex])) {
    displayData(dmd.width - 1, 0,
                getFirstByte(font,sentence[currentIndex],currentIndex_2),
                getSecondByte(font,sentence[currentIndex],currentIndex_2)
    );
  } else { displayData(dmd.width - 1, 2,0x00,0x00); }
  
  currentIndex_2++;
  if (currentIndex_2 > charWidth(font,sentence[currentIndex])) { currentIndex_2 = 0; currentIndex++; }
  if (currentIndex == sentence.length()) { if (looping) { currentIndex = 0; } else { running = false; } }
}

void displayData(int x, int y, bool data) { dmd.setPixel(x,y,data); }
void displayData(int x, int y, byte data1, byte data2) {
  dmd.setPixel(x,y,bitRead(data1,0));
  dmd.setPixel(x,y+1,bitRead(data1,1));
  dmd.setPixel(x,y+2,bitRead(data1,2));
  dmd.setPixel(x,y+3,bitRead(data1,3));
  dmd.setPixel(x,y+4,bitRead(data1,4));
  dmd.setPixel(x,y+5,bitRead(data1,5));
  dmd.setPixel(x,y+6,bitRead(data1,6));
  dmd.setPixel(x,y+7,bitRead(data1,7));
  dmd.setPixel(x,y+8,bitRead(data2,2));
  dmd.setPixel(x,y+9,bitRead(data2,3));
  dmd.setPixel(x,y+10,bitRead(data2,4));
  dmd.setPixel(x,y+11,bitRead(data2,5));
  dmd.setPixel(x,y+12,bitRead(data2,6));
  dmd.setPixel(x,y+13,bitRead(data2,7));
}
