#include <Arduino.h>

class servo {
	public:
		servo();
		void updateServo();
		void write(float angle);
		void writeMilliseconds(int val);
		float radToDeg(float rad);
		bool oneTime();
		int pos = 820;
		int pin = 0;
		bool offset90 = false;
		bool oneTimeActive = false;
	private:
		unsigned long prevTimer = 0;
};

