#include <LinkedList.h>
#include "stdio.h"
#include "stdlib.h"

int clientUpdateTime = 500;
unsigned long lastTimer_2 = 0;

LinkedList<String> connectedClients = LinkedList<String>();
LinkedList<String> prevClients = LinkedList<String>();
IPAddress address;

struct station_info *stat_info;
struct ipv4_addr *IPaddress;
const char *ssid = "ESP8266 Germicide";

void setupWifi() {
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

bool prevListContains(String val) {
  for (int i = 0; i < prevClients.size(); i++) { if (prevClients.get(i) == val) { return true; } }
  return false;
}

bool isDevConnected() {
  for (int i = 0; i < connectedClients.size(); i++) {
    if (connectedClients.get(i) == "8c:79:67:8c:a:7d") { return true; }
  }
  return false;
}
