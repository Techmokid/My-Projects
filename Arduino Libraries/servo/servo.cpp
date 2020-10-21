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
	if (offset90) { pos = (90 - angle) / 180 * 700 * 2 + 820;
	} else { pos = angle / 180 * 1750 + 720; }
}

bool servo::oneTime() {
	if (oneTimeActive) {
		oneTimeActive = false;
		return true;
	}

	return false;
}

float servo::radToDeg(float rad) { return rad * 180 / 3.14159; }