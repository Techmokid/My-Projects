#include <SPI.h>
#include <Ethernet.h>

// MAC and IP configuration
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);

// Ethernet server on port 80
EthernetServer server(80);

// Pin definitions
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

bool blinking = false;
unsigned long blinkInterval = 1000;  // Default blink interval in ms
unsigned long lastBlinkTime = 0;
bool ledState = false;

// RGB values
int redValue = 0;
int greenValue = 0;
int blueValue = 0;

void setup() {
  // Set pin modes
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Start Ethernet and server
  Ethernet.begin(mac, ip);
  server.begin();

  Serial.begin(9600);
  Serial.print("Server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // Check for client connection
  EthernetClient client = server.available();
  if (client) {
    Serial.println("New client connected.");
    boolean currentLineIsBlank = true;
    String request = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;

        // End of the HTTP request
        if (c == '\n' && currentLineIsBlank) {
          // Parse HTTP request
          if (request.indexOf("GET /") >= 0) {
            handleRequest(request);
          }

          // Send the webpage
          sendWebpage(client);
          break;
        }

        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }

    // Close the connection
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");
  }

  // Handle LED blinking
  if (blinking) {
    unsigned long currentTime = millis();
    if (currentTime - lastBlinkTime >= blinkInterval) {
      lastBlinkTime = currentTime;
      ledState = !ledState;
      analogWrite(redPin, ledState ? redValue : 0);
      analogWrite(greenPin, ledState ? greenValue : 0);
      analogWrite(bluePin, ledState ? blueValue : 0);
    }
  }
}

void handleRequest(String request) {
  // Extract R, G, B values
  if (request.indexOf("r=") > 0) {
    redValue = getValueFromRequest(request, "r");
    analogWrite(redPin, redValue);
  }
  if (request.indexOf("g=") > 0) {
    greenValue = getValueFromRequest(request, "g");
    analogWrite(greenPin, greenValue);
  }
  if (request.indexOf("b=") > 0) {
    blueValue = getValueFromRequest(request, "b");
    analogWrite(bluePin, blueValue);
  }

  // Extract blink interval
  if (request.indexOf("interval=") > 0) {
    blinkInterval = getValueFromRequest(request, "interval");
  }

  // Extract blinking state
  if (request.indexOf("action=pause") > 0) {
    blinking = false;
  }
  if (request.indexOf("action=play") > 0) {
    blinking = true;
  }
}

int getValueFromRequest(String request, String key) {
  int start = request.indexOf(key + "=");
  if (start == -1) return 0;
  start += key.length() + 1;
  int end = request.indexOf('&', start);
  if (end == -1) end = request.indexOf(' ', start);
  return request.substring(start, end).toInt();
}

void sendWebpage(EthernetClient &client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();

  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><title>RGB LED Controller</title></head>");
  client.println("<body>");
  client.println("<h1>Arduino Mega RGB LED Controller</h1>");
  client.println("<p>Control the RGB LED and blinking behavior.</p>");

  client.println("<form>");
  client.println("<label>Red (0-255):</label>");
  client.println("<input type='range' name='r' min='0' max='255' oninput='this.form.submit()'><br>");
  client.println("<label>Green (0-255):</label>");
  client.println("<input type='range' name='g' min='0' max='255' oninput='this.form.submit()'><br>");
  client.println("<label>Blue (0-255):</label>");
  client.println("<input type='range' name='b' min='0' max='255' oninput='this.form.submit()'><br>");
  client.println("</form>");

  client.println("<form>");
  client.println("<label>Blink Interval (ms):</label>");
  client.println("<input type='text' name='interval' value='" + String(blinkInterval) + "'>");
  client.println("<input type='submit' value='Set Interval'><br>");
  client.println("</form>");

  client.println("<form>");
  client.println("<button type='submit' name='action' value='play'>Play</button>");
  client.println("<button type='submit' name='action' value='pause'>Pause</button>");
  client.println("</form>");

  client.println("</body>");
  client.println("</html>");
}
