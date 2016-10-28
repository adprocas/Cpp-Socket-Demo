#include <iostream>
#include <string>
/*
This program was created in CPA2 at Fanshawe college for C++ Advanced
*/
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


	//Create the socket
	//there are a bunch of choices, like IPX, and stuff like that, but we want to use INET

	SOCKET hSocket = socket(AF_INET, SOCK_DGRAM, 0);
	//LOOK UP MSDN AND ADD ERROR CHECKING

	//Create the server address
	//These data structers are nightmares of macros, structures, and unions
	//Unions are despised by OOP - they pretty much don't exist in anything other than C and C++
	/*
		union utype {
			long n;
			float x;
		};
		utype u;
		//elements of union occupy the same space
		//we could do this
		u.n = 42;
		cout << u.x << endl; // this give some crazy number, because it's treating it as a float
		//this is good (but annoying) because it allows us to save space
	*/
	//cheap trick to initial values to 0
	//this initiliaizes all to 0 from the initializer - not just the first
	sockaddr_in serverAddress = { 0 };
	serverAddress.sin_family = AF_INET;
	//look up big-endian and little-endian
	//Intel had to switch - network order is big-endian
	//hton is host to network - s stands for short - there's also htonl, which is host to network long
	//this has to be done even on a motorola, but since you're on a big-endian machine, it does nothing
	serverAddress.sin_port = htons(PORT);
	//s_addr is actually a macro
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	//bind only takes pointers to sock address - we aren't padding it an address
	//we say, I want the pointer to the base object - in c, this means it's the first element
	//the second is the size of it, and we tell it what the rest of the data is
	int res = bind(hSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(sockaddr_in));

	//MS uses SOCKET_ERROR - unix uses minus 1
	if (res == SOCKET_ERROR) {
		cerr << "Error on bind\n";
		res = WSAGetLastError();
		cout << "Result: " << res << endl;
		closesocket(hSocket);

		return EXIT_FAILURE;

		//NEXT, WE WILL MOVE DATA IN AND OUT
	}

	//terminate
	//unix just uses close - handles in unix are all integers, so you can just use close
	//but POSIX does have a closesocket
	closesocket(hSocket);

	//all this wsa stuff (Windows Socket API) doesn't have to be done in unix - sockets are started
	//you only need to do this once per application
	WSACleanup();
}