/*
WebLED, an example of how to control digital outputs using a network-connected
web browser. uses the Winet W5100 Ethernet Shield and the Ethernet library
Darren Yates for APC Magazine, May 2013 issue
15 March 2013
*/

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,0, 200);

EthernetServer server(80);

void setup()
{
  Serial.begin(9600);    
  pinMode(5, OUTPUT);    
  Ethernet.begin(mac, ip);
  server.begin();
}

void loop()
{
  
  EthernetClient client = server.available();
  if (client) {
    boolean currentLineIsBlank = true;
    String buffer = "";  
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.print(c);   
        buffer+=c;       
        if (c == '\n' && currentLineIsBlank) {
          
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<font face='arial'>");
          if (digitalRead(5)){  
            client.print(" LED is <font color='green'>ON</font>");
          }else{
            client.print(" LED is <font color='red'>OFF</font>");
          }
          client.println("<br />");
          client.print("<FORM action=\"http://192.168.0.200/\" >");
          client.print("<P> <INPUT type=\"radio\" name=\"LED\" value=\"on\">ON");
          client.print("<P> <INPUT type=\"radio\" name=\"LED\" value=\"off\">OFF");
          client.print("<P> <INPUT type=\"submit\" value=\"Submit\"> </FORM>");
            
          break;
        }
        if (c == '\n') {
          
          currentLineIsBlank = true;
          buffer="";       
        } else if (c == '\r') {            
          if(buffer.indexOf("GET /?LED=on")>=0)
            digitalWrite(5,HIGH);  
          
          if(buffer.indexOf("GET /?LED=off")>=0)
            digitalWrite(5,LOW);  
        }
        else {
          
          currentLineIsBlank = false;
        }
      }
    }
    
    delay(50);
    
    client.stop();
  }
}

