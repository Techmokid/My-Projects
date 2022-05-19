#include <ESP8266WiFi.h>

WiFiServer server(80);
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);

byte ledPin = 2;

void setup() {
 Serial.begin(115200);
 WiFi.mode(WIFI_AP);
 WiFi.softAP(ssid);
 WiFi.softAPConfig(IP, IP, mask);
 server.begin();
 
 pinMode(ledPin, OUTPUT);
 
 Serial.println();
 Serial.println("ESP8266 Test Interface Server Has Booted");
 Serial.print("IP: "); Serial.println(WiFi.softAPIP());
 Serial.print("MAC:"); Serial.println(WiFi.softAPmacAddress());
}

void loop() {
 WiFiClient client = server.available();
 client.setSync(true);
 
 if (!client) { return; Serial.println("Lost connection to client"); }
 digitalWrite(ledPin, LOW);
 
 String request = client.readStringUntil('\n');
 client.println("ESP8266 Loopback: " + request);
 Serial.println("From the station: " + request);
 digitalWrite(ledPin, HIGH);
 delay(10);
}
