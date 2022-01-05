// find the TFT display
uint16_t identifier = tft.readRegister(0x0);
if (identifier == 0x9325) {
   Serial.println("Found ILI9325");
} else if (identifier == 0x9328) {
   Serial.println("Found ILI9328");
} else {
   Serial.print("Unknown driver chip ");
   Serial.println(identifier, HEX);
   while (1);
}
