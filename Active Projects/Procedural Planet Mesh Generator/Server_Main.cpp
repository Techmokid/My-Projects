#include "functions.h"

#include <cstdio>
#include <string>
#include <chrono>

void delay(unsigned int t) {
	std::chrono::system_clock::time_point waitUntil = std::chrono::system_clock::now() + std::chrono::seconds(5);
	std::this_thread::sleep_until(waitUntil);
}

int main(int argc, char *argv[]) {
	delay(5000);
	return 0;
}