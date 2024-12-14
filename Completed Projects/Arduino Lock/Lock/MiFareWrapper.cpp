// MiFareWrapper.cpp
#include "MiFareWrapper.h"

MiFareWrapper::MiFareWrapper(int ssPin, int rstPin) : rfidReader(ssPin, rstPin) {}

bool MiFareWrapper::initialize() {
    rfidReader.init();
    return true; // Assume success as EasyMFRC522 doesn't provide a direct status
}

bool MiFareWrapper::writeToCard(const String& data) {
    if (data.length() > 16) {
      //data = data.substring(0, 16); // Truncate data to the first 16 characters
      //Serial.print(F("Warning: Data exceeds block size (16 bytes). Data will be truncated to: "));
      //Serial.println(data);
    }

    Serial.println(F("Waiting for a tag to write..."));
    while (!rfidReader.detectTag()) {
        delay(50);
    }

    Serial.println(F("Tag detected. Writing data..."));
    int result = rfidReader.writeRaw(block, (byte*)data.c_str(), data.length());

    if (result >= 0) {
        Serial.println(F("Data written successfully!"));
        rfidReader.unselectMifareTag();
        return true;
    } else {
        Serial.print(F("Error writing to card: "));
        Serial.println(result);
        rfidReader.unselectMifareTag();
        return false;
    }
}

String MiFareWrapper::readFromCard() {
    Serial.println(F("Waiting for a tag to read..."));
    while (!rfidReader.detectTag()) {
        delay(50);
    }

    Serial.println(F("Tag detected. Reading data..."));
    char buffer[16] = {0};
    int result = rfidReader.readRaw(block, (byte*)buffer, sizeof(buffer));

    if (result >= 0) {
        Serial.println(F("Data read successfully!"));
        rfidReader.unselectMifareTag();
        return String(buffer);
    } else {
        Serial.print(F("Error reading from card: "));
        Serial.println(result);
        rfidReader.unselectMifareTag();
        return "";
    }
}

bool MiFareWrapper::newCardDetected() {
    if (rfidReader.detectTag()) {
        rfidReader.unselectMifareTag();
        return true;
    }
    return false;
}