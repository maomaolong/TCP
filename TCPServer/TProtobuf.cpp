
#include "TProtobuf.h"
#include "person.pb.h"
#include "common.h"
#include "TMysql.h"
#include <string>
#include <winsock2.h>
#pragma comment(lib, "libprotobuf.lib")
using namespace std;
using namespace test::protocol::sgp;

unsigned int TProtobuf::getSendBuffer(char *sendBuffer, int sendLen)
{
	//校验协议版本     
	GOOGLE_PROTOBUF_VERIFY_VERSION;   
	PersonInfo info = TestMysql();
	Person person;
	person.set_id(info.id);
	person.set_name(info.name.c_str());
	person.set_email(info.email.c_str());

	char* pSend = NULL;
	memset(sendBuffer, 0, sendLen);
	pSend = sendBuffer;
	string payload;
	person.SerializeToString(&payload);
	unsigned char flag = 12;
	unsigned int payloadLen = payload.length();
	unsigned short sendid = 1;
	*(unsigned char*)pSend = flag;
	pSend += sizeof(unsigned char);

	endianConvert32(&payloadLen);
	*(unsigned int*)pSend = payloadLen;
	pSend += sizeof(unsigned int);

	*(unsigned short*)pSend = htons(sendid);
	pSend += sizeof(unsigned short);

	strcpy(pSend, payload.c_str());

	return payload.length();
}