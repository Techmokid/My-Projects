/****************************************************************************************************************************
  GSM_MQTTS_ThingStream.ino - Dead simple MQTT Client for GSM/GPRS shields

  For ESP8266, ESP32, SAMD21/SAMD51, nRF52, SAM DUE, Teensy and STM32 with GSM modules

  GSM_Generic is a library for the ESP8266, ESP32, SAMD21/SAMD51, nRF52, SAM DUE, Teensy and STM32 with GSM modules

  Based on and modified from MKRGSM Library (https://github.com/arduino-libraries/MKRGSM)

  Built by Khoi Hoang https://github.com/khoih-prog/GSM_Generic
  Licensed under GNU Lesser General Public License

  Copyright (C) 2017  Arduino AG (http://www.arduino.cc/)
  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation, either version 2.1 of the License, or (at your option) any later version.
  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
  You should have received a copy of the GNU General Public License along with this program.
  If not, see <https://www.gnu.org/licenses/>.

  Version: 1.4.0
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.2.4    K Hoang     11/03/2021 Initial public release to add support to many boards / modules besides MKRGSM 1400 / SARA U201
  1.3.0    K Hoang     31/03/2021 Add ThingStream MQTTS support. Fix SMS receive bug.
  1.3.1    K Hoang     25/04/2021 Fix bug making ESP32 reset repeatedly.
  1.4.0    K Hoang     28/06/2021 Add support to RP2040-based boards using Arduino mbed or Arduino-pico core
 *****************************************************************************************************************************/
/*
  Basic MQTT example (with SSL!)
  This sketch demonstrates the basic capabilities of the library.
  It connects to an MQTT server then:
  - publishes {Hello from MQTTClient_SSL on NUCLEO_F767ZI} to the topic [STM32_Pub]
  - subscribes to the topic [STM32_Sub], printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  It will reconnect to the server if the connection is lost using a blocking
  reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
  achieve the same result without blocking the main loop.
*/

#include "defines.h"

//////////////////////////////////////////////////////

// Please enter your sensitive data in the Secret tab or arduino_secrets.h
// PIN Number
const char PINNUMBER[]     = SECRET_PINNUMBER;
// APN data
const char GPRS_APN[]      = SECRET_GPRS_APN;
const char GPRS_LOGIN[]    = SECRET_GPRS_LOGIN;
const char GPRS_PASSWORD[] = SECRET_GPRS_PASSWORD;

//////////////////////////////////////////////////////

#include <PubSubClient.h>

const char my_cert[]  = "FIXME";
const char my_key[]   = "FIXME";

#define USING_THINGSTREAM_IO      true

#if USING_THINGSTREAM_IO

const char *MQTT_PREFIX_TOPIC   = "esp32-sniffer/";
const char *MQTT_ANNOUNCE_TOPIC = "/status";
const char *MQTT_CONTROL_TOPIC  = "/control";
const char *MQTT_BLE_TOPIC      = "/ble";


// GOT FROM ThingsStream!
const char *MQTT_SERVER     = "mqtt.thingstream.io";
const char *MQTT_USER       = "MQTT_USER";
const char *MQTT_PASS       = "MQTT_PASS";
const char *MQTT_CLIENT_ID  = "MQTT_CLIENT_ID";

String topic    = MQTT_PREFIX_TOPIC + String("12345678") + MQTT_BLE_TOPIC;
String subTopic = MQTT_PREFIX_TOPIC + String("12345678") + MQTT_BLE_TOPIC;

#else

const char* MQTT_SERVER = "broker.emqx.io";        // Broker address

const char*  ID         = "MQTTClient_SSL-Client";  // Name of our device, must be unique
String      topic       = "STM32_Pub";              // Topic to subcribe to
String      subTopic    = "STM32_Sub";              // Topic to subcribe to

#endif

void mqtt_receive_callback(char* topic, byte* payload, unsigned int length);

const int   MQTT_PORT           = 8883; //if you use SSL //1883 no SSL

unsigned long lastMsg = 0;

// Initialize the SSL client library
// Arguments: EthernetClient, our trust anchors

//////////////////////////////////////////////////////

// initialize the library instance
GSMSSLClient gsmClient;
GPRS gprs;
GSM gsmAccess;

// connection state
bool connected = false;

// BaudRate to communicate to GSM/GPRS modem. If be limit to max 115200 inside modem
unsigned long baudRateSerialGSM  = 115200;

//////////////////////////////////////////////////////

PubSubClient client(MQTT_SERVER, MQTT_PORT, mqtt_receive_callback, gsmClient);

/*
   Called whenever a payload is received from a subscribed MQTT topic
*/
void mqtt_receive_callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("MQTT Message receive [");
  Serial.print(topic);
  Serial.print("] ");
  
  for (unsigned int i = 0; i < length; i++) 
  {
    Serial.print((char)payload[i]);
  }
  
  Serial.println();
}

void reconnect() 
{
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection to ");
    Serial.println(MQTT_SERVER);

    // Attempt to connect

#if USING_THINGSTREAM_IO
    int connect_status = client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS, topic.c_str(), 2, false, "");
#else
    int connect_status = client.connect(ID);
#endif

    if (connect_status)                                
    {
      Serial.println("...connected");
      
      // Once connected, publish an announcement...
      String data = "Hello from MQTTClient_SSL on " + String(BOARD_NAME);

      client.publish(topic.c_str(), data.c_str());

      Serial.println("Published connection message successfully!");
     
      Serial.print("Subcribed to: ");
      Serial.println(subTopic);
      
      // ... and resubscribe
      client.subscribe(subTopic.c_str());
      // for loopback testing
      client.subscribe(topic.c_str());
    } 
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void connectToGPRS()
{
  #define NUMBER_OF_CONNECTION_TRIES      10

  uint8_t tryNumber = 1;
  
  // After starting the modem with GSM.begin()
  // attach the shield to the GPRS network with the APN, login and password
  while ((gsmAccess.begin(baudRateSerialGSM, PINNUMBER) != GSM_READY) ||
         (gprs.attachGPRS(GPRS_APN, GPRS_LOGIN, GPRS_PASSWORD) != GPRS_READY)) 
  {
    // failed, retry
    Serial.print("Connect GPRS failed, try = "); Serial.println(tryNumber);

    if (++tryNumber > NUMBER_OF_CONNECTION_TRIES)
    {
      Serial.println("\nCan't connected to GPRS.");

      connected = false;
      return;
    }
    
    delay(1000);
  }

  connected = true;

  gsmClient.connect(MQTT_SERVER, MQTT_PORT, false);

  //Get IP.
  IPAddress LocalIP = gprs.getIPAddress();
  Serial.print("\nConnected to GPRS. IP address = ");
  Serial.println(LocalIP);
}

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial);

  delay(200);

  Serial.print(F("\nStart GSM_MQTTS_ThingStream on ")); Serial.println(BOARD_NAME);
  Serial.println(GSM_GENERIC_VERSION);

#if ( defined(DEBUG_GSM_GENERIC_PORT) && (_GSM_GENERIC_LOGLEVEL_ > 4) )
  MODEM.debug(DEBUG_GSM_GENERIC_PORT);
#endif  

  connectToGPRS();
}

#define MQTT_PUBLISH_INTERVAL_MS      5000L

String data         = "Hello from GSM_MQTT_ThingStream on " + String(BOARD_NAME);
const char *pubData = data.c_str();

void loop() 
{
  static unsigned long now;

  if (gsmAccess.status() != GSM_READY || gprs.status() != GPRS_READY) 
  {
    connectToGPRS();
  }

  if (connected)
  {
    if (!client.connected()) 
    {
      reconnect();
    }
  
    // Sending Data
    now = millis();
    
    if (now - lastMsg > MQTT_PUBLISH_INTERVAL_MS)
    {
      lastMsg = now;
  
      if (!client.publish(topic.c_str(), pubData))
      {
        Serial.println("Message failed to send.");
      }
  
      Serial.print("MQTT Message Send : " + topic + " => ");
      Serial.println(data);
    }
    
    client.loop();
  }
}
