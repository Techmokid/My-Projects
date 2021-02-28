int r_single;
int g_single;
int b_single;

void setSingleColour(int r, int g, int b) {
  r_single = r;
  g_single = g;
  b_single = b;
}

void updateSingleColour() {
  strip.clear();
  for(int x = 0; x < numberOfPixels; x++) {
    strip.setPixelColor(x, r_single, g_single,  b_single);
  }
    
  strip.show();
  delay(1);
}

String getSingleColourDataReadout() {
  return String(r_single) + "|" + String(g_single) + "|" + String(b_single);
}
