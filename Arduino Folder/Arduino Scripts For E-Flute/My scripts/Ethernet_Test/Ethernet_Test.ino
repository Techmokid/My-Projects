#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  
byte ip[] = { 192, 168, 1, 110 };   
int answer = 0; 

void setup()
{
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
}

void loop () {
  delay(100);
  answer = Ethernet.maintain();
  // 0 = nothing happened / Maintain Not needed by server;
  // 1 = renew failed;
  // 2 = renew success;
  // 3 = rebind failed;
  // 4 = rebind success;
  Serial.println(answer);
}
