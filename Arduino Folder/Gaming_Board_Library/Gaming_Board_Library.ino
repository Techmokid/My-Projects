#include<Wire.h>
#define MagAddr 0x1E    //I2C address of Magnetometer
#define MPUAddr 0x68    //I2C address of the MPU-6050

int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int MagX,MagY,MagZ;

void setup(){
  setupI2C();
}

void loop() {}

void setupI2C() {
  Serial.begin(9600);
  Wire.begin();
  
  Wire.beginTransmission(MPUAddr); //open communication with MPU-6050
  Wire.write(0x6B);  //PWR_MGMT_1 register
  Wire.write(0);     //Set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  Wire.beginTransmission(MagAddr); //open communication with Magnetometer
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();
}

void updateI2C(){
  Wire.beginTransmission(MagAddr);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();

  Wire.requestFrom(MagAddr, 6);
  MagX = Wire.read()<<8; //X msb
  MagX |= Wire.read(); //X lsb
  MagY = Wire.read()<<8; //Z msb
  MagY |= Wire.read(); //Z lsb
  MagZ = Wire.read()<<8; //Y msb
  MagZ |= Wire.read(); //Y lsb
  
  Wire.beginTransmission(MPUAddr);
  Wire.write(0x3B);  //Starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  
  Wire.requestFrom(MPUAddr,14,true);  //request a total of 14 registers
  AcX = Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY = Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read()<<8|Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}

int16_t accX() {
  return AcX;
}

int16_t accY() {
  return AcY;
}

int16_t accZ() {
  return AcZ;
}

int16_t temp() {
  return Tmp;
}

int16_t gyroX() {
  return GyX;
}

int16_t gyroY() {
  return GyY;
}

int16_t gyroZ() {
  return GyZ;
}

int magX() {
  return MagX;
}

int magY() {
  return MagY;
}

int magZ() {
  return MagZ;
}
