//Do not use pins 6, 7, 10, 11

#define motor_pin_A 2
#define motor_pin_B 3
#define restartPin  4

void setupMotor() {
  pinMode(motor_pin_A,OUTPUT);
  pinMode(motor_pin_B,OUTPUT);
  
  digitalWrite(motor_pin_A,LOW);
  digitalWrite(motor_pin_B,LOW);
}

void setSpeed(float input_speed) {
  input_speed = clamp(input_speed,1,-1);
  
  if (input_speed == 0) {
    digitalWrite(motor_pin_A,LOW);
    digitalWrite(motor_pin_B,LOW);
  } else if (input_speed == 1) {
    digitalWrite(motor_pin_B,LOW);
    digitalWrite(motor_pin_A,HIGH);
  } else if (input_speed == -1) {
    digitalWrite(motor_pin_A,LOW);
    digitalWrite(motor_pin_B,HIGH);
  } else if (input_speed > 0) {
    digitalWrite(motor_pin_B,LOW);
    analogWrite(motor_pin_A,input_speed*255);
  } else if (input_speed < 0) {
    digitalWrite(motor_pin_A,LOW);
    analogWrite(motor_pin_B,(-input_speed)*255);
  } else {
    Serial.println("ERROR");
  }
}

float clamp(float in, float A, float B) {
  if (A > B) {
    if (in > A) { return A; }
    if (in < B) { return B; }
    return in;
  } else if (A < B) {
    if (in > B) { return B; }
    if (in < A) { return A; }
    return in;
  } else { return A; }
}

void(* resetFunc) (void) = 0;
void restartArduino() { resetFunc(); digitalWrite(restartPin,HIGH); }