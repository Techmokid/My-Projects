#include <PinToGPIO.h>

PinToGPIO::PinToGPIO() {}

int PinToGPIO::pinToGPIO(int pin) {
	switch (pin) {
		case 0:
			return 16; break;
		case 1:
			return 5; break;
		case 2:
			return 4; break;
		case 3:
			return 0; break;
		case 4:
			return 2; break;
		case 5:
			return 14; break;
		case 6:
			return 12; break;
		case 7:
			return 13; break;
		case 8:
			return 15; break;
		default:
			return -1;
	}
}