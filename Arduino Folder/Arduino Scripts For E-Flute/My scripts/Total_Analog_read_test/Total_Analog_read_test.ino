void setup(){
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  Serial.begin(9600);
}

void loop(){
  Serial.print("A0 = ");
  Serial.print(analogRead(A0));
  Serial.print("      ");
  Serial.print("A1 = ");
  Serial.print(analogRead(A1));
  Serial.print("      ");
  Serial.print("A2 = ");
  Serial.print(analogRead(A2));
  Serial.print("      ");
  Serial.print("A3 = ");
  Serial.print(analogRead(A3));
  Serial.print("      ");
  Serial.print("A4 = ");
  Serial.print(analogRead(A4));
  Serial.print("      ");
  Serial.print("A5 = ");
  Serial.println(analogRead(A5));
  delay(50);
}
