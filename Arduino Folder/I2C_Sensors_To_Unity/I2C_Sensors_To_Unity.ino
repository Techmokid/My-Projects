#include <Wire.h>
#define MagAddr 0x1E                  //I2C address of Magnetometer
#define MPUAddr 0x68                  //I2C address of the MPU-6050

int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;  //Declare MPU-6050 variables
int MagX,MagY,MagZ;                   //Declare HMC5883L variables

void setup(){
  Serial.begin(9600);
  Serial.setTimeout(100);
  Wire.begin();
  
  Wire.beginTransmission(MPUAddr);    //Open communication with MPU-6050
  Wire.write(0x6B);                   //PWR_MGMT_1 register
  Wire.write(0);                      //Set to zero (wakes up the MPU-6050)
  Wire.endTransmission();

  Wire.beginTransmission(MagAddr);    //Open communication with Magnetometer
  Wire.write(0x02);                   //Select mode register
  Wire.write(0x00);                   //Continuous measurement mode
  Wire.endTransmission();
}

void loop(){
  Wire.beginTransmission(MagAddr);
  Wire.write(0x03);                   //Select register 3, X MSB register
  Wire.endTransmission();

  Wire.requestFrom(MagAddr, 6);
  MagX = Wire.read()<<8;              //X msb
  MagX |= Wire.read();                //X lsb
  MagY = Wire.read()<<8;              //Z msb
  MagY |= Wire.read();                //Z lsb
  MagZ = Wire.read()<<8;              //Y msb
  MagZ |= Wire.read();                //Y lsb
  
  Wire.beginTransmission(MPUAddr);
  Wire.write(0x3B);                   //Starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission();
  
  Wire.requestFrom(MPUAddr,14,true);  //Request a total of 14 registers
  AcX = Wire.read()<<8|Wire.read();   //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY = Wire.read()<<8|Wire.read();   //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read()<<8|Wire.read();   //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read()<<8|Wire.read();   //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read()<<8|Wire.read();   //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read()<<8|Wire.read();   //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read()<<8|Wire.read();   //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
  String Sentence = "|" + String(AcX);
  Sentence += "|" + String(AcY);
  Sentence += "|" + String(AcZ);
  Sentence += "|" + String(Tmp/340.00+36.53);  //Equation for temperature in degrees C from datasheet
  Sentence += "|" + String(GyX);
  Sentence += "|" + String(GyY);
  Sentence += "|" + String(GyZ);
  Sentence += "|" + String(MagX);
  Sentence += "|" + String(MagY);
  Sentence += "|" + String(MagZ) + "|";
  Serial.println(Sentence);
}
