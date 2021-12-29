unsigned long echo = 0;
int ultraSoundSignal = 9; // Ultrasound signal pin
unsigned long ultrasoundValue = 0;
int check = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(ultraSoundSignal,OUTPUT);
  digitalWrite(7,HIGH);
  delay(500);
  digitalWrite(7,LOW);
  delay(500);
}

unsigned long ping()
{
  pinMode(ultraSoundSignal, OUTPUT);
  digitalWrite(ultraSoundSignal, LOW);
  delayMicroseconds(2);
  digitalWrite(ultraSoundSignal, HIGH);
  delayMicroseconds(5);
  digitalWrite(ultraSoundSignal, LOW);
  pinMode(ultraSoundSignal, INPUT);
  digitalWrite(ultraSoundSignal, HIGH);
  // To change the timeout for the sensor, do this...
  // echo = pulseIn(ultraSoundSignal, HIGH, 38000)
  echo = pulseIn(ultraSoundSignal, HIGH);
  ultrasoundValue = (echo / 58.138);
  return ultrasoundValue;
}

void loop()
{
  int x = 0;
  x = ping();
  Serial.print(x);
  Serial.print(", ");
  x = x * analogRead(A1) / 5;
  tone(2,x);
  Serial.print(analogRead(A1));
  Serial.print(", ");
  Serial.print(x);
  Serial.print(", ");
  delay(analogRead(A0));
  if ((x - 30) > check > (x + 30)) {
    digitalWrite(7,HIGH);
  } else {
    digitalWrite(7,LOW);
  }
  check = x;
  Serial.println(analogRead(A0));
}
