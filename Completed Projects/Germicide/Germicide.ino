//Here is your germicide machine code! Feel free to change any of the pins used by altering the "#define PIN_NAME_HERE PIN_NUMBER" statements
#include <Servo.h>

#define PIR_Pin 2       //Movement sensor
#define Strobe_Pin 3    //The strobe pin turns on the warning lights
#define Relay_Pin 4     //The relay pin turns the germicide on.
#define trigPin 5       //Ultrasonic sensor trigger pin
#define echoPin 6       //Ultrasonic sensor echo pin
#define servoPin 7      //Servo for the ultrasonic sensor
#define IRPin 8         //IR input pin (For starting the process)
#define printData true

//This tells the system to round to the nearest "timeMultiplier" minutes when calculating the amount of time to stay on for
#define timeMultiplier 15

//This tells the chip how fast to flash pin 13 while running
int flashInterval = 200;

//These are variables you don't need to touch
Servo myservo;

bool running = false;

unsigned long timer = 0;
unsigned long flashTimer = 0;

float minutesToWait = 0;
float volumeToTimeModifier = 0.15;

void setup() {
  Serial.begin(115200);
  delay(500);
  
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(Strobe_Pin,OUTPUT);
  pinMode(Relay_Pin,OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  digitalWrite(LED_BUILTIN,LOW);
  
  myservo.attach(servoPin);
}

void loop() {
  flashLED();
  if ((!digitalRead(IRPin)) && (!digitalRead(PIR_Pin)) && (!running)) { startProcess(); }
  if (digitalRead(PIR_Pin) && running) { SerialPrintlnFunction("Detected Movement!"); stopProcess(); digitalWrite(LED_BUILTIN,HIGH); }
  if (running) { if (millis() - timer >= minutesToWait * 1000 * 60) { SerialPrintlnFunction("Process Complete!"); stopProcess(); digitalWrite(LED_BUILTIN,LOW); } }
}

void stopProcess() {running = false; digitalWrite(Relay_Pin,LOW); digitalWrite(Strobe_Pin,LOW); SerialPrintlnFunction("\n\n"); }
void startProcess() {
  SerialPrintlnFunction("Starting Process...");
  
  running = true;
  digitalWrite(Strobe_Pin,HIGH); getRoomSize(); digitalWrite(Relay_Pin,HIGH);
  flashTimer = millis();
  timer = millis();
  
  SerialPrintlnFunction("Calculated ETA: " + String(minutesToWait) + " mins");
}

void getRoomSize() {
  Serial.begin(115200);
  
  myservo.write(10); delay(500); SerialPrintFunction("Retrieving X distance 1..."); float temp_X_1 = getDistance(); SerialPrintlnFunction("Done. Measured: " + String(temp_X_1) + " meters");
  myservo.write(100); delay(500); SerialPrintFunction("Retrieving Y distance 1..."); float temp_Y_1 = getDistance(); SerialPrintlnFunction("Done. Measured: " + String(temp_Y_1) + " meters");
  myservo.write(180); delay(500); SerialPrintFunction("Retrieving X distance 2..."); float temp_X_2 = getDistance(); SerialPrintlnFunction("Done. Measured: " + String(temp_X_2) + " meters");
  myservo.write(100); delay(500); SerialPrintFunction("Retrieving Y distance 2..."); float temp_Y_2 = getDistance(); SerialPrintlnFunction("Done. Measured: " + String(temp_Y_2) + " meters");
  myservo.write(10);
  
  minutesToWait = volumeToTimeSeconds((temp_X_1 + temp_X_2) * (temp_Y_1 + temp_Y_2));
}

float getDistance() {
  flashLED();
  
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the calculated distance
  float result = pulseIn(echoPin, HIGH) * 0.034/2000;
  if (result != 0) { return result; }
  return getDistance();
}

float volumeToTimeSeconds(float roomVolume) { return ceil((roomVolume * volumeToTimeModifier) / timeMultiplier) * timeMultiplier; }

void SerialPrintFunction(String msg) { if (printData) { Serial.print(msg); } }
void SerialPrintlnFunction(String msg) { if (printData) { Serial.println(msg); } }
