void HTML_Printer(EthernetClient client) {
  // send a standard http response header
  client.println(F("HTTP/1.1 200 OK                                         "));
  client.println(F("Content-Type: text/html                                 "));
  client.println(F("Connection: close                                       "));
  client.println();
  
  //Now just print out the data
  client.println(F("<!DOCTYPE html>                                         "));
  
  client.println(F("<html>                                                  "));
  client.println(F("  <head>                                                "));
  client.println(F("    <title>Arduino Web Page</title>                     "));
  client.println(F("  </head>                                               "));
  client.println(F("  <body>                                                "));
  client.println(F("    <h1>Hello from Arduino!</h1>                        "));
  client.println(F("    <p>A web page from the Arduino server</p>           "));
  client.println(F("    <p>This is a test</p>                               "));
  client.println(F("  </body>                                               "));
  client.println(F("</html>                                                 "));
}
