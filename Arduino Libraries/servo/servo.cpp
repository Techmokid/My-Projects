#include "servo.h"

servo::servo() {}

void servo::updateServo() {
	if (millis() - prevTimer >= 20) {
		prevTimer = millis();
		pinMode(pin,OUTPUT);
		digitalWrite(pin, HIGH);
		delayMicroseconds(pos);
		digitalWrite(pin, LOW);
	}
}

void servo::writeMilliseconds(int val) { pos = val; }
void servo::write(float angle) {
	if (offset90) { angle = (90 - angle); }
	
	// 1ms is full left. 2ms is full right
	pos = 1000 + ((1000 + startValOffset + endValOffset)*angle) / 180 - endValOffset;
}

bool servo::oneTime() {
	if (oneTimeActive) {
		oneTimeActive = false;
		return true;
	}

	return false;
}

float servo::radToDeg(float rad) { return rad * 180 / 3.14159; }