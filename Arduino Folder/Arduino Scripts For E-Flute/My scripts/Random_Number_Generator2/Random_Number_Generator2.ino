int randNumber = 0;

void setup() {
  pinMode(A0,INPUT);
  pinMode(13,OUTPUT);
  randomSeed(analogRead(0));
  Serial.begin(9600);
}

void loop() {
  randNumber = random(0,2);
  if (randNumber == 1) {
    digitalWrite(13,HIGH);
  } else {
    digitalWrite(13,LOW);
  }
  randNumber = analogRead(A0);
  delay(randNumber);
  Serial.println(randNumber);
}
