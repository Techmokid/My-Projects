#define arduinoIndex 1
#define MAX_POWER_RATING 0.05
#define motorIndexCount 3

struct Motor {
  int motorPinA,motorPinB,motorID,sensorPin1,sensorPin2,sensorPin3;
  float motorRatedTorque,motorTargetTorque,sensorVal;
  bool isRunning = true;
  
  int clamp(int in,int max,int min) { return min(max(in,min),max); }
  void setMotorSpeed(int in) {
    if (!isRunning) { in = 0; motorTargetTorque = 0; }
    
    if (in == 0) { analogWrite(motorPinA,0); analogWrite(motorPinB,0);
    } else if (in == 1) { analogWrite(motorPinB,0); analogWrite(motorPinA,255);
    } else if (in == -1) { analogWrite(motorPinA,0); analogWrite(motorPinB,255);
    } else if (in > 0) { analogWrite(motorPinA,0); analogWrite(motorPinB,clamp(in,0,255));
    } else { analogWrite(motorPinB,0); analogWrite(motorPinA,clamp(in,0,255)); }
  }
};

int StringCount = 0;
String splitStrings[100];
Motor motors[motorIndexCount];

void setup() {
  Serial.begin(115200);
  setupFastRead();

  int motorIDs[] = {
    3*arduinoIndex,
    3*arduinoIndex+1,
    3*arduinoIndex+2
  };
  setMotorIDs(motorIDs);
  
  int motorPins1[] = {3,6,10};
  int motorPins2[] = {5,9,11};
  setMotorPins(motorPins1,motorPins2);
  
  int sensorPins1[] = {2,4,7};
  int sensorPins2[] = {8,9,10};
  int sensorPins3[] = {11,12,13};
  setSensorPins(sensorPins1,sensorPins2,sensorPins3);

  Serial.println(arduinoIndex);
  String msg = "";
  char c = Serial.read();
  while(c != '\n') {
    if (c > 20)
      msg += c;
    c = Serial.read();
  }

  splitString(msg,',');
  for(int i = 0; i < StringCount; i++) {
    String tmp = splitStrings[i];
    int ID = tmp.substring(0,tmp.indexOf(':')).toInt();
    for(int motorIndex = 0; motorIndex < motorIndexCount; motorIndex++) {
      if (motors[motorIndex].motorID == ID) {
        motors[motorIndex].motorRatedTorque = tmp.substring(tmp.indexOf(':')+1).toDouble();
      }
    }
  }
  
  //int motorTorques[] = {65,65,0.18};
  //setMotorRatedTorque(motorTorques);
}

void loop() {
  if(Serial.available()) {
    String msg = "";
    char c = Serial.read();
    while(c != '\n') {
      if (c > 20)
        msg += c;
      c = Serial.read();
    }
  
    splitString(msg,',');
    for(int i = 0; i < StringCount; i++) {
      String tmp = splitStrings[i];
      int ID = tmp.substring(0,tmp.indexOf(':')).toInt();
      for(int motorIndex = 0; motorIndex < motorIndexCount; motorIndex++) {
        if (motors[motorIndex].motorID == ID) {
          //motors[motorIndex].motorTargetTorque = tmp.substring(tmp.indexOf(':')+1).toDouble();
          motors[i].setMotorSpeed(tmp.substring(tmp.indexOf(':')+1).toDouble());
        }
      }
    }
  }

  runMotorsSafely();
}
