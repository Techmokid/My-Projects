#include <LinkedList.h>
#include "stdio.h"
#include "stdlib.h"

int clientUpdateTime = 500;
unsigned long lastTimer = 0;

LinkedList<String> connectedClients = LinkedList<String>();
LinkedList<String> prevClients = LinkedList<String>();

struct station_info *stat_info;
struct ipv4_addr *IPaddress;

void updateClientList() {
  if (millis() - lastTimer < clientUpdateTime) { return; }
  lastTimer = millis();
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
      } else { Serial.println("WARNING: Detected unknown device: " + connectedClients.get(i)); }
    }
  }
}

bool prevListContains(String val) {
  for (int i = 0; i < prevClients.size(); i++) { if (prevClients.get(i) == val) { return true; } }
  return false;
}
