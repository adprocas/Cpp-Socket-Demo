#include <iostream>
#include <string>

using namespace std;

#include <WinSock2.h>
#include <WS2tcpip.h>

unsigned short const PORT = 49153;

int main() {
	cout << "UDPServer\n";

	//initialize Wsa
	WSADATA wsaData;

	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult != 0) {
		cerr << "WSAStartup failed: " << iResult << endl;
		return EXIT_FAILURE;
	}


	//all this wsa stuff (Windows Socket API) doesn't have to be done in unix - sockets are started
	//you only need to do this once per application
	WSACleanup();
}