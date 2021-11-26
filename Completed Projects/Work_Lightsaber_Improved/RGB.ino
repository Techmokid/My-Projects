uint16_t i, j;

void rainbow(uint8_t wait) {
  isRainbow = true;
  StripIsOn = true;
  j++;
  for(i=0; i<=pixels.numPixels()/2; i++) {
    pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()*2) + j) & 255));
    pixels.setPixelColor(pixels.numPixels()-i, Wheel(((i * 256 / pixels.numPixels()*2) + j) & 255));
  }
#ifdef DO_RAINBOW_FLICKER
  if (random(0,RANDOM_FLICKER/100) == 1) {
    currentBrightness += random(-50,50);
    if (currentBrightness > MAX_BRIGHTNESS) { currentBrightness = MAX_BRIGHTNESS; }
    if (currentBrightness < MIN_BRIGHTNESS) { currentBrightness = MIN_BRIGHTNESS; }
    pixels.setBrightness(currentBrightness);
  }
#endif
  pixels.show();
  delay(wait);
}

void unsheathRainbow() {
  isRainbow = true;
  StripIsOn = true;
  j++;
  for(i=0; i<pixels.numPixels()/2; i++) {
    pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()*2) + j) & 255));
    pixels.setPixelColor(pixels.numPixels()-i, Wheel(((i * 256 / pixels.numPixels()*2) + j) & 255));
    pixels.show();
    delay(SABER_RETRACT_SPEED);
  }
}












// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}

uint8_t red(uint32_t c) {
  return (c >> 8);
}
uint8_t green(uint32_t c) {
  return (c >> 16);
}
uint8_t blue(uint32_t c) {
  return (c);
}
