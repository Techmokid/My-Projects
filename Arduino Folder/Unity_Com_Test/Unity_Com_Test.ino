void setup() {
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(11,INPUT);
  
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  
  Serial.begin(9600);
}

void loop() {
  //Write to Unity
  String digital = String(digitalRead(2)) + "_" + String(digitalRead(3)) + "_" + String(digitalRead(4)) + "_" + String(digitalRead(5)) + "_" + String(digitalRead(6)) + "_" + String(digitalRead(7)) + "_" + String(digitalRead(8)) + "_" + String(digitalRead(9)) + "_" + String(digitalRead(10)) + "_" + String(digitalRead(11)) + "_" + String(digitalRead(12)) + "_" + String(digitalRead(13));
  String analog = String(analogRead(A0)) + "_" + String(analogRead(A1)) + "_" + String(analogRead(A2)) + "_" + String(analogRead(A3)) + "_" + String(analogRead(A4)) + "_" + String(analogRead(A5));
  String sentenceToSend = digital + "_" + analog;
  Serial.println(sentenceToSend);
}
