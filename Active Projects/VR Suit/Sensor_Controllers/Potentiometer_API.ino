#define AnalIn_0 A0
#define AnalIn_1 A1
#define AnalIn_2 A2
#define AnalIn_3 A3
#define AnalIn_4 A4
#define AnalIn_5 A5

//5 Motors per data line
//Tie all 6 data lines and all 6 clock lines together
#define DataOut 2
#define ClkOut 3
#define ClkPulseLen 1000

#include <LinkedList.h>
LinkedList<int> sensorData = LinkedList<int>();

void setupSensors() {
  pinMode(AnalIn_0,INPUT_PULLUP);
  pinMode(AnalIn_1,INPUT_PULLUP);
  pinMode(AnalIn_2,INPUT_PULLUP);
  pinMode(AnalIn_3,INPUT_PULLUP);
  pinMode(AnalIn_4,INPUT_PULLUP);
  pinMode(AnalIn_5,INPUT_PULLUP);
  
  pinMode(DataOut,OUTPUT);
  pinMode(ClkOut,OUTPUT);
  clearOutputs();
}

void updateSensors() {
  clearOutputs();
  
  digitalWrite(DataOut,HIGH);
  pulseSensorClock();
  digitalWrite(DataOut,LOW);
  
  for (int i = 0; i < 5; i++) {
    sensorData.add(analogRead(AnalIn_0));
    sensorData.add(analogRead(AnalIn_1));
    sensorData.add(analogRead(AnalIn_2));
    sensorData.add(analogRead(AnalIn_3));
    sensorData.add(analogRead(AnalIn_4));
    sensorData.add(analogRead(AnalIn_5));
    pulseSensorClock();
  }
}

void clearOutputs() {
  digitalWrite(DataOut,LOW);
  for (int i = 0; i < 6; i++) { pulseSensorClock(); }
}

void pulseSensorClock() {
  digitalWrite(ClkOut,HIGH);
  delayMicroseconds(ClkPulseLen);
  digitalWrite(ClkOut,LOW);
}

int getSensorOutput(int ID) { return sensorData.get(ID); }

bool sensorDisconnected() {
  for (int i = 0; i < sensorData.size(); i++) {
    if ((sensorData.get(i) == 0) || (sensorData.get(i) == 1023)) {
      return true;
    }
  }
  return false;
}
