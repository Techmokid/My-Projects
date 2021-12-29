#define motor1Pin1 13
#define motor1Pin2 12
#define motor1Pin3 11
#define motor1Pin4 10

#define motor2Pin1 9
#define motor2Pin2 8
#define motor2Pin3 7
#define motor2Pin4 6

#define motor3Pin1 5
#define motor3Pin2 4
#define motor3Pin3 3
#define motor3Pin4 2

#define motor4Pin1 A0
#define motor4Pin2 A1
#define motor4Pin3 A2
#define motor4Pin4 A3

int position1 = 0;
int position2 = 0;
int position3 = 0;
int position4 = 0;

void setup() {
  pinMode(13,OUTPUT);
}

void loop() {
  stepLeft1();
  stepLeft2();
  stepLeft3();
  stepLeft4();
  Serial.read();
}
