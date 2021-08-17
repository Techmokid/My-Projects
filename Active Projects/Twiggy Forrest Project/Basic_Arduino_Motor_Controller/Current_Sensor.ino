//Packet says: 66mV/amp (Maximum voltage of 1.98v?)
//At a maximum of 30A to 5v, and an arduino analog read resolution of 1024, that gives an accuracy of 0.029A, or 29mA

#include <LinkedList.h>

#define AREF_VOLTAGE 5
#define MINIMUM_VOLTAGE 0
#define SENSITIVITY 0.066      // 66mV/amp

#define pin_A 0
#define pin_B 1

LinkedList<float> errorVals = LinkedList<float>();

float readRawCurrent(int pin) {
  float raw_reading = analogRead(pin);
  float inputVoltage = raw_reading * AREF_VOLTAGE / 1024;
  float outputCurrent = (inputVoltage - MINIMUM_VOLTAGE) / SENSITIVITY;
  return outputCurrent;
}

float readTotalCurrent() {
  float A = readRawCurrent(pin_A);
  float B = readRawCurrent(pin_B);
  float outputCurrent = A + B;
  
  errorVals.add(abs(A-B));
  if (errorVals.size() > 10) {
    errorVals.remove(0);
    
    float total = 0;
    for (int i = 0; i < errorVals.size(); i++) { total += errorVals.get(i); }
    currentError = total / errorVals.size();
  } else { currentError = 0; }
  
  return outputCurrent;
}
