#define trigPin 2
#define echoPin 3
#define outPin  4

#define senseDist 40

bool errorState = false;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(outPin, OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  int distance = duration*0.034/2;
  if (distance != 0) {
    errorState = false;
    digitalWrite(LED_BUILTIN,errorState);
    
    if (distance < senseDist) {
      digitalWrite(outPin,HIGH);
    } else {
      digitalWrite(outPin,LOW);
    }
    delay(5000);
  } else {
    digitalWrite(LED_BUILTIN,errorState);
    errorState = !errorState;
  }
}
