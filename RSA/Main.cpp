#include "RSA.h"
#include "BinCalc.h"
#include <iostream>
#include <stdlib.h>
int main()
{
	std::cout << "On calc prime num ... " << std::endl;
	createprime();
	std::cout << "On calc key ... " << std::endl;
	calcKey();
	bool * testbool = new bool[7]{
		true, false, false,
			false, true, false, true
	};
	std::cout << "before encryption:" << std::endl;
	outputboolarray(testbool,7);
	std::cout << std::endl;
	BinNum R = Encrypt(testbool, 7);
	std::cout << "after encryption:" << std::endl;
	outputB(R);
	BinNum dec = Decrypt(R);
	std::cout << "after decryption:" << std::endl;
	outputB(dec);
	std::cout << "if decryption is not equal the test ,may be overflow on calc (a+b) % n, i can't fix it,sorry for that" << std::endl;
	system("pause");
	return 0;
}