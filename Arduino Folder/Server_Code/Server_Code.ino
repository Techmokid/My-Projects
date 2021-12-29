#include <SPI.h>
#include <Ethernet.h>

// MAC address from Ethernet shield sticker under board
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//IPAddress ip(192, 168, 10, 87); // IP address, may need to change depending on network
EthernetServer server(55);  // create a server at port 80

void setup() {
  Serial.begin(115200);
  if(Ethernet.begin(mac) == 0) { 
    Serial.println("Configuration failed");
    while (1);
  } else {
    Serial.print("Arduino Server IP: ");   //Displays your Arduino's local IP address
    Serial.println(Ethernet.localIP());
  }
  
  server.begin();
  Serial.println("Server Running!");
}

void loop() {
  EthernetClient client = server.available();  // try to get client
  if (client) {
    Serial.print("Connected to client: ");
    
    while(client.available()) {
      char c = client.read();
      Serial.print(c);
    }
    
    if(client.connected()) {
      Serial.println("Webpage Sent To Client");
      HTML_Printer(client);
    }  
    
    delay(8);
    client.stop();    //Closes the client connection
    Serial.println("Disconnected from client");
  }
  delay(1500);      // give the web browser time to receive the data
  client.stop(); // close the connection
}
