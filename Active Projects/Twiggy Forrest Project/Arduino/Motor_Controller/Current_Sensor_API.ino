//Packet says: 66mV/amp (Maximum voltage of 1.98v?)
//At a maximum of 30A to 5v, and an arduino analog read resolution of 1024, that gives an accuracy of 0.029A, or 29mA

#define AREF_VOLTAGE 5
#define MINIMUM_VOLTAGE 0
#define SENSITIVITY 0.066      // 66mV/amp

LinkedList<float> errorVals = LinkedList<float>();
float averageCurrent = 0.00;

float readRawCurrent(int pin) {
  float raw_reading = analogRead(pin);
  float inputVoltage = raw_reading * AREF_VOLTAGE / 1024;
  float outputCurrent = (inputVoltage - MINIMUM_VOLTAGE) / SENSITIVITY;
  return outputCurrent;
}

float readAverageCurrent() {
  float outputCurrent =  readRawCurrent(SENSOR_PIN);
  errorVals.add(outputCurrent);

  if (errorVals.size() > 10) {
    errorVals.remove(0);
    
    float total = 0;
    for (int i = 0; i < errorVals.size(); i++) { total += errorVals.get(i); }
    averageCurrent = total / errorVals.size();
  } else { averageCurrent = 0; }
  
  return averageCurrent;
}
