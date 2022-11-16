#ifndef COMPILER_FUNCTIONS_LIST    // To make sure you don't declare the function more than once by including the header multiple times.
#define COMPILER_FUNCTIONS_LIST

#include <iostream>		// Required for User I/O operations
#include <windows.h>	// Required for console text colour editing
#include <winsock2.h>	// Required for server socket connections
//#include <ws2tcpip.h>

void print(std::string x);
void printFormatted(std::string module, std::string status, std::string msg);
void printSuccess(std::string module, std::string msg);
void printError(std::string module, std::string msg);
void printLog(std::string module, std::string msg);
void printInfo(std::string module, std::string msg);
void printDebug(std::string module, std::string msg);
void SetConsoleColor(int colour);

std::string stringToLower(std::string in);
std::string stringToLowerCapitalized(std::string in);
std::string stringToUpper(std::string in);

void waitForUserInput();

int StartSocket(int port);
bool OpenSocket();
bool CloseSocket();
bool CloseSocket(SOCKET i);
bool CloseClientSocket();
bool BindSocket(int port);
bool ListenOnSocket();
bool AcceptClient();
std::string GetClientResponse();
bool SendToClient(std::string dataToSend);

#endif