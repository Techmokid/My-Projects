#include <ESP8266WiFi.h>
#include <SPI.h>
#include "SdFat.h"
#include "sdios.h"

const char *ssid = "ESP8266 v10";
IPAddress mask = (255, 255, 255, 0); WiFiServer server(80); IPAddress IP(192,168,4,15);
using namespace sdfat;
extern "C" {
  #include<user_interface.h>
}

IPAddress address;

void setup() {
  Serial.begin(74880);
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);
  WiFi.softAPConfig(IP, IP, mask);
  server.begin();
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
 
  Serial.println();
  Serial.println(F("ESP8266 Test Interface Server Has Booted"));
  Serial.print(F("IP: ")); Serial.println(WiFi.softAPIP());
  Serial.print(F("MAC:")); Serial.println(WiFi.softAPmacAddress());
}

void loop() {
  updateClientList();
  
  WiFiClient client = server.available();
  client.setTimeout(10000);
  if (!client) { }
}
