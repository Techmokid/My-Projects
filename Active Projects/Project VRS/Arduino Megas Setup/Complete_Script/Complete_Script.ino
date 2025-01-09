#include<LinkedList.h>

#define MAX_POWER_RATING 0.05

int sensorDataArr[40];

//All torques must be in the same units. I am using Kg/cm for this example
//Does not matter what units, just so long as they match when you call "applyTorqueToJoint(ID,torque)"
float motorStrengths[] = {
  6.5,  //ID 1
  6.5,  //ID 2
  0.18  //ID 3
};

void setup() {
  Serial.begin(1000000);
  setupSensors();
}

String serialLines;
unsigned long prevMillis = 0;
void loop() {
  updateSerial();
  updateSensors();

  //Replace this with the input from the PC
  serialLines = readLine();
  //"ID:torque"
  while(serialLines != "") {
    if (serialLines != "") {
      //Split up the incoming line into "ID" and "Trq"
      Serial.println("W.I.P");
      int ID = 0;
      float Torque = 0;
      applyTorqueToJoint(ID,Torque);
    }
    serialLines = readLine();
  }

  if(sensorDisconnected()) {
    emergencyShutoff();
    
    Serial.println("\tDISCONNECT ERROR");
    for(int i = 0; i < sizeof(sensorDataArr)/sizeof(sensorDataArr[0]); i++) {
      if ((sensorDataArr[i] < 4) || (sensorDataArr[i] > 1018)) {
        Serial.println("\tSENSOR DISCONNECT ID " + String(i) + "\tWITH VALUE " + String(sensorDataArr[i]));
      } else {
        Serial.println("\tPERFECTLY FINE    ID " + String(i) + "\tWITH VALUE " + String(sensorDataArr[i]));
      }
    }
    while(true) {}
  }
  
  for(int i = 0; i < sizeof(sensorDataArr)/sizeof(sensorDataArr[0]); i++) {
    Serial.write(char(highByte(sensorDataArr[i])));
    Serial.write(char(lowByte(sensorDataArr[i])));
  }
  Serial.println();
  
  float timeDiff = micros() - prevMillis;
  float secondsPerIteration = timeDiff/1000000;
  float refreshRate = 1/secondsPerIteration;
  Serial.println(String(refreshRate) + " Hz");
  prevMillis = micros();
}
