#include <SPI.h>
#include <RH_RF95.h>
#include <EEPROM.h>

// Assuming you have a GPS module
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// Define pins for LoRa and GPS
#define RF95_CS 10
#define RF95_RST 9
#define RF95_INT 2
#define GPS_RX_PIN 4
#define GPS_TX_PIN 3

// LoRa radio settings
RH_RF95 rf95(RF95_CS, RF95_INT);

// GPS setup
SoftwareSerial ss(GPS_RX_PIN, GPS_TX_PIN);
TinyGPSPlus gps;

// Message structure with GPS, temperature, humidity, and UV
struct Message {
  uint32_t deviceID;      // The device ID that sent the message
  uint16_t messageNumber; // Incremental message count for this device
  float latitude;         // Latitude (GPS)
  float longitude;        // Longitude (GPS)
  float temperature;      // Temperature (in Celsius)
  float humidity;         // Humidity (percentage)
  float uvIndex;          // UV Index
  char payload[240];      // Message data (could be anything)
};

#define MAX_SEEN_MESSAGES 50
uint32_t seenMessages[MAX_SEEN_MESSAGES];
uint8_t seenIndex = 0;

uint32_t deviceID;
uint16_t messageNumber = 0;

void setup() {
  Serial.begin(9600);
  ss.begin(9600); // Start GPS serial

  // Initialize EEPROM (assumed device ID is stored at address 0)
  deviceID = EEPROM.read(0); 
  if (deviceID == 0xFFFFFFFF) {
    deviceID = random(1, 1000000);  // Generate random ID if EEPROM value is uninitialized
    EEPROM.write(0, deviceID);      // Save the generated ID to EEPROM
  }

  // Print device ID
  Serial.print("Device ID: ");
  Serial.println(deviceID);

  // Initialize the RF95 LoRa module
  pinMode(RF95_RST, OUTPUT);
  digitalWrite(RF95_RST, LOW);
  delay(100);
  digitalWrite(RF95_RST, HIGH);
  delay(100);
  
  if (!rf95.init()) {
    Serial.println("LoRa init failed!");
    while (1);
  }

  rf95.setFrequency(915.0);  // Set LoRa frequency (adjust as necessary)
  rf95.setTxPower(13);       // Set transmit power

  Serial.println("LoRa initialized.");
}

void loop() {
  // Read GPS data
  while (ss.available() > 0) {
    gps.encode(ss.read());
  }

  // Handle incoming messages
  if (rf95.available()) {
    uint8_t buf[255];
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len)) {
      Message msg;
      memcpy(&msg, buf, sizeof(Message));
      
      // Check if we've already seen this message
      if (hasSeenMessage(msg.deviceID, msg.messageNumber)) {
        return; // Ignore if already seen
      }

      // If the message is for this device, process it
      if (msg.deviceID == deviceID) {
        // Process message here (e.g., perform action based on payload)
        Serial.print("Message for me: ");
        Serial.println(msg.payload);
      } else {
        // Forward the message to other devices
        rf95.send(buf, len);
        rf95.waitPacketSent();
        recordSeenMessage(msg.deviceID, msg.messageNumber);
      }
    }
  }

  // Simulate sending a message periodically
  if (millis() % 10000 == 0) {
    sendMessage();
  }
}

// Function to send a message
void sendMessage() {
  Message msg;
  msg.deviceID = deviceID;
  msg.messageNumber = messageNumber++;
  
  // Get current GPS data
  if (gps.location.isUpdated()) {
    msg.latitude = gps.location.lat();
    msg.longitude = gps.location.lng();
  }

  // For demo purposes, using placeholder values for temperature, humidity, and UV
  msg.temperature = 25.0;  // Replace with actual sensor data
  msg.humidity = 60.0;     // Replace with actual sensor data
  msg.uvIndex = 5.0;       // Replace with actual sensor data
  
  snprintf(msg.payload, sizeof(msg.payload), "Message #%d from device %ld", msg.messageNumber, deviceID);

  // Send message
  uint8_t buf[sizeof(msg)];
  memcpy(buf, &msg, sizeof(msg));
  rf95.send(buf, sizeof(buf));
  rf95.waitPacketSent();
  
  Serial.print("Sent: ");
  Serial.print("Lat: ");
  Serial.print(msg.latitude, 6);
  Serial.print(" Long: ");
  Serial.print(msg.longitude, 6);
  Serial.print(" Temp: ");
  Serial.print(msg.temperature);
  Serial.print(" Humidity: ");
  Serial.print(msg.humidity);
  Serial.print(" UV: ");
  Serial.println(msg.uvIndex);
}

// Function to check if a message has already been seen
bool hasSeenMessage(uint32_t deviceID, uint16_t messageNumber) {
  uint32_t messageID = (deviceID << 16) | messageNumber;
  
  for (int i = 0; i < MAX_SEEN_MESSAGES; i++) {
    if (seenMessages[i] == messageID) {
      return true; // Message already seen
    }
  }
  return false; // Message not seen
}

// Function to record a new message as seen
void recordSeenMessage(uint32_t deviceID, uint16_t messageNumber) {
  uint32_t messageID = (deviceID << 16) | messageNumber;
  seenMessages[seenIndex] = messageID;
  seenIndex = (seenIndex + 1) % MAX_SEEN_MESSAGES; // Circular buffer
}
