//For EEPROM listings, see "Laser_Controller" script

#include <ESP8266WiFi.h>
#include <PinToGPIO.h>
#include <EEPROM.h>
#include <servo.h>
#include <SPI.h>
#include <SD.h>
#include "SdFat.h"
#include "sdios.h"

#define laserPin              2
#define servo_X_Pin           4
#define servo_Y_Pin           3

WiFiServer server(80);
WiFiClient client;
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);

const uint8_t chipSelect = SS;

bool running = false;
bool mountMode = false;
int Item_Position_X = 0;
int Item_Position_Y = 0;

using namespace sdfat;

extern "C" {
  #include<user_interface.h>
}

SdFat sd; SdFile root; SdFile f;
servo servo_X,servo_Y;
PinToGPIO p;

float width_of_tray;
float laser_pos_X;
float height_of_tray;
float laser_pos_Y;

void setup() {
  servo_X.startValOffset = readValueFromEEPROM(11);
  servo_X.endValOffset   = readValueFromEEPROM(12);
  servo_Y.startValOffset = readValueFromEEPROM(13);
  servo_Y.endValOffset   = readValueFromEEPROM(14);
  
  pinMode(p.pinToGPIO(laserPin),OUTPUT);
  
  servo_X.pin = p.pinToGPIO(servo_X_Pin); servo_X.write(90);
  servo_Y.pin = p.pinToGPIO(servo_Y_Pin); servo_Y.offset90 = true; servo_Y.write(0);
  
  unsigned long prevMill = millis();
  while (millis() - prevMill < 1000) { servo_X.updateServo(); servo_Y.updateServo(); }
  
  sdInit();
  setupWifi();
  
  Serial.println("\n---------------------- EEPROM Readout ----------------------");
  for (int i = 0; i < 6; i++) {
    Serial.println("Value \"" + String(readValueFromEEPROM(i)) + "\" at position \"" + String(i) + "\"");
  }
  Serial.println("------------------ End Of EEPROM Readout ------------------\n");
}

void loop() {
  updateClientList();
  updateLaser();
  
  client = server.available();
  client.setTimeout(60000);
  if (!client) { return; }
  
  Serial.println("\nWaiting for part code...");
  String request = client.readStringUntil('\n');
  request.toUpperCase();
  
  if (request.length() < 1) { Serial.println("Blank"); return; }
  if (bool(readValueFromEEPROM(5)) && (!isDevConnected())) {
    client.println("Dev lock active!");
  } else if (request.substring(0,5) == "HELP:") {
    Serial.println("Listing help to client");
    client.println("Help: ");
    client.println(" - Config:EEPROM Addr:Value:Units");
    client.println(" - ADCODE:Part Code:X:Y");
    client.println(" - RMCODE:Part Code");
    client.println(" - EDITCD:Part Code:New X:New Y");
    client.println(" - READAT:");
    client.println(" - MNTMOD:");
    client.println(" - TSTMTR:");
    client.println(" - CONFRDOUT:");
    client.println("\"Config Help\" for config values");
  } else if (request.substring(0,12) == "CONFIG HELP:") {
    Serial.println("Listing config help to client");
    client.println("Config Values: ");
    client.println(" - Address 0: Distance to wall");
    client.println(" - Address 1: Height offset from trays");
    client.println(" - Address 2: Width of tray area");
    client.println(" - Address 3: Height of tray area");
    client.println(" - Address 4: Distance of device from left of trays");
    client.println(" - Address 5: Activate Dev Lock (0 or 1)");
    client.println(" - Address 6: Speed of circle");
    client.println(" - Address 7: Radius of circle");
    client.println(" - Address 8: Number of trays in width");
    client.println(" - Address 9: Number of trays in height");
    client.println(" - Address 10: Circle activation (0 or 1)");
    client.println(" - Address 11: Servo X start calibration");
    client.println(" - Address 12: Servo X end calibration");
    client.println(" - Address 13: Servo Y start calibration");
    client.println(" - Address 14: Servo Y end calibration");
  } else if (request.substring(0,10) == "CONFRDOUT:") {
    Serial.println("Writing out EEPROM data to client");
    client.println("\n---------------------- EEPROM Readout ----------------------");
    for (int i = 0; i < 6; i++) {
      client.println("Value \"" + String(readValueFromEEPROM(i)) + "\" at position \"" + String(i) + "\"");
    }
    client.println("------------------ End Of EEPROM Readout ------------------\n");
  } else if (request.substring(0,7) == "CONFIG:") {
    EEPROM_Writer(request);
  } else if (request.substring(0,7) == "ADCODE:") {
    AddPartCode(request);
  } else if (request.substring(0,7) == "RMCODE:") {
    RemovePartCode(request);
  } else if (request.substring(0,7) == "EDITCD:") {
    EditPartCode(request);
  } else if (request.substring(0,7) == "READAT:") {
    EEPROM_Reader();
  } else if (request.substring(0,7) == "TSTMTR:") {
    client.println("Servo Test Mode Active");
    delay(50);
    updateClientList();
    
    int test_servo_timer = 3000;
    servo_X.write(90); servo_Y.write(0);  unsigned long temp = millis(); while(millis() - temp < test_servo_timer) { }
    servo_X.write(90); servo_Y.write(45); temp = millis(); while(millis() - temp < test_servo_timer) { }
    servo_X.write(90); servo_Y.write(90); temp = millis(); while(millis() - temp < test_servo_timer) { }
    servo_X.write(90); servo_Y.write(45); temp = millis(); while(millis() - temp < test_servo_timer) { }
    servo_X.write(90); servo_Y.write(0);  temp = millis(); while(millis() - temp < test_servo_timer) { }
    servo_X.write(45); servo_Y.write(0);  temp = millis(); while(millis() - temp < test_servo_timer) { }
    servo_X.write(0); servo_Y.write(0);   temp = millis(); while(millis() - temp < test_servo_timer) { }
    servo_X.write(45); servo_Y.write(0);  temp = millis(); while(millis() - temp < test_servo_timer) { }
    servo_X.write(90); servo_Y.write(0);  temp = millis(); while(millis() - temp < test_servo_timer) { }
    servo_X.write(135); servo_Y.write(0); temp = millis(); while(millis() - temp < test_servo_timer) { }
    servo_X.write(180); servo_Y.write(0); temp = millis(); while(millis() - temp < test_servo_timer) { }
    servo_X.write(135); servo_Y.write(0); temp = millis(); while(millis() - temp < test_servo_timer) { }
    servo_X.write(90); servo_Y.write(0);  temp = millis(); while(millis() - temp < test_servo_timer) { }
  } else if (request.substring(0,7) == "MNTMOD:") {
    mountMode = !mountMode;
    running = mountMode;
    servo_X.write(90);
    servo_Y.write(0);
    if (mountMode) {
      client.println("Set mount mode");
      Serial.println("Set mount mode");
    } else {
      client.println("Cleared mount mode");
      Serial.println("Cleared mount mode");
    }
  } else if (validPartCode(request)) {
    //It's a valid part code. Now, check to see where it is in SD memory
    client.println("Scanning for part: " + request);
    Serial.println("Scanning for part: " + request);
    
    getItem(request);
    if (Item_Position_X != -1) {
      startLaser();
      
      client.println("Part found at position (" + String(Item_Position_X) + "," + String(Item_Position_Y) + ")");
      Serial.println("Part found at position (" + String(Item_Position_X) + "," + String(Item_Position_Y) + ")");
      client.println("DEBUG - width_of_tray:" + String(width_of_tray));
      client.println("DEBUG - height_of_tray:" + String(height_of_tray));
      client.println("DEBUG - laser_pos_X:" + String(laser_pos_X));
      client.println("DEBUG - laser_pos_Y:" + String(laser_pos_Y));
      client.println("DEBUG - Z pos:" + String(readValueFromEEPROM(0)));

      //float width_of_tray;
      //float laser_pos_X;
      //float height_of_tray;
      //float laser_pos_Y;
    } else {
      client.println("Part code not found");
    }
  } else {
    client.println(request + " is not a valid part code!!!");
    Serial.println(request + " is not a valid part code!!!");
  }
  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
}
