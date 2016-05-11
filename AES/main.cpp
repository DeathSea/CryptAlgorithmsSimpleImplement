#include "AES.h"
using namespace std;
#define TEST 0
#define CFBTEST 1
#define CBCTEST 1
#define OFBTEST 1
int main()
{
#if TEST
	char * B = new char[16]{ (char)0x32,
		(char)0x43,
		(char)0xf6,
		(char)0xa8,
		(char)0x88,
		(char)0x5a,
		(char)0x30,
		(char)0x8d,
		(char)0x31,
		(char)0x31,
		(char)0x98,
		(char)0xa2,
		(char)0xe0,
		(char)0x37,
		(char)0x07,
		(char)0x34, };
	char * key = new char[16]{
		(char)0x2b,
		(char)0x7e,
		(char)0x15,
		(char)0x16,
		(char)0x28,
		(char)0xae,
		(char)0xd2,
		(char)0xa6,
		(char)0xab,
		(char)0xf7,
		(char)0x15,
		(char)0x88,
		(char)0x09,
		(char)0xcf,
		(char)0x4f,
		(char)0x3c,
	};
	char * R = new char[16];
	char * TESTSTR = new char[17]{
		'I',
		' ',
		'A',
		'M',
		' ',
		'A',
		' ',
		'T',
		'E',
		'S',
		'T',
		'S',
		'T',
		'I',
		'N',
		'G', '\0'
	};
	char * TESTKEY = new char[16]{
		'A',
		' ',
		'T', 
		'E', 
		'S', 
		'T', 
		' ', 
		'K', 
		'E', 
		'Y',
		' ',
		'1',
		'2',
		'3',
		'4',
		'5',
	};
	SetKeyLength(128);
	EncdeAES(B,key,R);
	std::cout << "AFTER AES, THE STATE IS:" << endl;
	outputSTATE();
	
	DecdeAES(R,key,B);
	std::cout << "AFTER DeAES, THE STATE IS:" << endl;
	outputSTATE();

	EncdeAES(TESTSTR, TESTKEY, R);
	std::cout << "AFTER AES, THE RESULT(IN hex) IS:" << endl;
	for (int index = 0; index < 16; index++){ 
		unsigned short E = R[index];E&=255; std::cout << std::hex << E;
	}
	std::cout << std::endl;
	DecdeAES(R, TESTKEY, TESTSTR);
	std::cout << "AFTER DeAES, THE RESULT IS:" << endl;
	std::cout << TESTSTR << endl;
#else
#endif
	char TestS[44] = {
		't', 'h', 'e', ' ', 'q', 'u', 'i', 'c', 'k', ' ', 'b', 'r', 'o', 'w', 'n', ' ', 'f', 'o', 'x', ' ', 'j', 'u', 'm', 'p', 's', ' ', 'o', 'v', 'e', 'r', ' ', 't', 'h', 'e', ' ', 'l', 'a', 'z', 'y', ' ', 'd', 'o', 'g', '\0'
	};
	char IV[16] = { 'w', 'e', 'a', 'r', 'e', 't', 'h', 'e', 'C', 'h', 'a', 'm', 'p', 'i', 'o', '\0' };
	char TestKey[32] = { 'y', 'o', 'u', ' ', 'a', 'r', 'e', ' ', 'm', 'y', ' ', 'a', 'p', 'p', 'l', 'e', ' ', 'i', 'n', ' ', 'm', 'y', ' ', 'e', 'y', 'e', ',', 'A', 'X', 'D', '=', '\0' };
	int sourceLen = strlen(TestS);
	int reslen = sourceLen / 16 * 16 + (sourceLen % 16 == 0 ? 0 : 16) + 1;
	char * res = (char *)malloc(sizeof(char)*reslen);
	char * decryptRe = (char *)malloc(sizeof(char)*reslen);
#if CFBTEST
	std::cout << "###################AES 256 CFB TEST start###################" << std::endl;
	AES_256_CFB_encrypt(TestS, TestKey, res, IV);
	res[reslen - 1] = '\0';
	std::cout << "===============AFETER ENCRYPTION================" << std::endl;
	for (int index = 0; index < reslen - 1; index++){
		unsigned short E = res[index]; E &= 255; std::cout << std::hex << E << " ";
	}
	std::cout << std::endl;
	AES_256_CFB_decrypt(res, TestKey, decryptRe, IV);
	std::cout << "===============AFETER DECRYPTION================" << std::endl;
	std::cout << decryptRe << std::endl;
	std::cout << "###################AES 256 CFB TEST end###################" << std::endl;
#else
#endif
#if CBCTEST
	std::cout << "###################AES 256 CBC TEST start###################" << std::endl;
	AES_256_CBC_encrypt(TestS, TestKey, res, IV);
	res[reslen - 1] = '\0';
	std::cout << "===============AFETER ENCRYPTION================" << std::endl;
	for (int index = 0; index < reslen - 1; index++){
		unsigned short E = res[index]; E &= 255; std::cout << std::hex << E << " ";
	}
	std::cout << std::endl;
	AES_256_CBC_decrypt(res, TestKey, decryptRe, IV);
	std::cout << "===============AFETER DECRYPTION================" << std::endl;
	std::cout << decryptRe << std::endl;
	std::cout << "###################AES 256 CBC TEST end###################" << std::endl;

#else
#endif
#if OFBTEST
	std::cout << "###################AES 256 OFB TEST start###################" << std::endl;
	AES_256_OFB_encrypt(TestS, TestKey, res, IV);
	res[reslen - 1] = '\0';
	std::cout << "===============AFETER ENCRYPTION================" << std::endl;
	for (int index = 0; index < reslen - 1; index++){
		unsigned short E = res[index]; E &= 255; std::cout << std::hex << E << " ";
	}
	std::cout << std::endl;
	AES_256_OFB_decrypt(res, TestKey, decryptRe, IV);
	std::cout << "===============AFETER DECRYPTION================" << std::endl;
	std::cout << decryptRe << std::endl;
	std::cout << "###################AES 256 OFB TEST end###################" << std::endl;

#else
#endif
	return 0;
}