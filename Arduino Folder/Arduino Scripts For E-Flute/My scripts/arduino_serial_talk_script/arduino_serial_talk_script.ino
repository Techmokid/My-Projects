int ser = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(ser);
  ser = ser + 1;
  if (ser > 255){
    Serial.print("EOC");
    endScript();
  }
}

void endScript() {
  digitalWrite(13,LOW);
  endScript();
}
