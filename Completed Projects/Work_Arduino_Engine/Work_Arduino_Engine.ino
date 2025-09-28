#define Button_Pin  4
#define LED_Pin     5
#define MOSFET_Pin  6

void setup() {
  pinMode(Button_Pin,INPUT_PULLUP);
  pinMode(LED_Pin,OUTPUT);
  pinMode(MOSFET_Pin,OUTPUT);
  pinMode(13,OUTPUT);

  Serial.begin(115200);
  digitalWrite(LED_Pin,HIGH);

}

void loop() {
  if (!digitalRead(Button_Pin)) { return; }
  digitalWrite(LED_Pin,LOW);
  digitalWrite(13,HIGH);

  // Rev up
  analogWrite(MOSFET_Pin,70); delay(100); analogWrite(MOSFET_Pin,40); delay(150);
  analogWrite(MOSFET_Pin,70); delay(100); analogWrite(MOSFET_Pin,40); delay(150);
  analogWrite(MOSFET_Pin,90); delay(100); analogWrite(MOSFET_Pin,40); delay(150);
  analogWrite(MOSFET_Pin,120); delay(100); analogWrite(MOSFET_Pin,40); delay(50);
  
  // Kick over and idle
  analogWrite(MOSFET_Pin,100); delay(200);
  analogWrite(MOSFET_Pin,95); delay(250);
  analogWrite(MOSFET_Pin,90); delay(250);
  analogWrite(MOSFET_Pin,85); delay(250);
  analogWrite(MOSFET_Pin,80); delay(250);
  analogWrite(MOSFET_Pin,75); delay(250);
  analogWrite(MOSFET_Pin,70); delay(250);
  analogWrite(MOSFET_Pin,65); delay(1000);
  analogWrite(MOSFET_Pin,60); delay(1000);

  // Idle down
  for (int i = 0; i < 8; i++) {
    analogWrite(MOSFET_Pin,55); delay(300);
    analogWrite(MOSFET_Pin,45); delay(300);
    analogWrite(MOSFET_Pin,40); delay(300);
    analogWrite(MOSFET_Pin,45); delay(300);
  }

  analogWrite(MOSFET_Pin,35); delay(150);
  analogWrite(MOSFET_Pin,0); delay(1000);

  digitalWrite(13,LOW);
  digitalWrite(LED_Pin,HIGH);
}