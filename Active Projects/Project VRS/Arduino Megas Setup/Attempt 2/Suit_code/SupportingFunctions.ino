void setMotorRatedTorque(int x[]) { for(int i = 0; i < motorIndexCount; i++) { motors[i].motorRatedTorque = x[i]; } }
void setMotorIDs(int x[]) { for(int i = 0; i < motorIndexCount; i++) { motors[i].motorID = x[i]; } }
void setMotorPins(int A[],int B[]) {
  for(int i = 0; i < motorIndexCount; i++) {
    motors[i].motorPinA = A[i];
    motors[i].motorPinB = B[i];
  }
}
void setSensorPins(int A[],int B[],int C[]) {
  for(int i = 0; i < motorIndexCount; i++) {
    motors[i].sensorPin1 = A[i];
    motors[i].sensorPin2 = B[i];
    motors[i].sensorPin3 = C[i];
  }
}

void splitString(String str,char sep) {
  StringCount = 0;
  while (str.length() > 0) {
    int index = str.indexOf(sep);
    if (index == -1) {
      splitStrings[StringCount++] = str;
      break;
    } else {
      splitStrings[StringCount++] = str.substring(0, index);
      str = str.substring(index+1);
    }
  }
}
