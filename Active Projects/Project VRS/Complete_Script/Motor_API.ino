void applyTorqueToJoint(int ID, float torque) {
  setMotorSpeed(ID, clamp(255*(torque/motorStrengths[ID]),255*MAX_POWER_RATING,0));
}

void setMotorSpeed(int motorID, int in) { motorID *= 2; setMotorSpeed(motorID+2,motorID+3,in); }
void setMotorSpeed(int pinA, int pinB, int in) {
  if (in == 0) {
    analogWrite(pinA,0);
    analogWrite(pinB,0);
  } else if (in == 1) {
    analogWrite(pinB,0);
    analogWrite(pinA,255);
  } else if (in == -1) {
    analogWrite(pinA,0);
    analogWrite(pinB,255);
  } else if (in > 0) {
    analogWrite(pinA,0);
    analogWrite(pinB,clamp(in,0,255));
  } else {
    analogWrite(pinB,0);
    analogWrite(pinA,clamp(in,0,255));
  }
}

void setupMotors() {
  for (int i = 2; i < 55; i++) {
    pinMode(i,OUTPUT);
    analogWrite(i,0);
  }
}

void emergencyShutoff() {
  for (int i = 2; i < 55; i++) {
    analogWrite(i,0);
  }
}

int clamp(int in,int max,int min) {
  return min(max(in,min),max);
}
