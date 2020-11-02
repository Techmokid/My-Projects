#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH THE MAC Address of your receiver 
uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0xB9, 0xCC, 0x10};

bool isOn;
bool incomingIsOn;
String success;

typedef struct struct_message {
    bool isOn;
} struct_message;

struct_message outgoingReadings;
struct_message incomingReadings;
 
void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  setupWifiHandler();
}
 
void loop() {
  // Set values to send
  outgoingReadings.isOn = analogRead(32) < 1;
  Serial.println(outgoingReadings.isOn);

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &outgoingReadings, sizeof(outgoingReadings));
}
