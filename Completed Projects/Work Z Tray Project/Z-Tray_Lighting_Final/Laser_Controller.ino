//EEPROM.read(0) = 400        - This is the z offset from the tray (How far away from the main wall the trays are on)
//EEPROM.read(1) = 220        - This is the height offset to the top of the trays
//EEPROM.read(2) =            - This is the total width of the trays
//EEPROM.read(3) =            - This is the total height of the trays
//EEPROM.read(4) = 14.5       - This is an internal variable for X offset of mechanism from the left of the trays
//EEPROM.read(5) = 0          - This tells the system whether to activate the "dev lock" (0 is off, 1 is on)
//EEPROM.read(6) = 0.003      - This is the variable for how fast the servos should rotate around the circle
//EEPROM.read(7) = 200        - This is the radius of the drawn circle
//EEPROM.read(8) =            - This is the number of trays wide
//EEPROM.read(9) =            - This is the number of trays high
//EEPROM.read(10) =           - This is the tray circling enable
//EEPROM.read(11) =           - This is the servo X start value calibration variable
//EEPROM.read(11) =           - This is the servo X end   value calibration variable
//EEPROM.read(11) =           - This is the servo Y start value calibration variable
//EEPROM.read(11) =           - This is the servo Y end   value calibration variable

//Trays (28 across and 40 high) are 7.6cm wide and 4.625 high
float lastTimer = 0;
float laserDuration = 5; //Number of seconds to display the laser for

void startLaser() {
  if ((Item_Position_X >= 0) && (Item_Position_Y >= 0)) {
    //servo_X.oneTimeActive = true;
    digitalWrite(p.pinToGPIO(laserPin),HIGH);
    lastTimer = millis();
    running = true;
    
    width_of_tray = readValueFromEEPROM(2)/readValueFromEEPROM(8);
    laser_pos_X = -readValueFromEEPROM(4) + float(Item_Position_X)*width_of_tray - width_of_tray/2;

    height_of_tray = readValueFromEEPROM(3)/readValueFromEEPROM(9);
    laser_pos_Y = readValueFromEEPROM(1) + float(Item_Position_Y)*height_of_tray - height_of_tray/2;
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
  if (readValueFromEEPROM(10) > 0) { laser_pos_X += sin(millis()*readValueFromEEPROM(6))*readValueFromEEPROM(7); }
  Serial.println("laser_pos_X: " + String(laser_pos_X));
  float result_X = 90 + servo_X.radToDeg(atan(laser_pos_X / readValueFromEEPROM(0)));
  servo_X.write(result_X);
  Serial.println("X:" + String(result_X));
  
  //For Y we multiply the number of trays across by the width of a tray
  //Then we add the height above the trays the mechanism sits
  if (readValueFromEEPROM(10) > 0) { laser_pos_Y += cos(millis()*readValueFromEEPROM(6))*readValueFromEEPROM(7); }
  float result_Y = 90 - servo_Y.radToDeg(atan(laser_pos_Y / sqrt(pow(laser_pos_X,2) + pow(readValueFromEEPROM(0),2))));
  servo_Y.write(result_Y);
  Serial.println("Y:" + String(result_Y));
  return;
}
