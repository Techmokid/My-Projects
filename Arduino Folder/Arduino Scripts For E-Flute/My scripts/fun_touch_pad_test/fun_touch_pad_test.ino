int Mic = 0;

void setup() {
  pinMode(A0,INPUT); 
  Serial.begin(9600);
}

void loop() {
  Mic = digitalRead(A0);
  if (Mic == 0) {
    Serial.print("Don't even think about touching me.");
  } else {
    Serial.print("AARRRGGGGHHHHH!!!!! Don't Touch Me!");
  }
  
  Mic = analogRead(A0);
  Serial.print("                      ");
  Serial.print(Mic);
  
  Mic = digitalRead(A0);
  Serial.print("                      ");
  Serial.println(Mic);
  delay(100);
}
