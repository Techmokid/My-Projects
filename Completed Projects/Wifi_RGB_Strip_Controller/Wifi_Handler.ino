#include <LinkedList.h>

const char* ssid     = "Never_Gonna_Give_You_Up";
const char* password = "beezChurger";

//const char* host = "djxmmx.net";
//const uint16_t port = 17;

WiFiClient client;

void setupWifi() {
  Serial.begin(115200);
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

String getValue(String data, char separator, int index) {
    int found = 0; int strIndex[] = { 0, -1 }; int maxIndex = data.length() - 1;
    for (int i = 0; i <= maxIndex && found <= index; i++) { if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
    } } return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void handleWifiClient() {
  if (client.available() < 1) { return; }
  
  Serial.println("\nWaiting for response...");
  String request = client.readStringUntil('\n');
  request.toUpperCase();
  
  if (request.length() < 1) {
    Serial.println("Blank");
  } else if (request.substring(0,11) == "READ:SINGLE") {
    Serial.println("Sent single colour readout to client");
    client.println(getSingleColourDataReadout());
  } else if (request.substring(0,9) == "READ:FADE") {
    Serial.println("Sent fade colour readout to client");
    client.println(getFadeColourDataReadout());
  } else if (request.substring(0,11) == "SET:SINGLE:") {
    request = getValue(request,':',2);
    int r = getValue(request,'|',0).toInt();
    int g = getValue(request,'|',1).toInt();
    int b = getValue(request,'|',2).toInt();
    Serial.println("Set single colour to R:" + String(r) + " G:" + String(g) + " B:" + String(b));
    setSingleColour(r,g,b);
    status = 1;
  } else if (request.substring(0,9) == "SET:FADE:") {
    request = getValue(request,':',2);
    int r1 = getValue(request,'|',0).toInt();
    int g1 = getValue(request,'|',1).toInt();
    int b1 = getValue(request,'|',2).toInt();
    int r2 = getValue(request,'|',3).toInt();
    int g2 = getValue(request,'|',4).toInt();
    int b2 = getValue(request,'|',5).toInt();
    int fadeSpeed = getValue(request,'|',6).toInt();
    
    Serial.println(
      "Set fade colour to between <RGB:" +
      String(r1) + "," + String(g1) + "," + String(b1) + "> and <RGB:" +
      String(r2) + "," + String(g2) + "," + String(b2) + ">"
    );
    
    setFade(r1,g1,b1,r2,g2,b2,fadeSpeed);
    status = 2;
  } else if (request.substring(0,14) == "SET:INTENSITY:") {
    int brightness = getValue(request,':',2).toInt();
    
    if (brightness > 255) { brightness = 255; }
    if (brightness < 0)   { brightness = 0; }
    strip.setBrightness(brightness);
    
    Serial.println("Set brightness intensity to: " + String(brightness) + "/255");
  } else if (request.substring(0,9) == "SET:CLEAR") {
    strip.clear();
    strip.show();

    status = 0;
    Serial.println("Turned off strip");
  } else if (request.substring(0,14) == "SET:FADESPEED:") {
    int fade_speed = getValue(request,':',2).toInt();
    updateFadeSpeed(fade_speed);
    
    Serial.println("Set fade speed to: " + String(fade_speed) + "ms");
  }
  
  delay(50);
}
