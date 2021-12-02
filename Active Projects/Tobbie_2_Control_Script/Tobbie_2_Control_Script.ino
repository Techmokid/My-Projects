void setup() { }

void loop() {
  setMicLED(true);  //delay(1000);
  setMicLED(false); //delay(1000);
  for(int y = 0; y < 5; y++) {
    for(int x = 0; x < 5; x++) {
      setLED(x,y,HIGH); //delay(100);
      setLED(x,y,LOW);  //delay(100);
    }
  }
}
