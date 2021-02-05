#include <SPI.h>
#include <LoRa.h>
#include <AltSoftSerial.h>

AltSoftSerial altser;
const int mybaud = 9600;

void setup() {
  delay(200);
  Serial.begin(9600);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("Initializing GPS module");
  Serial1.begin(mybaud);    // TX1
  altser.begin(mybaud);     // RX1
}

void loop() {
  String msg = "";
  byte b = altser.read();
  while (b != '\n') {
    if ((b > 1) && (b < 127)) {
      msg += char(b);
    }
    
    b = altser.read();
  }

  Serial.println(msg);
  
  LoRa.beginPacket();
  LoRa.print(msg);
  LoRa.endPacket();
}
