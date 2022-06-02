#include<LinkedList.h>

char server[] = "techmo.unity.chickenkiller.com";
char port[] = "80";

void setup() {
  startSerial();
  startModem();
  Serial.println("Done starting modem");
  getServerResponse("techmo.unity.chickenkiller.com","80",new String {"Newid:1"},1);
  Serial.println("Done getting data");
}

void loop() {
  serialLoop();
}
