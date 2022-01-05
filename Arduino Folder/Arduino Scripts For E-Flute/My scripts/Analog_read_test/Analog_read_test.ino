void setup(){
  pinMode(A1,INPUT);
  Serial.begin(9600);
}

void loop(){
  Serial.println(analogRead(A1));
  delay(50);
}
