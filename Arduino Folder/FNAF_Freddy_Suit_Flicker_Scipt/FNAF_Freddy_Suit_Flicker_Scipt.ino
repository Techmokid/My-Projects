void setup() {
  Serial.begin(9600);
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);
}

void loop() {
  digitalWrite(8,HIGH);
  int randomVal = random(20,100);
  delay(randomVal);
  
  digitalWrite(8,LOW);
  randomVal = random(0,500);
  delay(randomVal);
}
