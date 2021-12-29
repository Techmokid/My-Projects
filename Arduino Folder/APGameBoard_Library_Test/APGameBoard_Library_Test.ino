//This code just reads from the tilt and compass sensors.
//The tilt sensor is the Accelerometer, the compass sensor is the Magnetometer, change in motion is recorded by the Gyroscope, and I added in a Temperature sensor just because I can :)

#include <APGameBoard.h>

//Initialise the APGameBoard Library
APGameBoard myLib;

void setup() {
  myLib.setupI2C();
}

void loop() {
  //Update the I2C data before continuing
  myLib.updateI2C();
  
  
  //This looks complex, but essentially each sensor returns an integer, so I convert it to a string and add it to a string variable. Quite simple, but just looks confusing. Sorry about that!
  String AccelerometerData = "AccX: " + String(myLib.accX()) + "\tAccY: " + String(myLib.accY()) + "\tAccZ: " + String(myLib.accZ());
  String MagnetometerData = "MagX: " + String(myLib.magX()) + "\tMagY: " + String(myLib.magY()) + "\tMagZ: " + String(myLib.magZ());
  String GyroscopeData = "GyroX: " + String(myLib.gyroX()) + "\tGyroY: " + String(myLib.gyroY()) + "\tGyroZ: " + String(myLib.gyroZ());
  String TemperatureData = "Temp: " + String(myLib.temp());
  
  //Now we just print the result! NOTE: If the sensors only return "-1", then there is a connection problem with the sensors. Check to make sure no pins have come loose.
  Serial.println(AccelerometerData);
  Serial.println(MagnetometerData);
  Serial.println(GyroscopeData);
  Serial.println(TemperatureData);
  Serial.println();
  
  //This just pauses the Arduino for 1 second so that we can easily read the output
  delay(1000);
}
