#include <CapacitiveButtonRead.h>
#include <Wire.h>

#define MPUAddr 0x68    //I2C address of the MPU-6050
#define ArrayLength 10
#define zero_x 1.569
#define zero_y 1.569
#define zero_z 1.569

int16_t AcX;
int16_t AcY;
int16_t AcZ;
int16_t Temp;
int16_t GyX;
int16_t GyY;
int16_t GyZ;

float angle_x_arr[ArrayLength];
float angle_z_arr[ArrayLength];
float noteToPlay = 0;
float previousNote = 0;

bool playingNote = true;

CapacitiveButtonRead myLib;

void setup() {
  Serial.begin(9600);
  Serial.println("Serial Connection Established!\n");
  
  Wire.begin();
  Serial.println("-Wire Library Initialized...");
  Wire.beginTransmission(MPUAddr); //open communication with MPU-6050
  Wire.write(0x6B);  //PWR_MGMT_1 register
  Wire.write(0);     //Set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.println("-MPU-6050 Initialized...");
  
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(11,INPUT);
  pinMode(12,INPUT);
  pinMode(13,INPUT);
  Serial.println("-Digital Pins Set To Input...");
  
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  Serial.println("-Analog Pins Set To Input...");
  Serial.println("\nSetup Complete!\n\n\n");
}

void loop() {
  AccelerometerUpdate();
  playingNote = false;
  
  float xv=(analogRead(A0)/1024.0*5-zero_x)/0.3;
  float yv=(analogRead(A1)/1024.0*5-zero_y)/0.3;
  float zv=(analogRead(A2)/1024.0*5-zero_z)/0.3;
  
  float angle_x =atan2(-xv,-zv)*57.2957795+180;
  float angle_z =atan2(-xv,-yv)*57.2957795+180;
  
  addArr(angle_x_arr,angle_x);
  addArr(angle_z_arr,angle_z);
  
  float Average_X_Angle = 10 * (averageArr(angle_x_arr) - 85);
  float Average_Z_Angle = 10 * (averageArr(angle_z_arr) - 64);
  
  bool upperRegister = Average_X_Angle < 0;
  
  //              C,A,G,G#,F,E,D,Eb,C#(Low),C(Low),B,Bb,Tone  ,B_Ln,E_Ln
  if (!upperRegister) {
    testToneCombo(1,1,1,0 ,1,1,1,0 ,1      ,1     ,1,1 ,261.63,true,false); //Low C
    testToneCombo(1,1,1,0 ,1,1,1,0 ,0      ,1     ,1,1 ,261.63,true,false); //Low C
    testToneCombo(1,1,1,0 ,1,1,1,0 ,1      ,0     ,1,1 ,277.18,true,false); //Low C#
    testToneCombo(1,1,1,0 ,1,1,1,0 ,0      ,0     ,1,1 ,293.66,true,false); //Low D
    testToneCombo(1,1,1,0 ,1,1,1,1 ,0      ,0     ,1,1 ,311.13,true,false); //Low Eb
    
    testToneCombo(1,1,1,0 ,1,1,0,0 ,0      ,0     ,1,1 ,329.63,true,true);  //Low E
    testToneCombo(1,1,1,0 ,1,0,0,0 ,0      ,0     ,1,1 ,349.23,true,true);  //Low F
    testToneCombo(1,1,1,0 ,1,0,1,0 ,0      ,0     ,1,1 ,349.23,true,true);  //Low F Improper Added F#
    testToneCombo(1,1,1,0 ,0,0,1,0 ,0      ,0     ,1,1 ,369.99,true,true);  //Low F#
    testToneCombo(1,1,1,0 ,0,0,0,0 ,0      ,0     ,1,1 ,392.00,true,true);  //Low G
    testToneCombo(1,1,1,1 ,0,0,0,0 ,0      ,0     ,1,1 ,415.30,true,true);  //Low G#
    testToneCombo(1,1,0,0 ,0,0,0,0 ,0      ,0     ,1,1 ,440.00,true,true);  //Low A
    
    testToneCombo(1,0,0,0 ,0,0,0,0 ,0      ,0     ,1,1 ,466.16,false,true); //Low Bb
    testToneCombo(1,0,0,0 ,0,0,0,0 ,0      ,0     ,0,1 ,466.16,false,true); //Low Bb
    testToneCombo(1,0,0,0 ,0,0,0,0 ,0      ,0     ,1,0 ,493.88,false,true); //Low B
    testToneCombo(1,0,0,0 ,0,0,0,0 ,0      ,0     ,0,0 ,523.25,false,true); //Mid C
    testToneCombo(0,0,0,0 ,0,0,0,0 ,0      ,0     ,0,0 ,554.36,false,true); //Mid C#
  } else {
    testToneCombo(1,1,1,0 ,1,1,1,0 ,1      ,1     ,1,1 ,523.25,true,false); //Mid C  Improper Lower Fingering
    testToneCombo(1,1,1,0 ,1,1,1,0 ,0      ,1     ,1,1 ,523.25,true,false); //Mid C  Improper Lower Fingering
    testToneCombo(1,1,1,0 ,1,1,1,0 ,1      ,0     ,1,1 ,554.36,true,false); //Mid C# Improper Lower Fingering
    testToneCombo(1,1,1,0 ,1,1,1,0 ,0      ,0     ,1,1 ,587.32,true,false); //Mid D  Improper Lower Fingering
    testToneCombo(1,1,1,0 ,1,1,1,1 ,0      ,0     ,1,1 ,622.26,true,false); //Mid Eb Improper Lower Fingering
    
    testToneCombo(0,1,1,0 ,1,1,1,0 ,0      ,0     ,1,1 ,587.32,true,false); //Mid D
    testToneCombo(0,1,1,0 ,1,1,1,1 ,0      ,0     ,1,1 ,622.26,true,false); //Mid Eb
    
    testToneCombo(1,1,1,0 ,1,1,0,0 ,0      ,0     ,1,1 ,659.26,true,true);  //Mid E
    testToneCombo(1,1,1,0 ,1,0,0,0 ,0      ,0     ,1,1 ,698.46,true,true);  //Mid F
    testToneCombo(1,1,1,0 ,1,0,1,0 ,0      ,0     ,1,1 ,698.46,true,true);  //Mid F Improper Added F#
    testToneCombo(1,1,1,0 ,0,0,1,0 ,0      ,0     ,1,1 ,739.99,true,true);  //Mid F#
    testToneCombo(1,1,1,0 ,0,0,0,0 ,0      ,0     ,1,1 ,783.99,true,true);  //Mid G
    testToneCombo(1,1,1,1 ,0,0,0,0 ,0      ,0     ,1,1 ,830.61,true,true);  //Mid G#
    testToneCombo(1,1,0,0 ,0,0,0,0 ,0      ,0     ,1,1 ,880.00,true,true);  //Mid A
    
    testToneCombo(1,0,0,0 ,0,0,0,0 ,0      ,0     ,1,1 ,932.33,false,true); //Mid Bb
    testToneCombo(1,0,0,0 ,0,0,0,0 ,0      ,0     ,0,1 ,932.33,false,true); //Mid Bb
    testToneCombo(1,0,0,0 ,0,0,0,0 ,0      ,0     ,1,0 ,987.77,false,true); //Mid B
    testToneCombo(1,0,0,0 ,0,0,0,0 ,0      ,0     ,0,0 ,1046.50,false,true);//High C
    testToneCombo(0,0,0,0 ,0,0,0,0 ,0      ,0     ,0,0 ,1108.73,false,true);//High C#
  }

  testToneCombo(0,1,1,0 ,0,0,0,0 ,0      ,0     ,1,1 ,1174.66,true,true);   //High D
  testToneCombo(1,1,1,1 ,1,1,1,1 ,0      ,0     ,1,1 ,1244.51,true,false);  //High Eb
  testToneCombo(1,1,0,0 ,1,1,0,0 ,0      ,0     ,1,1 ,1318.51,true,true);   //High E
  testToneCombo(1,0,1,0 ,1,0,1,0 ,0      ,0     ,1,1 ,1396.91,true,true);   //High F
  testToneCombo(1,0,1,0 ,0,0,1,0 ,0      ,0     ,1,1 ,1479.98,true,true);   //High F#
  testToneCombo(1,1,1,0 ,0,0,0,0 ,0      ,0     ,0,0 ,1567.98,false,true);  //High G
  testToneCombo(0,1,1,1 ,0,0,0,0 ,0      ,0     ,0,0 ,1661.22,false,true);  //High G#
  testToneCombo(0,1,0,0 ,1,0,0,0 ,0      ,0     ,0,0 ,1760.00,true,true);   //High A
  testToneCombo(0,0,0,0 ,1,0,0,0 ,0      ,0     ,0,0 ,1864.66,true,true);   //High Bb
  testToneCombo(1,0,0,0 ,1,0,0,0 ,0      ,0     ,0,0 ,1864.66,true,true);   //High Bb
  testToneCombo(1,0,1,0 ,0,0,0,0 ,0      ,0     ,0,0 ,1975.53,true,true);   //High B
  testToneCombo(1,1,1,1 ,1,0,0,0 ,0      ,0     ,0,0 ,2093.00,false,true);  //Very High C
  
  if ((noteToPlay != previousNote) or (!playingNote)) {
    noTone(A6);
    previousNote = noteToPlay;
    
    if (playingNote) {
      tone(A6,noteToPlay + Average_Z_Angle * noteToPlay / 10);
      Serial.println(noteToPlay + Average_Z_Angle * noteToPlay / 2000);
    }
  }
}

float testToneCombo(bool a,bool b,bool c,bool d,bool e,bool f,bool g,bool h,bool i,bool j,bool k,bool l,float note,bool B_Leniency,bool E_Leniency) {
  if (myLib.ReadPin2()==a) {
    if (myLib.ReadPin3()==b) {
      if (myLib.ReadPin4()==c) {
        if (myLib.ReadPin5()==d) {
          if (myLib.ReadPin6()==e) {
            if (myLib.ReadPin7()==f) {
              if (myLib.ReadPin8()==g) {
                if ((myLib.ReadPin9()==h) or E_Leniency) {
                  if (myLib.ReadPin10()==i) {
                    if (myLib.ReadPin11()==j) {
                      if (B_Leniency) {
                        if (myLib.ReadPin12() or myLib.ReadPin13()) {
                          noteToPlay = note;
                          playingNote = true;
                        }
                      } else {
                        if (myLib.ReadPin12()==k) {
                          if (myLib.ReadPin13()==l) {
                            noteToPlay = note;
                            playingNote = true;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return true;
}

float averageArr(float arr[]) {
  int result = 0;
  for (int i=0; i<ArrayLength; i++) {
    result+= arr[i];
  }
  
  return (result/ArrayLength);
}

void addArr(float arr[], float val) {
  int i = 0;
  while (i < ArrayLength - 1) {
    arr[i] = arr[i+1];
    i += 1;
  }
  
  arr[i] = val;
}

void AccelerometerUpdate() {
  Wire.beginTransmission(MPUAddr);
  Wire.write(0x3B);  //Starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  
  Wire.requestFrom(MPUAddr,14,true);  //request a total of 14 registers
  AcX = Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY = Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Temp = Wire.read()<<8|Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
  return true;
}
