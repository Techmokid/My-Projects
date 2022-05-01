#include <SPI.h>
#include <LoRa.h>

void setup() {
  Serial.begin(9600);
  Serial.println("LoRa Sender");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  LoRa.beginPacket();
  LoRa.print("Testing Message 123");
  LoRa.endPacket();
  delay(10);
}
