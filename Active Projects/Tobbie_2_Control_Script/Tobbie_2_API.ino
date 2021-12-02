int myRows[] = {21,22,23,24,25};
int myColumbs[] = {4,7,3,6,10};

void walkForwards(bool walk) { digitalWrite(13,walk); }
void walkBackwards(bool walk) { digitalWrite(14,walk); }
void turnRight(bool walk) { digitalWrite(15,walk); }
void turnLeft(bool walk) { digitalWrite(16,walk); }

void startDistanceSensors() { digitalWrite(12,HIGH); }
float readLeftDist() { return analogRead(1); }
float readRightDist() { return analogRead(2); }

void setPin(int pin, bool status) {
  pinMode(pin,OUTPUT);
  digitalWrite(pin,status);
}

void setLED(int x, int y, bool status) {
  setPin(myColumbs[x],!status);
  setPin(myRows[y],status);
}

void setMicLED(bool status) { setPin(10,!status); setPin(28,status); }

bool getButton(int ID) {
  if (ID == 0) {
    return digitalRead(5);
  } else if (ID == 1) {
    return digitalRead(11);
  } else { return 0; }
}

void setTone(float frequency) {
  
}

//pin 27 is the speaker

//pins 3,0,4,1,10,2 are analogIn