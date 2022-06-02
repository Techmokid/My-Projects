//#define DUMP_AT_COMMANDS

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("----------------------------------------------------");
  
  setupModem();
  
  //char server[] = "163.47.56.221";
  //int port = 8081;
  
  char server[] = "techmo.unity.chickenkiller.com";
  int port = 80;
  
  String response = getServerResponse(server, port);
  response = response.substring(response.indexOf("<body>"),response.indexOf("</body>"));
  response.replace("<br/>","\n");
  response.replace("<body>","");
  Serial.println("----------------------------------------------------");
  Serial.println(response);
}

void loop() {}
