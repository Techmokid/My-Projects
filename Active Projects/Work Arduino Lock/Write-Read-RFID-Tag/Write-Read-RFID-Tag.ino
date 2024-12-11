#include "MiFareWrapper.cpp"  // Include the MiFare wrapper

MiFareWrapper rfid(SS_PIN, RST_PIN);  // Create an instance of MiFareWrapper

void setup() {
  Serial.begin(115200);
  
  if (!rfid.initialize()) {
    Serial.println("ERROR! Could not initialize RFID reader!");
    while (true);  // Halt the program if initialization fails
  }

  String dataToWrite = "HelloWorld123";
  
  if (rfid.writeAndConfirm(dataToWrite)) {
    Serial.println("Data successfully written and verified!");
  } else {
    Serial.println("Failed to write or verify data!");
  }
}

void loop() { }
