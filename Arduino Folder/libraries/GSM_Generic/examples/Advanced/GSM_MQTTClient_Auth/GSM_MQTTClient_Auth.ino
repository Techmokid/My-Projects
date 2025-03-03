/****************************************************************************************************************************
  GSM_MQTTClient_Auth.ino - Dead simple MQTT Client for GSM/GPRS shields

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
  Basic MQTT example (without SSL!) with Authentication
  This sketch demonstrates the basic capabilities of the library.
  It connects to an MQTT server then:
  - providing username and password
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic", printing out any messages
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

// initialize the library instance
GSMClient gsmClient;
GPRS gprs;
GSM gsmAccess;

// connection state
bool connected = false;

// BaudRate to communicate to GSM/GPRS modem. If be limit to max 115200 inside modem
unsigned long baudRateSerialGSM  = 115200;

//////////////////////////////////////////////////////

#include <PubSubClient.h>

// Update these with values suitable for your network.
//const char* mqttServer = "broker.example";        // Broker address
const char* mqttServer = "broker.emqx.io";        // Broker address
//const char* mqttServer = "broker.shiftr.io";        // Broker address

const char *ID        = "MQTTClient_SSL-Client";  // Name of our device, must be unique
const char *TOPIC     = "MQTT_Pub";               // Topic to subcribe to
const char *subTopic  = "MQTT_Sub";               // Topic to subcribe to

//IPAddress mqttServer(172, 16, 0, 2);

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  for (unsigned int i = 0; i < length; i++) 
  {
    Serial.print((char)payload[i]);
  }
  
  Serial.println();
}

PubSubClient client(mqttServer, 1883, callback, gsmClient);

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection to ");
    Serial.print(mqttServer);

    // Attempt to connect
    if (client.connect("arduino", "try", "try"))
    {
      Serial.println("...connected");
      
      // Once connected, publish an announcement...
      String data = "Hello from GSM_MQTTClient_Auth on " + String(BOARD_NAME);

      client.publish(TOPIC, data.c_str());

      //Serial.println("Published connection message successfully!");
      //Serial.print("Subcribed to: ");
      //Serial.println(subTopic);
      
      // This is a workaround to address https://github.com/OPEnSLab-OSU/SSLClient/issues/9
      //ethClientSSL.flush();
      // ... and resubscribe
      client.subscribe(subTopic);
      // for loopback testing
      client.subscribe(TOPIC);
      // This is a workaround to address https://github.com/OPEnSLab-OSU/SSLClient/issues/9
      //ethClientSSL.flush();
    }
    else
    {
      Serial.print("...failed, rc=");
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

  Serial.print(F("\nStart GSM_MQTT_Medium on ")); Serial.println(BOARD_NAME);
  Serial.println(GSM_GENERIC_VERSION);

#if ( defined(DEBUG_GSM_GENERIC_PORT) && (_GSM_GENERIC_LOGLEVEL_ > 4) )
  MODEM.debug(DEBUG_GSM_GENERIC_PORT);
#endif  

  connectToGPRS();
}

#define MQTT_PUBLISH_INTERVAL_MS       5000L

String data         = "Hello from GSM_MQTTClient_Auth on " + String(BOARD_NAME);
const char *pubData = data.c_str();

unsigned long lastMsg = 0;

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
  
      if (!client.publish(TOPIC, pubData))
      {
        Serial.println("Message failed to send.");
      }
  
      Serial.print("Message Send : " + String(TOPIC) + " => ");
      Serial.println(data);
    }
    
    client.loop();
  }
}
