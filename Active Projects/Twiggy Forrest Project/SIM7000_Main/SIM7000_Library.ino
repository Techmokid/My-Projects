// Select your modem:
// #define TINY_GSM_MODEM_SIM800
// #define TINY_GSM_MODEM_SIM808
// #define TINY_GSM_MODEM_SIM868
// #define TINY_GSM_MODEM_SIM900
 #define TINY_GSM_MODEM_SIM7000
// #define TINY_GSM_MODEM_SIM7000SSL
// #define TINY_GSM_MODEM_SIM7080
// #define TINY_GSM_MODEM_SIM5360
// #define TINY_GSM_MODEM_SIM7600
// #define TINY_GSM_MODEM_UBLOX
// #define TINY_GSM_MODEM_SARAR4
// #define TINY_GSM_MODEM_M95
// #define TINY_GSM_MODEM_BG96
// #define TINY_GSM_MODEM_A6
// #define TINY_GSM_MODEM_A7
// #define TINY_GSM_MODEM_M590
// #define TINY_GSM_MODEM_MC60
// #define TINY_GSM_MODEM_MC60E
// #define TINY_GSM_MODEM_ESP8266
// #define TINY_GSM_MODEM_XBEE
// #define TINY_GSM_MODEM_SEQUANS_MONARCH

#include <SoftwareSerial.h>
SoftwareSerial SerialAT(TX, RX);  // RX, TX

// This is the amount of bytes to use for holding the message returned by your website
#if !defined(TINY_GSM_RX_BUFFER)
#define TINY_GSM_RX_BUFFER 1024
#endif

#define TINY_GSM_USE_GPRS true
#define TINY_GSM_USE_WIFI false
#define GSM_PIN ""

// Your GPRS credentials, if any
const char apn[]      = "telstra.wap";
const char gprsUser[] = "";
const char gprsPass[] = "";

// Your WiFi connection credentials, if applicable
const char wifiSSID[] = "Never_Gonna_Give_You_Up";
const char wifiPass[] = "beezChurger";

// Server details


// #define DUMP_AT_COMMANDS
// #define TINY_GSM_DEBUG Serial

// Range to attempt to autobaud
// NOTE:  DO NOT AUTOBAUD in production code.  Once you've established
// communication, set a fixed baud rate using modem.setBaud(#).
#define GSM_AUTOBAUD_MIN 9600
#define GSM_AUTOBAUD_MAX 115200

// Uncomment this if you want to use SSL
// #define USE_SSL

// --------------------------------------------------------------------------------------------------------------------------------------

#include <TinyGsmClient.h>

// Just in case someone defined the wrong thing..
#if TINY_GSM_USE_GPRS && not defined TINY_GSM_MODEM_HAS_GPRS
#undef TINY_GSM_USE_GPRS
#undef TINY_GSM_USE_WIFI
#define TINY_GSM_USE_GPRS false
#define TINY_GSM_USE_WIFI true
#endif
#if TINY_GSM_USE_WIFI && not defined TINY_GSM_MODEM_HAS_WIFI
#undef TINY_GSM_USE_GPRS
#undef TINY_GSM_USE_WIFI
#define TINY_GSM_USE_GPRS true
#define TINY_GSM_USE_WIFI false
#endif

#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, Serial);
TinyGsm        modem(debugger);
#else
TinyGsm        modem(SerialAT);
#endif

TinyGsmClient  client(modem);

String modemName = "";
String modemInfo = "";

void setupModem() {
  // Set GSM module baud rate
  //TinyGsmAutoBaud(SerialAT, GSM_AUTOBAUD_MIN, GSM_AUTOBAUD_MAX);
  SerialAT.begin(9600);
  pinMode(PWRKEY, OUTPUT);
  digitalWrite(PWRKEY, HIGH);
  delay(260);
  digitalWrite(PWRKEY, LOW);
  delay(10000);

  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  //Serial.println("Initializing modem...");
  if (!modem.restart()) {
  //if (!modem.init(180000L)) {
    DBG("Failed to restart modem, delaying 10s and retrying");
    // restart autobaud in case GSM just rebooted
    //TinyGsmAutoBaud(SerialAT, GSM_AUTOBAUD_MIN, GSM_AUTOBAUD_MAX);
    return;
  }
  
  modemName = modem.getModemName();
  modemInfo = modem.getModemInfo();

#if TINY_GSM_USE_GPRS
  // Unlock your SIM card with a PIN if needed
  if ((GSM_PIN != "") && modem.getSimStatus() != 3) { modem.simUnlock(GSM_PIN); }
#endif
}

void startServerComms() {
  #if TINY_GSM_USE_WIFI
  // Wifi connection parameters must be set before waiting for the network
  if (!modem.networkConnect(wifiSSID, wifiPass)) {
    Serial.println(F("Could not set SSID/Password"));
    return;
  }
#endif

#if TINY_GSM_USE_GPRS && defined TINY_GSM_MODEM_XBEE
  // The XBee must run the gprsConnect function BEFORE waiting for network!
  modem.gprsConnect(apn, gprsUser, gprsPass);
#endif

  if (!modem.waitForNetwork()) {
    Serial.println(F("Could not connect to network"));
    return;
  }

  if (modem.isNetworkConnected()) { Serial.println(F("Network connected")); }

#if TINY_GSM_USE_GPRS
  // GPRS connection parameters are usually set after network registration
  if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
    Serial.println("Failed to connect to " + String(apn));
    return;
  }

  if (modem.isGprsConnected()) { Serial.println(F("GPRS connected")); }
#endif
}

bool isServerConnected = false;
void getServerResponse(String server, int port, char resource[]) {
  Serial.println("DEBUG:0"); 
  getServerResponse(
    server,
    port,
    resource,
    new String[0],
    0
  ); return;
}

void getServerResponse(String server, int port, char resource[], String headers[], int numHeaders) {
  char tempServer[1024];
  server.toCharArray(tempServer,server.length()+1);
  getServerResponse(tempServer,port,"/",headers, numHeaders);
  return;
}
void getServerResponse(String server, int port, String headers[], int numHeaders) { getServerResponse(server, port, "/", headers, numHeaders); return; }
void getServerResponse(char server[], int port, String headers[], int numHeaders) { getServerResponse(server, port, "/", headers, numHeaders); return; }

void getServerResponse(char server[], int port, char resource[], String headers[], int numHeaders) {
  Serial.println("Connecting to: " + String(server) + ":" + String(port));
  if (!isServerConnected) {startServerComms(); isServerConnected=true;}
  
  if (!client.connect(server, port)) {
    isServerConnected = false;
    Serial.println("Failed to connect to " + String(server));
    delay(10000);
    return;
  }

  // Make a HTTP GET request:
  client.print(String("GET ") + resource + " HTTP/1.1\r\n");
  client.print(String("Host: ") + server + "\r\n");
  for (int i = 0; i < numHeaders; i++) {
    client.print(headers[i] + "\r\n");
  }
  //client.print("Getinfoonid:1\r\n");
  client.print(String("Accept: */*") + "\r\n");
  client.print("Connection: close\r\n\r\n");
  client.println();

  serverResponse = "";
  uint32_t timeout = millis();
  while (client.connected() && millis() - timeout < 10000) {
    // Print available data
    while (client.available()) {
      char c = client.read();
      if (c > 5) {
        serverResponse += c;
        //Serial.println("HY: " + String(c));
      }
      
      timeout = millis();
    }
  }
  if (millis() - timeout > 9999) {
    Serial.println("Timed out");
  } else {
    //Serial.println(serverResponse);
  }
  
  //Serial.println("Response from server: " + result);
  delay(500);
  client.flush();
  client.stop();
  //return result;
  
  int temp_start = serverResponse.indexOf("Location: http://");
  if (temp_start != -1) {
    String redirectData = serverResponse.substring(temp_start,serverResponse.length());
    if (redirectData.indexOf("\n") != -1) {
      redirectData = redirectData.substring(0,redirectData.indexOf("\n"));
    }

    redirectData = redirectData.substring(
      redirectData.indexOf("Location: http://") + String("Location: http://").length(),
      redirectData.length()-1
    );
    
    String temp_server = redirectData.substring(0,redirectData.indexOf(":"));
    String temp_port = redirectData.substring(redirectData.indexOf(":")+1,redirectData.length());

    Serial.println("Detected redirect to: " + temp_server + " on port " + temp_port);
    serverResponse = "";
    
    redirectData = "";
    //startServerComms();
    getServerResponse(temp_server, temp_port.toInt(), resource, headers, numHeaders);
    return;
  }
  
  isServerConnected = false;
  Serial.println("Resp: " + serverResponse);
  
  int startString = serverResponse.indexOf("<body>") + 7;
  Serial.println("Start: " + String(startString));
  
  int endString = serverResponse.indexOf("</body>");
  Serial.println("End: " + String(endString));
  
  serverResponse = serverResponse.substring(startString,endString);
  serverResponse.replace("<br/>","\n");
  Serial.println("Final response: " + serverResponse);

  if (serverResponse == "") {
    getServerResponse(server,port,resource,headers,numHeaders);
    return;
  }
  delay(1000);
  client.flush();
  client.stop();

  delay(1000);
  return;
}

String postServerResponse(String server, int port, char resource[]) {
  char tempServer[16];
  server.toCharArray(tempServer,server.length()+1);
  return postServerResponse(tempServer,port,"/");
}
String postServerResponse(String server, int port) { return postServerResponse(server,port,"/");}
String postServerResponse(char server[], int port) { return postServerResponse(server, port, "/"); }
String postServerResponse(char server[], int port, char resource[]) {
  Serial.println("Connecting to: " + String(server) + ":" + String(port));
  if (!isServerConnected) {startServerComms(); isServerConnected=true;}
  
  if (!client.connect(server, port)) {
    Serial.println("Failed to connect to " + String(server));
    delay(10000);
    return;
  }

  // Make a HTTP GET request:
  client.print(String("POST ") + resource + " HTTP/1.1\r\n");
  client.print(String("Host: ") + server + "\r\n");
  client.print(String("Accept: */*") + "\r\n");
  client.print(F("Connection: close\r\n\r\n"));
  client.println();

  String result = "";
  uint32_t timeout = millis();
  while (client.connected() && millis() - timeout < 10000L) {
    // Print available data
    while (client.available()) {
      char c = client.read();
      result += c;
      timeout = millis();
    }
  }

  client.flush();
  client.stop();
  
  isServerConnected = false;
  return result;
}

void serverSetStatus(String status) { serverSetVariable("Status",status); }
void serverSetVariable(String key,String value) {
  String temp[] = {"Setvalue:\"" + value + "\"","Key:\"" + key + "\"","Id:" + (String)ID};
  getServerResponse(
    "techmo.unity.chickenkiller.com",
    80,
    temp,
    3
  );
  //Serial.println(serverResponse);
}
