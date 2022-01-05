void setup() {
  Serial.begin(9600);
}

void loop() {
  //analogRead(0) is up and down, with up increasing in value and down decreasing
  //analogRead(1) is tilt clockwise and anticlockwise, with clockwise increasing in value and anticlockwise decreasing
  
  Serial.print(analogRead(0));
  Serial.print(" ");
  Serial.println(analogRead(1));
}
