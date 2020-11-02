#include <esp_now.h>
#include <WiFi.h>

#define LED_Pin 32

// REPLACE WITH THE MAC Address of your receiver 
uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0xB9, 0xB3, 0x2C};

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

  pinMode(LED_Pin,OUTPUT);
}
 
void loop() {
  // Set values to send
  //outgoingReadings.isOn = isOn;

  // Send message via ESP-NOW
  //esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &outgoingReadings, sizeof(outgoingReadings));
  
}
