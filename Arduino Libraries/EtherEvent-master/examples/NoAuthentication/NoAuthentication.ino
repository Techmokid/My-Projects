// Example sketch demonstrating unauthenticated use of the EtherEvent library
// Periodically sends a test event, receives events and prints them to the serial monitor.
// Required the modified TCPEvents plugin for use with EventGhost: https://github.com/per1234/TCPEvents
// Use with the EventGhost-example-trees.

//These libraries are required by EtherEvent:
#include <SPI.h>
#include <Ethernet.h>
#define ETHEREVENT_NO_AUTHENTICATION  //this line must come before #include "EtherEvent.h"
#include <EtherEvent.h>


//configuration parameters - modify these values to your desired settings
const boolean useDHCP = false;  //true==use DHCP to assign an IP address to the device, this will significantly increase memory usage. false==use static IP address.
byte MACaddress[] = {0, 1, 2, 3, 4, 4};  //this can be anything you like, but must be unique on your network
const IPAddress deviceIP = IPAddress(192, 168, 69, 104);  //IP address to use for the device. This can be any valid address on the network as long as it is unique. If you are using DHCP then this doesn't need to be configured.
const unsigned int port = 1024;  //TCP port to receive events

const unsigned int sendEventInterval = 4000;  //(ms)Delay between sending the test events.
const IPAddress targetIP = IPAddress(192, 168, 69, 100);  //The IP address to send the test events to.
const unsigned int targetPort = 1024;  //The port to send the test events to. This will also be used as the default port to send events to.


EthernetServer ethernetServer(port);  //TCP port to receive on
EthernetClient ethernetClient;  //create the client object for Ethernet communication
unsigned long sendTimestamp;  //used by the example to periodically send an event


void setup() {
  Serial.begin(9600);  //the received event and other information will be displayed in your serial monitor while the sketch is running
  if (useDHCP == true) {
    Ethernet.begin(MACaddress);  //let the network assign an IP address
  }
  else {
    Ethernet.begin(MACaddress, deviceIP);  //use static IP address
  }
  ethernetServer.begin();  //begin the server that will be used to receive events
  if (EtherEvent.begin() == false) { //initialize EtherEvent
    Serial.print(F("ERROR: Buffer size exceeds available memory, use smaller values."));
    while (true);  //abort execution of the rest of the program
  }
}


void loop() {
  if (byte availableLength = EtherEvent.availableEvent(ethernetServer)) {  //this checks for a new event and gets the length of the event including the null terminator
    Serial.print(F("\nReceived event length="));
    Serial.println(availableLength);
    char event[availableLength];  //create the event buffer of the correct size
    EtherEvent.readEvent(event);  //read the event into the event buffer
    Serial.print(F("Received event: "));
    Serial.println(event);  //now the event is in your buffer
    availableLength = EtherEvent.availablePayload();  //receiving the payload works the same as the event
    Serial.print(F("Received payload length="));
    Serial.println(availableLength);
    char payload[availableLength];
    EtherEvent.readPayload(payload);
    Serial.print(F("Received payload: "));
    Serial.println(payload);
  }

  if (millis() - sendTimestamp > sendEventInterval) {  //periodically send event
    sendTimestamp = millis();  //reset the timestamp for the next event send
    Serial.println(F("\nAttempting event send"));
    if (EtherEvent.send(ethernetClient, targetIP, targetPort, "test", "test payload")) {  //send event to target IP address, port, event, payload
      Serial.println(F("Event send successful"));
    }
    else {
      Serial.println(F("Event send failed"));
    }
  }

  if (useDHCP == true) {
    Ethernet.maintain();  //request renewal of DHCP lease if expired
  }
}

