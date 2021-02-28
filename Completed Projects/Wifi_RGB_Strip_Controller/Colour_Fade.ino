int r_fade_start;
int g_fade_start;
int b_fade_start;

int r_fade_current;
int g_fade_current;
int b_fade_current;

int r_fade_destination;
int g_fade_destination;
int b_fade_destination;

unsigned long fadeSpeedInMilliseconds;
unsigned long startingTime;
bool repeating = true;

void setFade(int r, int g, int b, float fadeSpeed) {
  setFade(r_fade_current,g_fade_current,b_fade_current,r,g,b,fadeSpeed);
}
void setFade(int r1, int g1, int b1, int r2, int g2, int b2, float fadeSpeed) {
  r_fade_start = r1;
  g_fade_start = g1;
  b_fade_start = b1;
  
  r_fade_destination = r2;
  g_fade_destination = g2;
  b_fade_destination = b2;

  r_fade_current = r_fade_start;
  g_fade_current = g_fade_start;
  b_fade_current = b_fade_start;
  
  fadeSpeedInMilliseconds = fadeSpeed;
  startingTime = millis();
}

void updateFade() {
  if (millis() - startingTime > fadeSpeedInMilliseconds) {
    r_fade_current = r_fade_destination;
    g_fade_current = g_fade_destination;
    b_fade_current = b_fade_destination;
    
    if (repeating) {
      r_fade_destination = r_fade_start;
      g_fade_destination = g_fade_start;
      b_fade_destination = b_fade_start;
      r_fade_start = r_fade_current;
      g_fade_start = g_fade_current;
      b_fade_start = b_fade_current;
      startingTime = millis();
    }
  } else {
    float percentageOfFadeCompleted = (millis() - startingTime) / float(fadeSpeedInMilliseconds);
    float inversePercentageOfFadeCompleted = 1 / percentageOfFadeCompleted;
    
    r_fade_current = float(r_fade_start)*inversePercentageOfFadeCompleted + float(r_fade_destination)*percentageOfFadeCompleted;
    g_fade_current = float(g_fade_start)*inversePercentageOfFadeCompleted + float(g_fade_destination)*percentageOfFadeCompleted;
    b_fade_current = float(b_fade_start)*inversePercentageOfFadeCompleted + float(b_fade_destination)*percentageOfFadeCompleted;
  }
  
  strip.clear();
  for(int x = 0; x < numberOfPixels; x++) {
    strip.setPixelColor(x, r_fade_current, g_fade_current,  b_fade_current);
  }
  
  strip.show();
  delay(1);
}

String getFadeColourDataReadout() {
  String startData =       String(r_fade_start)       + "|" + String(g_fade_start)       + "|" + String(b_fade_start);
  String currentData =     String(r_fade_current)     + "|" + String(g_fade_current)     + "|" + String(b_fade_current);
  String destinationData = String(r_fade_destination) + "|" + String(g_fade_destination) + "|" + String(b_fade_destination);
  return startData + "|" + currentData + "|" + destinationData;
}

void updateFadeSpeed(float fadeSpeed) {
  fadeSpeedInMilliseconds = fadeSpeed;
}
