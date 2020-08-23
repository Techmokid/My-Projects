//Here is your germicide machine code! Feel free to change any of the pins used by altering the "#define PIN_NAME_HERE PIN_NUMBER" statements
#include <ESP8266WiFi.h>
#include <PinToGPIO.h>
#include <EEPROM.h>
#include <servo.h>
#include <SPI.h>

#define PIR_Pin 2       //Movement sensor
#define Strobe_Pin 3    //The strobe pin turns on the warning lights
#define Relay_Pin 4     //The relay pin turns the germicide on.
#define trigPin 5       //Ultrasonic sensor trigger pin
#define echoPin 6       //Ultrasonic sensor echo pin
#define servoPin 7      //Servo for the ultrasonic sensor
#define printData true

//This tells the system to round to the nearest "timeMultiplier" minutes when calculating the amount of time to stay on for
#define timeMultiplier 15

//This tells the chip how fast to flash pin 13 while running
int flashInterval = 200;

//These are variables you don't need to touch
WiFiServer server(80);
WiFiClient client;
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);

extern "C" {
  #include<user_interface.h>
}

servo myservo;
PinToGPIO p;

bool running = false;

unsigned long timer = 0;
unsigned long flashTimer = 0;

float minutesToWait = 0;
float volumeToTimeModifier = 0.15;

void setup() {
  Serial.begin(115200);
  Serial.println("Test");
  pinMode(p.pinToGPIO(Strobe_Pin),OUTPUT);
  pinMode(p.pinToGPIO(Relay_Pin),OUTPUT);
  pinMode(p.pinToGPIO(trigPin), OUTPUT);
  pinMode(p.pinToGPIO(echoPin), INPUT);
  myservo.pin = p.pinToGPIO(1);
  setupWifi();
}

void loop() {
  flashLED();
  
  if (digitalRead(p.pinToGPIO(PIR_Pin)) && running) {
    SerialPrintlnFunction("Detected Movement!");
    stopProcess();
    digitalWrite(LED_BUILTIN,HIGH);
  }
  
  if (running) {
    if (millis() - timer >= minutesToWait * 1000 * 60) {
      SerialPrintlnFunction("Process Complete!");
      stopProcess();
      digitalWrite(LED_BUILTIN,LOW);
    }
  }
  
  //if ((!digitalRead(IRPin)) && (!digitalRead(PIR_Pin)) && (!running)) { startProcess(); }
  client = server.available();
  if (!client) { return; }
  
  client.setTimeout(2000);
  String request = client.readStringUntil('\n');
  request.toUpperCase();
  
  if (request.length() < 1) {
    Serial.println("Blank Message"); return;
  } else if (request.substring(0,4) == "TEST") {
    client.println("Test Loop");
  } else if (request.substring(0,5) == "START") {
    if (!running) {
      if (!digitalRead(p.pinToGPIO(PIR_Pin))) {
        client.println("Starting...");
        startProcess();
      } else { client.println("Could not start process as movement sensor is triggered"); }
    } else { client.println("Already Running!"); }
  } else if (request.substring(0,4) == "STOP") {
    if (running) {
      client.println("Stopping");
      stopProcess();
    } else { client.println("Already Halted!"); }
  } else { client.println("Unknown Command"); }
  
  delay(50);
}

void stopProcess() {
  running = false;
  digitalWrite(p.pinToGPIO(Relay_Pin),LOW);
  digitalWrite(p.pinToGPIO(Strobe_Pin),LOW);
  SerialPrintlnFunction("\n\n");
}

void startProcess() {
  SerialPrintlnFunction("Starting Process...");
  
  running = true;
  digitalWrite(p.pinToGPIO(Strobe_Pin),HIGH);
  getRoomSize();
  digitalWrite(p.pinToGPIO(Relay_Pin),HIGH);
  
  flashTimer = millis();
  timer = millis();
  
  SerialPrintlnFunction("Calculated ETA: " + String(minutesToWait) + " mins");
}

void getRoomSize() {
  Serial.begin(115200);
  
  myservo.write(10); delay(500); SerialPrintFunction("Retrieving X distance 1..."); float temp_X_1 = getDistance(); SerialPrintlnFunction("Done. Measured: " + String(temp_X_1) + " meters");
  myservo.write(100); delay(500); SerialPrintFunction("Retrieving Y distance 1..."); float temp_Y_1 = getDistance(); SerialPrintlnFunction("Done. Measured: " + String(temp_Y_1) + " meters");
  myservo.write(180); delay(500); SerialPrintFunction("Retrieving X distance 2..."); float temp_X_2 = getDistance(); SerialPrintlnFunction("Done. Measured: " + String(temp_X_2) + " meters");
  myservo.write(100); delay(500); SerialPrintFunction("Retrieving Y distance 2..."); float temp_Y_2 = getDistance(); SerialPrintlnFunction("Done. Measured: " + String(temp_Y_2) + " meters");
  myservo.write(10);
  
  minutesToWait = volumeToTimeSeconds((temp_X_1 + temp_X_2) * (temp_Y_1 + temp_Y_2));
}

float getDistance() {
  flashLED();
  
  // Clears the trigPin
  digitalWrite(p.pinToGPIO(trigPin), LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(p.pinToGPIO(trigPin), HIGH);
  delayMicroseconds(10);
  digitalWrite(p.pinToGPIO(trigPin), LOW);
  
  // Reads the echoPin, returns the calculated distance
  float result = pulseIn(echoPin, HIGH) * 0.034/2000;
  if (result != 0) { return result; }
  return getDistance();
}

float volumeToTimeSeconds(float roomVolume) { return ceil((roomVolume * volumeToTimeModifier) / timeMultiplier) * timeMultiplier; }

void SerialPrintFunction(String msg) { if (printData) { Serial.print(msg); } }
void SerialPrintlnFunction(String msg) { if (printData) { Serial.println(msg); } }
