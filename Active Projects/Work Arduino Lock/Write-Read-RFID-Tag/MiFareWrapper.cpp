#include <SPI.h>
#include <MFRC522.h>

// Pin configuration for the RFID module
#define RST_PIN 9   // Reset pin
#define SS_PIN 10   // Slave Select pin

// MiFare Wrapper Class definition
class MiFareWrapper {
public:
  MiFareWrapper(uint8_t ssPin, uint8_t rstPin)
    : mfrc522(ssPin, rstPin), encryptionKey(0xAA) {}

  bool initialize() {
    SPI.begin();
    mfrc522.PCD_Init();  // Initialize the MFRC522 module
    return mfrc522.PCD_PerformSelfTest();  // Check if RFID reader initializes correctly
  }

  // Function to encrypt data using XOR
  String encryptData(const String &data) {
    String encryptedData = "";
    for (int i = 0; i < data.length(); i++) {
      encryptedData += char(data[i] ^ encryptionKey);  // XOR encryption
    }
    return encryptedData;
  }

  // Function to decrypt data using XOR (reverse of encryption)
  String decryptData(const String &encryptedData) {
    return encryptData(encryptedData);  // XOR is symmetric, so we can reuse the encryption function
  }

  // Function to write encrypted data to the card
  bool writeData(const String &data) {
    byte block = 4;  // Block to write to (adjust if needed)
    byte buffer[16];

    // Prepare the buffer with the encrypted data
    String encrypted = encryptData(data);
    int len = encrypted.length();
    for (int i = 0; i < 16; i++) {
      buffer[i] = (i < len) ? encrypted[i] : 0;  // Pad with 0 if data is less than 16 bytes
    }

    MFRC522::StatusCode status = mfrc522.MIFARE_Write(block, buffer, 16);
    return (status == MFRC522::STATUS_OK);
  }

  // Function to read data from the card
  String readData() {
    byte block = 4;  // Block to read from
    byte buffer[18];  // Buffer to store data

    MFRC522::StatusCode status = mfrc522.MIFARE_Read(block, buffer, &buffer[0]);
    if (status != MFRC522::STATUS_OK) {
      return "";  // Return an empty string if reading fails
    }

    // Convert buffer to a string
    String data = "";
    for (byte i = 0; i < 16; i++) {
      if (buffer[i] != 0) {
        data += char(buffer[i]);
      }
    }

    // Decrypt and return the data
    return decryptData(data);
  }

  // Function to write and confirm the data on the card
  bool writeAndConfirm(const String &data) {
    // Write the data to the RFID card
    if (!writeData(data)) {
      return false;  // If writing failed, return false
    }

    // Read the data back and check if it matches
    String readDataFromCard = readData();  // Renamed variable to avoid conflict
    return (readDataFromCard == data);  // Return true if the data read matches the data written
  }

private:
  MFRC522 mfrc522;
  const byte encryptionKey;
};
