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

#define DUMP_TINYGSM_INTERFACE_DATA
#define DUMP_AT_COMMANDS


#ifdef DUMP_AT_COMMANDS
#define DUMP_TINYGSM_INTERFACE_DATA
#endif

#ifdef DUMP_TINYGSM_INTERFACE_DATA
#define TINY_GSM_DEBUG Serial
#endif

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
  while (!modem.restart()) {
    //if (!modem.init(180000L)) {
    DBG("Failed to restart modem, delaying 10s and retrying");
    // restart autobaud in case GSM just rebooted
    //TinyGsmAutoBaud(SerialAT, GSM_AUTOBAUD_MIN, GSM_AUTOBAUD_MAX);
    //return;
  }

  modemName = modem.getModemName();
  modemInfo = modem.getModemInfo();

#if TINY_GSM_USE_GPRS
  // Unlock your SIM card with a PIN if needed
  if ((GSM_PIN != "") && modem.getSimStatus() != 3) {
    modem.simUnlock(GSM_PIN);
  }
#endif
}

void startServerComms() {
#if TINY_GSM_USE_WIFI
  // Wifi connection parameters must be set before waiting for the network
  if (!modem.networkConnect(wifiSSID, wifiPass)) {
    Serial.println(F("[TinyGSM Interface]: Could not set SSID/Password"));
  }
#endif

#if TINY_GSM_USE_GPRS && defined TINY_GSM_MODEM_XBEE
  // The XBee must run the gprsConnect function BEFORE waiting for network!
  modem.gprsConnect(apn, gprsUser, gprsPass);
#endif

  if (!modem.waitForNetwork()) {
    Serial.println(F("[TinyGSM Interface]: Could not connect to network"));
    return;
  }

  if (modem.isNetworkConnected()) {
    Serial.println(F("[TinyGSM Interface]: Network connected"));
  }

#if TINY_GSM_USE_GPRS
  // GPRS connection parameters are usually set after network registration
  if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
    Serial.println("[TinyGSM Interface]: Failed to connect to " + String(apn));
    return;
  }

  if (modem.isGprsConnected()) {
    Serial.println(F("[TinyGSM Interface]: GPRS connected"));
  }
#endif
}

bool isServerConnected = false;
void getServerResponse(String server, int port, char resource[]) {
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
  server.toCharArray(tempServer, server.length() + 1);
  getServerResponse(tempServer, port, "/", headers, numHeaders);
  return;
}
void getServerResponse(String server, int port, String headers[], int numHeaders) {
  getServerResponse(server, port, "/", headers, numHeaders);
  return;
}
void getServerResponse(char server[], int port, String headers[], int numHeaders) {
  getServerResponse(server, port, "/", headers, numHeaders);
  return;
}
void getServerResponse(char server[], int port, char resource[], String headers[], int numHeaders) {
#ifdef DUMP_TINYGSM_INTERFACE_DATA
  //Serial.println("Connecting to: " + String(server) + ":" + String(port));
#endif

  if (!isServerConnected) {
    startServerComms();
    isServerConnected = true;
  }

  if (!client.connect(server, port)) {
    isServerConnected = false;
    Serial.println("[TinyGSM Interface]: Failed to connect to " + String(server));
    delay(10000);
    return;
  }

  // Make a HTTP GET request:
  client.print(String("GET ") + resource + " HTTP/1.1\r\n"); delay(50);
  client.print(String("Host: ") + server + "\r\n"); delay(50);
  for (int i = 0; i < numHeaders; i++) {
#ifdef DUMP_TINYGSM_INTERFACE_DATA
    Serial.println("[TinyGSM Interface]: HEADERS: " + headers[i]);
#endif
    client.print(headers[i] + "\r\n"); delay(50);
  }
  //client.print("Getinfoonid:1\r\n");
  client.print(String("Accept: */*") + "\r\n"); delay(50);
  client.print("Connection: close\r\n\r\n"); delay(50);
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
    Serial.println("[TinyGSM Interface]: Timed out attempting to access: " + String(server) + ":" + String(port));
  } else {
    //Serial.println(serverResponse);
  }

  //Serial.println("Response from server: " + result);
  client.flush();
  client.stop();
  //return result;

  int temp_start = serverResponse.indexOf("Location: http://");
  if (temp_start != -1) {
    String redirectData = serverResponse.substring(temp_start, serverResponse.length());
    if (redirectData.indexOf("\n") != -1) {
      redirectData = redirectData.substring(0, redirectData.indexOf("\n"));
    }

    redirectData = redirectData.substring(
                     redirectData.indexOf("Location: http://") + String("Location: http://").length(),
                     redirectData.length() - 1
                   );

    String temp_server = redirectData.substring(0, redirectData.indexOf(":"));
    String temp_port = redirectData.substring(redirectData.indexOf(":") + 1, redirectData.length());

#ifdef DUMP_TINYGSM_INTERFACE_DATA
    Serial.println("[TinyGSM Interface]: Detected redirect to: " + temp_server + " on port " + temp_port);
#endif

    serverResponse = "";

    redirectData = "";
    //startServerComms();
    getServerResponse(temp_server, temp_port.toInt(), resource, headers, numHeaders);
    return;
  }

  isServerConnected = false;
  //Serial.println("Resp: " + serverResponse);

  int startString = serverResponse.indexOf("<body>") + 7;
  //Serial.println("Start: " + String(startString));

  int endString = serverResponse.indexOf("</body>");
  //Serial.println("End: " + String(endString));

  serverResponse = serverResponse.substring(startString, endString);
  serverResponse.replace("<br/>", "\n");
  //Serial.println("Final response: " + serverResponse);

  if (serverResponse == "") {
    getServerResponse(server, port, resource, headers, numHeaders);
    return;
  }

  delay(1000);
  client.flush();
  client.stop();
  return;
}

String postServerResponse(String server, int port, char resource[]) {
  char tempServer[16];
  server.toCharArray(tempServer, server.length() + 1);
  return postServerResponse(tempServer, port, "/");
}
String postServerResponse(String server, int port) {
  return postServerResponse(server, port, "/");
}
String postServerResponse(char server[], int port) {
  return postServerResponse(server, port, "/");
}
String postServerResponse(char server[], int port, char resource[]) {
#ifdef DUMP_TINYGSM_INTERFACE_DATA
  Serial.println("[TinyGSM Interface]: Connecting to: " + String(server) + ":" + String(port));
#endif
  if (!isServerConnected) {
    startServerComms();
    isServerConnected = true;
  }

  if (!client.connect(server, port)) {
    Serial.println("[TinyGSM Interface]: Failed to connect to " + String(server));
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

void serverSetStatus(String status) {
  serverSetVariable("Status", status);
}
void serverSetVariable(String key, String value) {
  String temp[] = {"Setvalue:" + value, "Key:" + key, "Id:" + (String)ID};
  getServerResponse(
    "techmo.unity.chickenkiller.com",
    80,
    temp,
    3
  );
  //Serial.println(serverResponse);
}

#define TINY_GSM_TEST_TEMPERATURE 1

float getTemp() {
#if TINY_GSM_TEST_TEMPERATURE && defined TINY_GSM_MODEM_HAS_TEMPERATURE
  return modem.getTemperature();
#else
  return -273.15;
#endif
}

String getTime() {
  int   year3    = 0;
  int   month3   = 0;
  int   day3     = 0;
  int   hour3    = 0;
  int   min3     = 0;
  int   sec3     = 0;
  float timezone = 0;
  for (int8_t i = 5; i; i--) {
#ifdef DUMP_TINYGSM_INTERFACE_DATA
    DBG("Requesting current network time");
#endif
    if (modem.getNetworkTime(&year3, &month3, &day3, &hour3, &min3, &sec3,
                             &timezone)) {
#ifdef DUMP_TINYGSM_INTERFACE_DATA
      DBG("Year:", year3, "\tMonth:", month3, "\tDay:", day3);
      DBG("Hour:", hour3, "\tMinute:", min3, "\tSecond:", sec3);
      DBG("Timezone:", timezone);
#endif
      break;
    } else {
#ifdef DUMP_TINYGSM_INTERFACE_DATA
      DBG("Couldn't get network time, retrying in 15s.");
#endif
      delay(15000L);
    }
  }

  return modem.getGSMDateTime(DATE_FULL) + ",TZ+" + timezone;
}

String getGPSData() {
  modem.enableGPS();
  delay(15000L);
  float lat2      = 0;
  float lon2      = 0;
  float speed2    = 0;
  float alt2      = 0;
  int   vsat2     = 0;
  int   usat2     = 0;
  float accuracy2 = 0;
  int   year2     = 0;
  int   month2    = 0;
  int   day2      = 0;
  int   hour2     = 0;
  int   min2      = 0;
  int   sec2      = 0;
  for (int8_t i = 15; i; i--) {
#ifdef DUMP_TINYGSM_INTERFACE_DATA
    DBG("Requesting current GPS/GNSS/GLONASS location");
#endif
    if (modem.getGPS(&lat2, &lon2, &speed2, &alt2, &vsat2, &usat2, &accuracy2,
                     &year2, &month2, &day2, &hour2, &min2, &sec2)) {
#ifdef DUMP_TINYGSM_INTERFACE_DATA
      DBG("Latitude:", String(lat2, 8), "\tLongitude:", String(lon2, 8));
      DBG("Speed:", speed2, "\tAltitude:", alt2);
      DBG("Visible Satellites:", vsat2, "\tUsed Satellites:", usat2);
      DBG("Accuracy:", accuracy2);
      DBG("Year:", year2, "\tMonth:", month2, "\tDay:", day2);
      DBG("Hour:", hour2, "\tMinute:", min2, "\tSecond:", sec2);
#endif
      break;
    } else {
#ifdef DUMP_TINYGSM_INTERFACE_DATA
      DBG("Couldn't get GPS/GNSS/GLONASS location, retrying in 15s.");
#endif
      delay(15000L);
    }
  }

  modem.disableGPS();

  String result = String(lat2, 8) + ",";
  result       += String(lon2, 8) + ",";
  result       += String(speed2, 8) + ",";
  result       += String(alt2, 8) + ",";
  result       += String(vsat2, 8) + ",";
  result       += String(usat2, 8) + ",";
  result       += String(accuracy2, 8) + ",";
  return result;
}
