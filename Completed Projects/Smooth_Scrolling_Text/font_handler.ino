//PROVEN WORKING
int roundUp(float x) { if (x == int(x)) { return x; } return int(x + 1); }

byte getVal(const uint8_t font[],int position) { return pgm_read_word_near(font + position); }

int getCharWidthMultiplier(const uint8_t font[]) { return roundUp(float(getVal(font,3)) / 8); }

int charWidth(const uint8_t font[],char letter) { return getVal(font,6 + letter - 32); }

int getCharStartPos(const uint8_t font[],char letter) {
  int checkLetter = 32; int index = 102;
  while (checkLetter < letter) {
    index += charWidth(font,checkLetter)*getCharWidthMultiplier(font);
    checkLetter++;
  }
  return index;
}

//STILL TO BE TESTED
byte getCharSlice(const uint8_t font[],char letter,int slice,int byteSelect) {
  return getVal(font,getCharStartPos(font,letter) + slice + charWidth(font,letter)*byteSelect);
}

byte getFirstByte(const uint8_t font[],char letter,int slice) {
  return getVal(font,getCharStartPos(font,letter) + slice);
}

byte getSecondByte(const uint8_t font[],char letter,int slice) {
  return getVal(font,getCharStartPos(font,letter) + slice + charWidth(font,letter));
}
