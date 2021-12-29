#include <Mouse.h>

int current = 0;

void setup() {
  while (!digitalRead(4)) {}
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  Serial.begin(9600);
  Mouse.begin();
}

void loop() {
  if((digitalRead(2)==false) && (digitalRead(3)==false) && (current!=0)) {
    current = 0;
    Serial.println("Setting to User Control");
    Mouse.end();
  }
  
  if(current==0) {
    if(digitalRead(2)) {
      Serial.println("Detected Water Option");
      current = 2;
      Mouse.begin();
    }
    if(digitalRead(3)) {
      Serial.println("Detected Lava Option");
      current = 3;
      Mouse.begin();
    }
  } else if(current==2) {
    delay(135);
    Mouse.click();
    delay(135);
    Mouse.click();
  } else {
    delay(750);
    Mouse.click();
    delay(83);
    Mouse.click();
  }
}
