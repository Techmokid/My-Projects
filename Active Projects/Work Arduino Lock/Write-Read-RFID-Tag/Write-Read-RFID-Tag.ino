#include "MiFareWrapper.h"

#define SS_PIN 10
#define RST_PIN 9

MiFareWrapper rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println("-------------------------------");
  Serial.println();

  // Initialize RFID
  if (!rfid.initialize()) {
    Serial.println(F("RFID failed to initialize :("));
    while (true);
  }

  Serial.println(F("RFID initialized successfully"));
}

void loop() {
  if (!rfid.newCardDetected()) { delay(100); return; }

  // Write to card
  String data = "RealSecretCodeLOL";
  if (!rfid.writeToCard(data)) {
    Serial.println(F("Failed to write data"));
    delay(500);
    return;
  }
  Serial.println(F("Data written successfully!"));

  // Read the string
  String dataRead = rfid.readFromCard();
  if (dataRead == "") {
    Serial.println(F("Failed to read data from the card"));
    return;
  }

  Serial.print(F("Data read from block: "));
  Serial.println(dataRead);
  Serial.println();
  Serial.println("-------------------------------");
  Serial.println();
  delay(2000);
}
