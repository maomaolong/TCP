#include "stdio.h"
#include "TSocket.h"
#include "TProtobuf.h"
#include "common.h"
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#define PACKET_HEADER_LEN (1+4+2)

DWORD WINAPI ClientThread(PVOID pvParam)
{
	char recvBuffer[1024] = { 0 };
	char* pRecv = NULL;
	while (true)
	{
		memset(recvBuffer, 0, sizeof(recvBuffer));
		int len = recv((SOCKET)pvParam, recvBuffer, sizeof(recvBuffer), 0);
		if (len <= 0)
			break;
		printf("len : %d\n", len);
		pRecv = recvBuffer;
		printf("flag : %d\n", (unsigned char)*pRecv);
		pRecv = pRecv + sizeof(unsigned char);

		unsigned int length;
		length = *(unsigned int*)pRecv;
		endianConvert32(&length);
		printf("payload length : %d\n", length);
		pRecv = pRecv + sizeof(unsigned int);

		unsigned short id;
		id = *(unsigned short*)pRecv;
		id = ntohs(id);
		printf("id : %d\n", id);
		pRecv = pRecv + sizeof(unsigned short);

		char *str = pRecv;
		printf("recv : %s\n", str);

		char sendBuffer[1024] = {0};
		TProtobuf tprotobuf;
		unsigned int payloadLen = tprotobuf.getSendBuffer(sendBuffer, sizeof(sendBuffer));
		send((SOCKET)pvParam, sendBuffer, PACKET_HEADER_LEN + payloadLen, 0);

	}
	closesocket((SOCKET)pvParam);
	return 0;
}

void TSocket::TestSocket()
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

	bind(s, (SOCKADDR*)&addr, sizeof(addr));
	listen(s, 5);
	SOCKADDR_IN recvAddr;
	int addrLen = sizeof(recvAddr);

	while (true)
	{
		SOCKET accSocket = accept(s, (SOCKADDR*)&recvAddr, &addrLen);
		if (SOCKET_ERROR == accSocket)
		{
			exit(-1);
		}
		printf("accept ip : %s port : %d\n", inet_ntoa(recvAddr.sin_addr), recvAddr.sin_port);

		HANDLE thread1;
		DWORD threadID;
		thread1 = CreateThread(NULL, 0, ClientThread, (LPVOID)accSocket, 0, &threadID);
	}
}