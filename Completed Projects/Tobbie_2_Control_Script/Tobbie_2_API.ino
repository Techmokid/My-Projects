//Magnetometer variables
//#include <SparkFun_MAG3110.h>
//MAG3110 mag = MAG3110();
//int magX,magY,magZ;

//Accelerometer data
//#include <Wire.h>
//#include <MMA8653.h>
//MMA8653 accel;

//Combined accelerometer and magnetometer
//#include <LSM303AGR_ACC_Sensor.h>
//#include <LSM303AGR_MAG_Sensor.h>
//#if defined(ARDUINO_SAM_DUE)
//#define DEV_I2C Wire1   //Define which I2C bus is used. Wire1 for the Arduino Due
//#define SerialPort Serial
//#else
//#define DEV_I2C Wire    //Or Wire
//#define SerialPort Serial
//#endif
//LSM303AGR_ACC_Sensor Acc(&DEV_I2C);
//LSM303AGR_MAG_Sensor Mag(&DEV_I2C);

//LED display variables
int myRows[] = {21,22,23,24,25};
int myColumbs[] = {4,7,3,6,10};
bool LEDs[5][5] = {};

//Speaker variables
bool speakerInit = false;
bool speakerOn = false;
bool speakerWaveHalf = false;
unsigned long speakerPrevMillis = 0;
unsigned long speakerTimeInterval = 0;

void walkForwards(bool walk) { pinMode(13,OUTPUT); digitalWrite(13,walk); }
void walkBackwards(bool walk) { pinMode(14,OUTPUT); digitalWrite(14,walk); }
void turnRight(bool walk) { pinMode(15,OUTPUT); digitalWrite(15,walk); }
void turnLeft(bool walk) { pinMode(16,OUTPUT); digitalWrite(16,walk); }

void startDistanceSensors() { pinMode(12,OUTPUT); digitalWrite(12,HIGH); }
float readLeftDist() { pinMode(1,INPUT); return analogRead(1); }
float readRightDist() { pinMode(2,INPUT); return analogRead(2); }

//void startMagnetometer() {
//  mag.initialize(); //Initializes the mag sensor
//  mag.start();      //Puts the sensor in active mode
//}

//void readMagnetometer() { mag.readMag(&magX,&magY,&magZ); }
//float getMagnetometerX() { return magX; }
//float getMagnetometerY() { return magY; }
//float getMagnetometerZ() { return magZ; }

//void startAccelerometer() { accel.begin(false, 2); } // 8-bit mode, 2g range
//void readAccelerometer() { accel.update(); }
//float getAccelerometerX() { return (float)accel.getX() * 0.0156; }
//float getAccelerometerY() { return (float)accel.getY() * 0.0156; }
//float getAccelerometerZ() { return (float)accel.getZ() * 0.0156; }

//void startAccMag() {
//  DEV_I2C.begin(); 
//  Acc.begin();
//  Acc.Enable();
//  Acc.EnableTemperatureSensor();
//  Mag.begin();
//  Mag.Enable();

//  int32_t accelerometer[3];
//  Acc.GetAxes(accelerometer);

  // Read temperature LSM303AGR.
//  float temperature;
//  Acc.GetTemperature(&temperature);
  
  // Read magnetometer LSM303AGR.
//  int32_t magnetometer[3];
//  Mag.GetAxes(magnetometer);

  // Output data.
  //SerialPort.print("| Acc[mg]: ");
  //SerialPort.print(accelerometer[0]);
  //SerialPort.print(" ");
  //SerialPort.print(accelerometer[1]);
  //SerialPort.print(" ");
  //SerialPort.print(accelerometer[2]);
  //SerialPort.print(" | Mag[mGauss]: ");
  //SerialPort.print(magnetometer[0]);
  //SerialPort.print(" ");
  //SerialPort.print(magnetometer[1]);
  //SerialPort.print(" ");
  //SerialPort.print(magnetometer[2]);
  //SerialPort.print(" | Temp[C]: ");
  //SerialPort.print(temperature, 2);
  //SerialPort.println(" |");
//}

void startTobbie2() {
  clearDisplay();
  updateDisplay();
}

void clearDisplay() {
  for(int x = 0; x < 5; x++) {
    for (int y = 0; y < 5; y++) {
      LEDs[x][y] = 0;
    }
  }
}
void clearDisplayNow() {
  for(int x = 0; x < 5; x++) {
    for (int y = 0; y < 5; y++) {
      setLED(x,y,false,false);
    }
  }
}

void updateDisplay() {
  for(int x = 0; x < 5; x++) {
    for (int y = 0; y < 5; y++) {
      setLED(x,y,LEDs[x][y]);
      delay(0.5);
      setLED(x,y,false,false);
    }
  }
}

void setDisplay(int LED[5][5]) {
  clearDisplayNow();
  for(int y = 0; y < 5; y++) {
    for (int x = 0; x < 5; x++) {
      LEDs[x][y]=LED[y][x];
    }
  }
  updateDisplay();
}

void setPin(int pin, bool status) {
  pinMode(pin,OUTPUT);
  digitalWrite(pin,status);
}

void setLED(int x, int y, bool status) { setLED(x,y,status,true); }
void setLED(int x, int y, bool status, bool makeChangesToMemory) {
  if (makeChangesToMemory) {
    LEDs[x][y] = status;
  }
  setPin(myColumbs[x],!status);
  setPin(myRows[y],status);
}

void setMicLED(bool status) { setPin(10,!status); setPin(28,status); }

bool getButton(int ID) {
  if (ID == 0) {
    pinMode(5,INPUT);
    return !digitalRead(5);
  } else if (ID == 1) {
    pinMode(11,INPUT);
    return !digitalRead(11);
  } else { return 0; }
}

void startSpeaker() { pinMode(27,OUTPUT); }
void stopTone() {speakerOn = false; digitalWrite(27,LOW); };
void setTone(float frequency) {
  if (!speakerInit) { startSpeaker(); }
  speakerOn = true;
  speakerTimeInterval = 1000000/frequency;
}
void playMelody(int notes[], int durations[], int numberOfNotes) {
  for (int thisNote = 0; thisNote < numberOfNotes; thisNote++) {
    int noteDuration = 1000 / durations[thisNote];

    setTone(notes[thisNote]);
    int pauseBetweenNotes = noteDuration * 2;

    delayYield(pauseBetweenNotes);
    stopTone();
  }
}

void updateTone() {
  if (speakerOn) {
    if (micros() - speakerPrevMillis > speakerTimeInterval/2.2) {
      speakerPrevMillis = micros();
      digitalWrite(27,speakerWaveHalf);
      speakerWaveHalf = !speakerWaveHalf;
    }
  }
}

void delayYield(unsigned long time) {
  unsigned long prevMillis = millis();
  while(millis() - prevMillis < time) {
    updateDisplay();
    updateTone();
  }
}

//pins 3,0,4,1,10,2 are analogIn
