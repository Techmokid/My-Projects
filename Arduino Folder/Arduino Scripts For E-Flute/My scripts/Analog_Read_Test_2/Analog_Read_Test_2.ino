int mic = 0;
int LOOP = 0;
int maximum = 0;
int totMax = 0;
int serin = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  serin = Serial.read();
  if (serin == 49) {
    ABC();
  }
  if (serin == 50) {
    test();
  }
}

void ABC() {
  serin = digitalRead(0);
  if (serin == LOW) {
    maximum = 0;
    totMax = 0;
    Serial.println();
    Serial.println();
    Serial.println("Command Received");
    Serial.println();
    tone(2,9);
    delay(50);
    noTone(2);
    delay(20);
  }
  serin = Serial.read();
  if (LOOP == 20) {
    Serial.print("      Max was ");
    Serial.print(maximum);
    Serial.print("      total Maximum is ");
    Serial.print(totMax);
    maximum = 0;
    LOOP = 0;
  }
  Serial.println();
  mic = analogRead(0);
  if (mic > maximum) {
    maximum = mic;
  }
  if (maximum > totMax) {
    totMax = maximum;
  }
  Serial.print("Analog Input on pin A0 is ");
  Serial.print(mic);
  LOOP = LOOP + 1;
  ABC();
}

void test() {
  
}
