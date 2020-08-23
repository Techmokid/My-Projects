#include <ESP8266WiFi.h>
#include <PinToGPIO.h>

#define PIR_Pin 2
#define Strobe_Pin 3
#define Relay_Pin 4
//#define Trig_1 5
//#define Trig_2 6
//#define Trig_3 7
//#define Trig_4 8
//#define Echo_1 9
//#define Echo_2 10
//#define Echo_3 11
//#define Echo_4 12

WiFiServer server(8080);
WiFiClient client;
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);

PinToGPIO p;

bool running = false;
unsigned long timer = 0;
int flashInterval = 10;

void setup() {
  Serial.begin(115200);
  
  pinMode(p.pinToGPIO(Strobe_Pin),OUTPUT);
  pinMode(p.pinToGPIO(Relay_Pin),OUTPUT);
  
  setupWifi();
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
  } else if (request.substring(0,5) == "START") {
    if (running) { client.println("Already Started!"); } else {
      if (!digitalRead(p.pinToGPIO(PIR_Pin))) {
        client.println("Starting...");
        startProcess();
      } else {
        Serial.println("Failed to start: PIR sensor has detected motion");
        client.println("Failed to start: PIR sensor has detected motion");
      }
    }
  } else if (request.substring(0,4) == "STOP") {
    if (!running) {
      Serial.println("Failed to stop: Not running");
      client.println("Failed to stop: Not running");
    } else {
      client.println("Stopped");
      stopProcess();
    }
  } else {
    Serial.println("Invalid command: " + request);
    client.println("Invalid command: " + request);
  }
  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
}
