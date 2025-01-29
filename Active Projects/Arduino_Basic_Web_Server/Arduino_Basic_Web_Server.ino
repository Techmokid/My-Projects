#include <SPI.h>
#include <Ethernet.h>

// MAC address and IP address
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177); // Replace with an appropriate IP address for your network

// Ethernet server on port 80
EthernetServer server(80);

void setup() {
  // Initialize Ethernet and start server
  Ethernet.begin(mac, ip);
  server.begin();

  Serial.begin(9600);
  Serial.print("Server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // Check if a client has connected
  EthernetClient client = server.available();
  if (client) {
    Serial.println("New client connected.");
    boolean currentLineIsBlank = true;
    String request = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;

        // Detect the end of an HTTP request
        if (c == '\n' && currentLineIsBlank) {
          // Send a response
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // Connection closed after response
          client.println();
          
          // Webpage content
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head><title>Arduino Web Server</title></head>");
          client.println("<body>");
          client.println("<h1>Welcome to the Arduino Mega Web Server!</h1>");
          client.println("<p>This is a simple webpage served by your Arduino Mega with Ethernet shield.</p>");
          client.println("</body>");
          client.println("</html>");
          break;
        }

        // Check if current line is blank
        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }

    // Give the browser time to receive data
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");
  }
}
