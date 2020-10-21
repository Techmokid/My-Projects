#include <ESP8266WiFi.h>
#include <PinToGPIO.h>

#define PIR_Pin 2
#define Strobe_Pin 3
#define Relay_Pin 4

WiFiServer server(8080);
WiFiClient client;
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);

PinToGPIO p;

bool running = false;
unsigned long timer = 0;
int flashInterval = 15*60;

void setup() {
  Serial.begin(115200);
  
  pinMode(p.pinToGPIO(Strobe_Pin),OUTPUT);
  pinMode(p.pinToGPIO(Relay_Pin),OUTPUT);
  
  setupWifi("GERMICIDE INTERFACE v1.0","beezChurger");
}

void loop() {
  handleMainFunctions();
  updateClientList();
  
  client = server.available();
  client.setTimeout(1000);
  
  if (!client) { return; }
  String request = client.readStringUntil('\n');
  request.toUpperCase();
  Serial.println();
  
  if (request.length() < 1) {
    Serial.println("Blank");
  } else if (request.substring(0,3) == "SET") {
    flashInterval = request.substring(4,request.length()).toInt();
    printData("Set time to " + String(flashInterval) + " seconds (" + String(flashInterval/60) + " minutes)");
  } else if (request.substring(0,5) == "START") {
    if (running) { client.println("Already Started!"); } else {
      if (!digitalRead(p.pinToGPIO(PIR_Pin))) {
        client.println("Starting..."); startProcess();
      } else { printData("Failed to start: PIR sensor has detected motion"); }
    }
  } else if (request.substring(0,4) == "STOP") {
    if (!running) { printData("Failed to stop: Not running"); } else {
      client.println("Stopped"); stopProcess();
    }
  } else { printData("Invalid command: " + request); }
  digitalWrite(LED_BUILTIN, HIGH); delay(50);
}

void printData(String x) { Serial.println(x); client.println(x); }
