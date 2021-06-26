#include <Arduino.h>

class servo {
	public:
		servo();
		void updateServo();
		void write(float angle);
		void writeMilliseconds(int val);
		float radToDeg(float rad);
		bool oneTime();
		float pos = 1500;
		int pin = 0;
		bool offset90 = false;
		bool oneTimeActive = false;
		float startValOffset = 0;
		float endValOffset = 0;
	private:
		unsigned long prevTimer = 0;
};

