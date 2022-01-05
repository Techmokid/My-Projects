//Made by Andrey Rumming on 24/01/2018
//This is for use with the Arduino Gamepad Shield and Unity3d Game-making Engine 5.6.0f and higher
//Pin 2 is A, Pin 3 is B, Pin 4 is C, Pin 5 is D, Pin 6 is E, Pin 7 is F, Pin 8 is the Joystick Button, and pins A0-A1 are the pins for the joysticks position (x and y respectively)

void setup() {
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  Serial.begin(9600);
}

void loop() {
  String buttons = String(digitalRead(2)) + "_" + String(digitalRead(3)) + "_" + String(digitalRead(4)) + "_" + String(digitalRead(5)) + "_" + String(digitalRead(6)) + "_" + String(digitalRead(7));
  String Joystick = String(digitalRead(8)) + "_" + String(analogRead(A0)) + "_" + String(analogRead(A1));
  String extraAnalogInputs = String(analogRead(A2)) + "_" + String(analogRead(A3)) + "_" + String(analogRead(A4)) + "_" + String(analogRead(A5));
  String extraDigitalInputs = String(digitalRead(9)) + "_" + String(digitalRead(10)) + "_" + String(digitalRead(11)) + "_" + String(digitalRead(12)) + "_" + String(digitalRead(13));
  
  String sentenceToSend = buttons + "_" + Joystick + "_" + extraAnalogInputs + "_" + extraDigitalInputs;

  Serial.flush();
  Serial.println(sentenceToSend);
  delay(20);
}
