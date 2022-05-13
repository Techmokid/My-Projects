struct servo {
  float offset0Deg = 1000;
  float offset180Deg = 2000;
  bool offset90 = false;
  int pin = 0;

  unsigned long previousTrigTimer = 0;
  bool onHalfOfSignal = false;
  int onTime = 1500;

  void writeMicroseconds(int x) { onTime = x; }//onTime = clamp(x,1000,2000); }
  void write(int x) {
    if (offset90) {
      onTime = map(0,180,offset0Deg,offset180Deg,clamp(x,-90,90) + 90);
    } else {
      onTime = map(0,180,offset0Deg,offset180Deg,clamp(x,0,180));
    }
  }

  float clamp(float x, float a, float b) {
    if (a==b) {return a;}
    if (a>b) { return min(a,max(b,x)); }
    return min(b,max(a,x));
  }
  
  void updateServo() {
    bool statementA = (onHalfOfSignal) && (micros() - previousTrigTimer >= onTime);
    bool statementB = (!onHalfOfSignal) && (micros() - previousTrigTimer >= 20000);
    if (statementB) { previousTrigTimer = micros(); } else if (!statementA) { return; }

    onHalfOfSignal = !onHalfOfSignal;
    digitalWrite(pin,onHalfOfSignal);
  }

  float map(float startIn, float startOut, float endIn, float endOut, float val) {
    val -= startIn;               // Starting values are just offsets
    val /= startOut - startIn;    // Now get the percentage between the two points that val is
    val *= (endOut - endIn);      // Extrapolate that percentage onto the new bounding parameters
    return val + endIn;           // Return the result, adding on the starting offset value
    // return ((val - startIn) / (startOut - startIn)) * (endOut - endIn) + endIn;
  }
};

servo serX;

void setup() {
  serX.pin = 12;
  pinMode(serX.pin,OUTPUT);
  Serial.begin(115200);
}

bool firstHalf = true;
float currentPos = 650;
float timingVal = 0.01;

unsigned long lastTime = 0;
void loop() {
  if (millis() - lastTime > 250) {
    Serial.println(currentPos);
    lastTime = millis();
  }
  serX.updateServo();

  if (firstHalf) {
    currentPos += timingVal;
    if (currentPos > 2400) { firstHalf = false; }
  } else {
    currentPos -= timingVal;
    if (currentPos < 650) { firstHalf = true; }
  }

  serX.writeMicroseconds(currentPos);
}
