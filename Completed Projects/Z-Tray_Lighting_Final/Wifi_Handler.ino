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
const char *ssid = "ESP8266 v1.5";

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

void updateClientList() {
  if (millis() - lastTimer_2 < clientUpdateTime) { return; }
  lastTimer_2 = millis();
  connectedClients.clear();
  
  int connections = wifi_softap_get_station_num();
  
  stat_info = wifi_softap_get_station_info();
  while (stat_info != NULL) {
    IPaddress = &stat_info->ip;
    address = IPaddress->addr;
    
    String result = String(stat_info->bssid[0],HEX) + ":";
    result += String(stat_info->bssid[1],HEX) + ":";
    result += String(stat_info->bssid[2],HEX) + ":";
    result += String(stat_info->bssid[3],HEX) + ":";
    result += String(stat_info->bssid[4],HEX) + ":";
    result += String(stat_info->bssid[5],HEX);
    connectedClients.add(result);
    
    sys:yield();
    stat_info = STAILQ_NEXT(stat_info, next);
  }
  
  detectDiscretions();
  prevClients.clear();
  for (int i = 0; i < connectedClients.size(); i++) { prevClients.add(connectedClients.get(i)); }
}

void detectDiscretions() {
  for (int i = 0; i < connectedClients.size(); i++) { 
    if(!prevListContains(connectedClients.get(i))) {
      if (connectedClients.get(i) == "8c:79:67:8c:a:7d") {
        Serial.println("Detected dev device");
      } else { Serial.println("WARNING: Unknown device: " + connectedClients.get(i)); }
    }
  }
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
