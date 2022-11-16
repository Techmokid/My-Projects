#include "functions.h"

//This is a stripped down version of the code found at:
//https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket

#pragma comment(lib,"Ws2_32.lib")

#define DEFAULT_BUFLEN 1024

WSADATA wsaData = {0};
int iResult;
char recvbuf[DEFAULT_BUFLEN];
int recvbuflen = DEFAULT_BUFLEN;

SOCKET sock = INVALID_SOCKET;
SOCKET clientSock = INVALID_SOCKET;
int iFamily = AF_INET;
int iType = 1;
int iProtocol = IPPROTO_TCP;

sockaddr_in service;
int boundToPort = -1;

int StartSocket(int port) {
	printFormatted("SERVER","Info","Starting up server");
	if (!OpenSocket())     { return 1; }
	if (!BindSocket(port)) { return 2; }
	if (!ListenOnSocket()) { return 3; }
	return 0;
}

bool OpenSocket() {
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printFormatted("SERVER","Error","WSAStartup failed with error: " + std::to_string(iResult));
        return false;
    }
	
	sock = socket(iFamily, iType, iProtocol);
    if (sock != INVALID_SOCKET) {
		printFormatted("SERVER","Success","Socket function succeeded");
		return true;
	}
	
	printFormatted("SERVER","Error","Failed to start socket with error: " + std::to_string(WSAGetLastError()));
	WSACleanup();
	return false;
}

bool CloseSocket() { CloseSocket(sock); sock == INVALID_SOCKET; }
bool CloseClientSocket() { CloseSocket(clientSock); clientSock == INVALID_SOCKET; }
bool CloseSocket(SOCKET i) {
	boundToPort = -1;
	iResult = closesocket(i);
	if (iResult != SOCKET_ERROR) {
		printFormatted("SERVER","Success","Closed socket");
		return true;
	}
	printFormatted("SERVER","Error","Failed to close socket with error: " + std::to_string(WSAGetLastError()));
	WSACleanup();
	return false;
}

bool BindSocket(int port) {
	if (sock == INVALID_SOCKET) { return false; }
	
	service.sin_family = iFamily;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(port);
	
	iResult = bind(sock, (SOCKADDR *) &service, sizeof (service));
	if (iResult == SOCKET_ERROR) {
		printFormatted("SERVER","Error","Failed to bind socket to port with error: " + std::to_string(WSAGetLastError()));
		CloseSocket();
		return false;
	}
	
	printFormatted("SERVER","Success","Bound socket to port: " + std::to_string(port));
	boundToPort = port;
	return true;
}

bool ListenOnSocket() {
	if (iProtocol == IPPROTO_UDP) { printFormatted("SERVER","Warning","UDP connection does not support listening"); return false; }
	if (sock == INVALID_SOCKET) { return false; }
	if (boundToPort == -1) { return false; }
	
	if (listen(sock, SOMAXCONN) == SOCKET_ERROR) {
		printFormatted("SERVER","Error","Could not listen on port: " + std::to_string(boundToPort));
		print(std::to_string(WSAGetLastError()));
		return false;
	}
	
	printFormatted("SERVER","Log","Listening on socket...");
}

bool AcceptClient() {
	if (sock == INVALID_SOCKET) { printFormatted("SERVER","ERROR","Server socket not initialized"); return false; }
	if (boundToPort == -1) { printFormatted("SERVER","ERROR","Server socket not bound to port"); return false; }
	
	// Try to receive some data, this is a blocking call
	clientSock = accept(sock, NULL, NULL);
	if (clientSock == INVALID_SOCKET) {
        printFormatted("SERVER","Warning","Client accept failed with error: " + std::to_string(WSAGetLastError()));
        CloseSocket(sock);
        return false;
    } else {
        printFormatted("SERVER","Success","Client connected");
	}
	
	CloseSocket(sock);
}

std::string GetClientResponse() {
	if (clientSock == INVALID_SOCKET) { printFormatted("SERVER","ERROR","Client socket not initialized"); return ""; }
	
	iResult = recv(clientSock, recvbuf, recvbuflen, 0);
	while(iResult == 0) {
		if (iResult < 0){ print("Error receiving data from client. Trying again"); }
		iResult = recv(clientSock, recvbuf, recvbuflen, 0);
	}
	
	return std::string(recvbuf);
}

bool SendToClient(std::string dataToSend) {
	if (clientSock == INVALID_SOCKET) { printFormatted("SERVER","ERROR","Client socket not initialized"); return false; }
	
	char msg[dataToSend.length() + 1];
	strcpy(msg, dataToSend.c_str());
	
	iResult = send(clientSock, msg, dataToSend.length(), 0);
	if (iResult != SOCKET_ERROR) { return true; }
	
    printFormatted("SERVER","ERROR","Client send failed: " + std::to_string(WSAGetLastError()));
    CloseSocket(clientSock);
    return false;
}
















