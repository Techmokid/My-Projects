#include "functions.h"

#define printFormattingModuleLength 10

#define black			0
#define d_blue			1
#define green			2
#define turqoise		3
#define d_red			4
#define d_purple		5
#define d_yellow		6
#define gray			7
#define d_gray			8
#define blue			9
#define l_green			10
#define l_blue			11
#define red				12
#define p_purple		13
#define yellow			14
#define white			15

void print(std::string x) {
	std::cout << x << std::endl; //std::flush;
}

void waitForUserInput () {
	std::system("pause");
}

std::string stringToLower(std::string in) {
    std::string result = "";
	for (int i = 0; i < in.length(); i++) {
		result += std::tolower(in[i]);
	}
	return result;
}

std::string stringToUpper(std::string in) {
    std::string result = "";
	for (int i = 0; i < in.length(); i++) {
		result += std::toupper(in[i]);
	}
	return result;
}

std::string stringToLowerCapitalized(std::string in) {
    std::string result = stringToLower(in);
	result[0] = std::toupper(result[0]);
	return result;
}

void SetConsoleColor(int colour) {
   HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hCon,colour);
}

void printSuccess(std::string module, std::string msg) { printFormatted(module, "success", msg); }
void printError(std::string module,   std::string msg) { printFormatted(module, "error", msg); }
void printLog(std::string module,     std::string msg) { printFormatted(module, "log", msg); }
void printInfo(std::string module,    std::string msg) { printFormatted(module, "info", msg); }
void printDebug(std::string module,   std::string msg) { printFormatted(module, "debug", msg); }
void printFormatted(std::string module, std::string status, std::string msg) {
	std::cout << "[" + module + "]";
	for (int i = 0; i <	printFormattingModuleLength - module.length(); i++) {
		std::cout << " ";
	}
	
	std::cout << "[";
	status = stringToLowerCapitalized(status);
	
	if (status.length() > 7) { status = "???????"; }
	if (status == "Success") {
		SetConsoleColor(green);
		std::cout << "Success";
	} else if (status == "Warning") {
		SetConsoleColor(yellow);
		std::cout << "Warning";
	} else if (status == "Error") {
		SetConsoleColor(red);
		std::cout << " Error ";
	} else if (status == "Log") {
		SetConsoleColor(gray);
		std::cout << "  Log  ";
	} else if (status == "Info") {
		SetConsoleColor(gray);
		std::cout << "  Info ";
	} else if (status == "Debug") {
		SetConsoleColor(d_purple);
		std::cout << " Debug ";
	} else {
		SetConsoleColor(turqoise);
		std::cout << "???????";
	}
	
	SetConsoleColor(white);
	std::cout << "]: " + msg << std::endl;
}