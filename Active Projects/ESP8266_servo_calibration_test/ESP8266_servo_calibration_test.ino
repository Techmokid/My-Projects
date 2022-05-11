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
servo serY;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println("Initializing");
  
  serX.offset0Deg = 700;
  serX.offset180Deg = 2400;
  serY.offset0Deg = 600;
  serY.offset180Deg = 2200;

  serX.pin = pinToGPIO(4);
  serY.pin = pinToGPIO(3);

  pinMode(serX.pin,OUTPUT);
  pinMode(serY.pin,OUTPUT);

  serY.offset90 = true;

  serX.write(90);
  serY.write(0);
  Serial.println("Completed startup. Entering program loop");
}

void loop() {
  if (Serial.available()) {
    Serial.println("Receiving data from terminal...");
    String temp = Serial.readString();
    temp.replace(" ","");

    String servoAxis = temp.substring(0,2);
    servoAxis.toLowerCase();

    int val = temp.substring(2).toInt();
    
    if (servoAxis == "xs") { serX.offset0Deg = val;   Serial.println("Set servo X start to:" + String(val)); }
    if (servoAxis == "xl") { serX.offset180Deg = val; Serial.println("Set servo X finsh to:" + String(val)); }
    if (servoAxis == "ys") { serY.offset0Deg = val;   Serial.println("Set servo Y start to:" + String(val)); }
    if (servoAxis == "yl") { serY.offset180Deg = val; Serial.println("Set servo Y finsh to:" + String(val)); }
    
    String secondTemp = temp.substring(0,4);
    int secondVal = temp.substring(4).toInt();
    if (secondTemp == "SETX") { serX.write(secondVal); Serial.println("Set servo X to:" + String(secondVal) + " | " + String(serX.onTime)); }
    if (secondTemp == "SETY") { serY.write(secondVal); Serial.println("Set servo Y to:" + String(secondVal) + " | " + String(serY.onTime)); }
  }
  
  serX.write(0); unsigned long temp = millis(); while (millis() - temp < 2000) { serX.updateServo(); } delay(100);
  serX.write(90); temp = millis(); while (millis() - temp < 2000) { serX.updateServo(); } delay(100); if (Serial.available()) {}
  serX.write(180); temp = millis(); while (millis() - temp < 2000) { serX.updateServo(); } delay(100); if (Serial.available()) {}
  serX.write(90); temp = millis(); while (millis() - temp < 2000) { serX.updateServo(); } delay(100); if (Serial.available()) {}
}

int pinToGPIO(int x) {
  if (x == 0) {return 16;}
  if (x == 1) {return 5;}
  if (x == 2) {return 4;}
  if (x == 3) {return 0;}
  if (x == 4) {return 2;}
  if (x == 5) {return 14;}
  if (x == 6) {return 12;}
  if (x == 7) {return 13;}
  if (x == 8) {return 15;}
  return -1;
}
