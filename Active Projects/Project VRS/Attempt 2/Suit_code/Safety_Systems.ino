bool valsWithinDistance(float val1, float val2, float dist) { return abs(val1 - val2) < dist; }
bool valBetweenVals(float val1, float val2, float x) { return ((x>min(val1,val2)) && (x<max(val1,val2))); }

void runMotorsSafely() {
  for(int i = 0; i < motorIndexCount; i++) {
    float dist = 2; // How many degrees of threshold can we have before the system locks us out? Depending on the accuracy of the sensors
    float val1 = getAngleFromAnalogRead(motors[i].sensorPin1);
    float val2 = getAngleFromRotaryEncoder(motors[i].sensorPin2);
    float val3 = getAngleFromHallEffectSensor(motors[i].sensorPin3);
    bool statement1 = valsWithinDistance(val1,val2,dist);
    bool statement2 = valsWithinDistance(val1,val3,dist);
    bool statement3 = valsWithinDistance(val2,val3,dist);
    
    if ((!statement1) || (!statement2) || (!statement3)) {
      motors[i].sensorVal = -1;
    } else {
      //motors[i].sensorVal = val1; //Comment out the least accurate two options
      //motors[i].sensorVal = val2; //Comment out the least accurate two options
      motors[i].sensorVal = val3; //Comment out the least accurate two options
    }
  }
}

float getAngleFromRotaryEncoder(int pin) {
  while(1);
}

float getAngleFromHallEffectSensor(int pin) {
  while(1);
}

float getAngleFromAnalogRead(int pin) { return 135*(2*analogRead(pin) / 1023 - 1); }  // This is relative to the rotation of the potentiometer
