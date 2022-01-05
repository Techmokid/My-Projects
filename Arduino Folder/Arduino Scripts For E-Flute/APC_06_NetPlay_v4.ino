/*
 -----------------------------------------------------------
 NetPlayer web-powered stereo audio player
 Darren Yates for APC Magazine, April 2013 issue
 http://apcmag.com/arduino.htm
 15 Mar 2013
 
 Modified code created from Lutz Lisseck's SSDAWebServer, 
  with help from Ladyada SD webserver example.
 -----------------------------------------------------------
*/

#include <SPI.h>
#include <Ethernet.h>
#include <SimpleSDAudio.h>


// Setup the MAC address for your Ethernet port
// (Realistically, doesn't really matter).
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEC };

// Change the IP address to one that matches your home network.
// NOTE: It must be on the same subnet as your network eg. 192.168.0.xxx
IPAddress ip(192,168,0,200); 

// Set up server
EthernetServer server(80);

void setup() {
  // launch serial debugger line at 9600baud
  Serial.begin(9600);
  // initialise the SimpleSDAudio library to play STEREO files, set the SPI rate to half (8MHz)
  SdPlay.init(SSDA_MODE_STEREO | SSDA_MODE_HALFRATE);
  // turn on the Ethernet
  Ethernet.begin(mac,ip);
  // launch the server
  server.begin();
}

EthernetClient *pclient;

void dir_callback(char *buf) { 
  if(pclient) {
    pclient->print("<li><a href=\"");
    pclient->print(buf);
    pclient->println("\">"); 
    pclient->print(buf);
    pclient->println("</a></li>");
  }
}

#define BUFSIZ 100
boolean playflag = false;
String temp;
String temp2;
int pauseset;
char* track;

void loop() {

  char clientline[BUFSIZ];
  int index = 0;
  if(playflag) { SdPlay.play(); playflag = false;}
  SdPlay.worker();

  EthernetClient client = server.available();
  if (client) {
    boolean currentLineIsBlank = true;
    String buffer = "";  
    pclient = &client;
    index = 0;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        if (c != '\n' && c != '\r') {
          clientline[index] = c;
          index++;
          // are we too big for the buffer? start tossing out data
          if (index >= BUFSIZ) 
            index = BUFSIZ -1;
          
          // continue to read more data!
          continue;
        }
        clientline[index] = 0;
        Serial.println(clientline);

        buffer+=c;       
        char *filename;
        if (c == '\n' && currentLineIsBlank) {   
          
        // create the web page to be sent back to the requesting client's web browser          
          client.println(F("HTTP/1.1 200 OK"));
          client.println(F("Content-Type: text/html"));
          client.println();
          client.println("<font face='arial'>");
 
          client.println(F("<a href=\"http://www.hackerspace-ffm.de/wiki/index.php?title=SimpleSDAudio\">SimpleSDAudio</a> V" SSDA_VERSIONSTRING " Webinterface"));
          client.println(F("<br />Modified by Darren Yates for <a href=\"http://www.apcmag.com/arduino.htm\">APC Magazine</a>, May 2013 issue."));
          client.println(F("<br /><h2>Pick file to play:</h2><ul>"));
          SdPlay.dir(&dir_callback);
          client.println(F("<br /><li><a href=\"Stop\">Stop playback"));
          client.println("</a></li>");
          client.println(F("</ul>"));
          client.print(F("<h3>Track now playing - "));
          client.print(filename);
          client.print(F(".</h3>"));
          break;
          
        }
        if (c == '\n') {
          
          currentLineIsBlank = true;
          buffer="";       
        
        } else if (c == '\r') {            
          
          // check to see what's being requested by the client
          // first up, check to see if we just want the home page
            if(strstr(clientline, "GET /") != 0) {
                Serial.println(clientline);
 
              filename = clientline + 5;  
              (strstr(clientline, " HTTP/1.1"))[0] = 0;
                Serial.print("current: ");
              Serial.println(filename);
           
           // check to see if the 'stop playback' link was pressed
              if (filename == "STOP") {
                SdPlay.stop();
              }
              
            }
                    
        } else {
          currentLineIsBlank = false;
        }
      }
    }
   delay(1);
   client.stop();
   pclient = NULL;
  }
}

