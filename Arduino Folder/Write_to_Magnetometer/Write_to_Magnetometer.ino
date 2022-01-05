#include <Wire.h> //I2C Arduino Library
#define address 0x1E //0011110b, I2C 7bit address of Magnetometer

int x,y,z; //triple axis data

void setup(){
  //Initialize Serial and I2C communications
  Serial.begin(9600);
  Wire.begin();
  
  //Put the Magnetometer IC into the correct operating mode
  Wire.beginTransmission(address); //open communication with Magnetometer
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();
}

void loop(){
  //Tell the Magnetometer where to begin reading data
  Wire.beginTransmission(address);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  
 
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(address, 6);
  x = Wire.read()<<8; //X msb
  x |= Wire.read(); //X lsb
  z = Wire.read()<<8; //Z msb
  z |= Wire.read(); //Z lsb
  y = Wire.read()<<8; //Y msb
  y |= Wire.read(); //Y lsb
  
  //Print out values of each axis
  //x is y orientation (The one thing an accelerometer cannot measure)
  //y is UNKNOWN
  //z is up and down, where looking down increases the value
  Serial.println(x);
  //Serial.print(" ");
  //Serial.println(y);
  //Serial.print(" ");
  //Serial.println(z);
  
  delay(50);
}
