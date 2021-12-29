#include <Wire.h>

float acc_x,acc_y,acc_z,temp,gyro_x,gyro_y,gyro_z;
float gyro_x_cal = 0;
float gyro_y_cal = 0;
float gyro_z_cal = 0;
float currentTime = 0;
bool accelerometer = false;
bool temperature = true;
bool gyroscope = false;

void setup() {
  Serial.begin(115200);
  Wire.begin();                                                        //Start I2C as master
  
  //Activate the MPU-6050
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x6B);                                                    //Send the requested starting register
  Wire.write(0x00);                                                    //Set the requested starting register
  Wire.endTransmission();                                             
  //Configure the accelerometer (+/-8g)
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x1C);                                                    //Send the requested starting register
  Wire.write(0x10);                                                    //Set the requested starting register
  Wire.endTransmission();                                             
  //Configure the gyro (500dps full scale)
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x1B);                                                    //Send the requested starting register
  Wire.write(0x08);                                                    //Set the requested starting register
  Wire.endTransmission();
  
  int i = 0;
  double numberOfLoops = 2000;
  while (i<numberOfLoops) {
    Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
    Wire.write(0x3B);                                                    //Send the requested starting register
    Wire.endTransmission();                                              //End the transmission
    Wire.requestFrom(0x68,14);                                           //Request 14 bytes from the MPU-6050
    while(Wire.available() < 14);                                        //Wait until all the bytes are received
    acc_x = Wire.read()<<8|Wire.read();
    acc_y = Wire.read()<<8|Wire.read();
    acc_z = Wire.read()<<8|Wire.read();
    temp = Wire.read()<<8|Wire.read();
    gyro_x_cal += Wire.read()<<8|Wire.read();
    gyro_y_cal += Wire.read()<<8|Wire.read();
    gyro_z_cal += Wire.read()<<8|Wire.read();
    i++;
  }
  
  gyro_x_cal /= numberOfLoops;
  gyro_y_cal /= numberOfLoops;
  gyro_z_cal /= numberOfLoops;
  
  currentTime = millis();
}

void loop() {
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x3B);                                                    //Send the requested starting register
  Wire.endTransmission();                                              //End the transmission
  Wire.requestFrom(0x68,14);                                           //Request 14 bytes from the MPU-6050
  while(Wire.available() < 14);                                        //Wait until all the bytes are received
  acc_x = Wire.read()<<8|Wire.read();
  acc_y = Wire.read()<<8|Wire.read();
  acc_z = Wire.read()<<8|Wire.read();
  temp = Wire.read()<<8|Wire.read();
  gyro_x += Wire.read()<<8|Wire.read();
  gyro_y += Wire.read()<<8|Wire.read();
  gyro_z += Wire.read()<<8|Wire.read();
  
  gyro_x -= gyro_x_cal;
  gyro_y -= gyro_y_cal;
  gyro_z -= gyro_z_cal;
  
  if (accelerometer) {Serial.println(String(acc_x) + " " + String(acc_y) + " " + String(acc_z));}
  if (temperature) {Serial.println(" "+String(temp));}
  if (gyroscope) {Serial.println(" "+String(gyro_x) + " " + String(gyro_y) + " " + String(gyro_z));}
  
  if (currentTime+5000 < millis()) {
    currentTime = millis();
  }
}

void resetGyroscope() {
  gyro_x = 0;
  gyro_y = 0;
  gyro_z = 0;
}
