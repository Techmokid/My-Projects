//Do not use pins 6, 7, 10, 11

#define motor_pin_A 5
#define motor_pin_B 3

void setupMotor() {
  pinMode(motor_pin_A,OUTPUT);
  pinMode(motor_pin_B,OUTPUT);
  
  digitalWrite(motor_pin_A,LOW);
  digitalWrite(motor_pin_B,LOW);
}

void setSpeed(float input_speed) {
  input_speed = max(min(input_speed,1),-1);
  
  if (input_speed == 0) {
    digitalWrite(motor_pin_A,LOW);
    digitalWrite(motor_pin_B,LOW);
  } else if (input_speed == 1) {
    digitalWrite(motor_pin_A,HIGH);
    digitalWrite(motor_pin_B,LOW);
  } else if (input_speed == -1) {
    digitalWrite(motor_pin_A,LOW);
    digitalWrite(motor_pin_B,HIGH);
  } else if (input_speed > 0) {
    analogWrite(motor_pin_A,input_speed*255);
    digitalWrite(motor_pin_B,LOW);
  } else {
    digitalWrite(motor_pin_A,LOW);
    analogWrite(motor_pin_B,(-input_speed)*255);
  }
}
