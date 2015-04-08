#include <stdio.h>
#include <winsock2.h>
//#pragma comment(lib,"ws2_32.lib")

int main(int argc, char *argv[])
{
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(1, 1);
	WSAStartup(wVersionRequested, &wsaData);

	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(9000);

	int len;
	connect(s, (SOCKADDR*)&addr, sizeof(addr));
	getchar();
	return 0;
}