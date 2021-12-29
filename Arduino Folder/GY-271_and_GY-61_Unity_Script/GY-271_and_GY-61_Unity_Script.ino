#include<Wire.h>
#define MagAddr 0x1E    //I2C address of Magnetometer

int MagX,MagY,MagZ;
float MagneticTiltX[10];
float MagneticTiltY[10];
float MagneticTiltZ[10];

void setup(){
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  
  Serial.begin(9600);
  Wire.begin();

  Wire.beginTransmission(MagAddr); //open communication with Magnetometer
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();
}

void loop(){
  Wire.beginTransmission(MagAddr);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  
  shiftArray(MagneticTiltX);
  shiftArray(MagneticTiltY);
  shiftArray(MagneticTiltZ);
  
  Wire.requestFrom(MagAddr, 6);
  MagX = Wire.read()<<8; //X msb
  MagX |= Wire.read(); //X lsb
  MagY = Wire.read()<<8; //Z msb
  MagY |= Wire.read(); //Z lsb
  MagZ = Wire.read()<<8; //Y msb
  MagZ |= Wire.read(); //Y lsb
  
  MagneticTiltX[10] = analogRead(0);
  MagneticTiltY[10] = analogRead(1);
  MagneticTiltZ[10] = analogRead(2);
  
  Serial.print(averageArray(MagneticTiltX));
  Serial.print(" ");
  Serial.print(averageArray(MagneticTiltY));
  Serial.print(" ");
  Serial.println(averageArray(MagneticTiltZ));
}

void shiftArray(float arr[10]) {
  for(int i = 0; i < 10; i++){
    arr[i] = arr[i+1];
  }
}

float averageArray(float arr[10]) {
  float data = 0;
  
  for(int i = 0; i < 10; i++){
    data += arr[i];
  }
  
  return (data/11);
}

