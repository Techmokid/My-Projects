//EEPROM.read(0) = 400        - This is the z offset from the tray (How far away from the main wall the trays are on)
//EEPROM.read(1) = 220        - This is the height offset to the trays
//EEPROM.read(2) = 76         - This is the average width of each tray
//EEPROM.read(3) = 46.25      - This is the average height of each tray
//EEPROM.read(4) = 14.5       - This is an internal variable for X offset of mechanism from the left of the trays
//EEPROM.read(5) = 0          - This tells the system whether to activate the "dev lock" (0 is off, 1 is on)
//EEPROM.read(6) = 0.003      - This is the variable for how fast the servos should rotate around the circle
//EEPROM.read(7) = 200        - This is the radius of the drawn circle

//Trays (28 across and 40 high) are 7.6cm wide and 4.625 high
float lastTimer = 0;
float laserDuration = 5; //Number of seconds to display the laser for

void startLaser() {
  if ((Item_Position_X >= 0) && (Item_Position_Y >= 0)) {
    servo_X.oneTimeActive = true;
    digitalWrite(p.pinToGPIO(laserPin),HIGH);
    lastTimer = millis();
    running = true;
  }
}

void updateLaser() {
  if (!running) { return; }
  
  servo_X.updateServo();
  servo_Y.updateServo();
  
  if (mountMode) { return; }
  
  if ((millis() - lastTimer > laserDuration * 1000) && running) {
    digitalWrite(p.pinToGPIO(laserPin),LOW);
    running = false;
    
    servo_X.write(90);
    servo_Y.write(0);
    
    unsigned long temp = millis();
    while (millis() - temp < 1000) { servo_X.updateServo(); servo_Y.updateServo(); }
    return;
  }
  
  //For X we just multiply the number of trays across by the width of a tray
  //Then we subtract half of the trays to make it centralised
  float X_Offset = sin(millis()*readValueFromEEPROM(6))*readValueFromEEPROM(7);
  float laser_pos_X = readValueFromEEPROM(2)*(float(Item_Position_X - readValueFromEEPROM(4))) + X_Offset;
  float result_X = servo_X.radToDeg(atan(laser_pos_X / readValueFromEEPROM(0)));
  
  servo_X.write(result_X + 90);
  
  //For Y we multiply the number of trays across by the width of a tray
  //Then we add the height above the trays the mechanism sits
  float Y_Offset = cos(millis()*readValueFromEEPROM(6))*readValueFromEEPROM(7);
  float laser_pos_Y = float(Item_Position_Y)*readValueFromEEPROM(3) + readValueFromEEPROM(1) + Y_Offset;
  float result_Y = servo_X.radToDeg(atan(laser_pos_Y / (readValueFromEEPROM(0) / cos(result_X/180*3.14159))));
  
  servo_Y.write(result_Y);
  
  return;
}
