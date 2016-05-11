#include "RSA.h"
#include <iostream>
int main()
{
	bool TESTA[16] = {
		true, false, true, false, true, false, false, false, 
		true, true, false, true, true, false, true, true
	};//43227
	bool TESTB[16] = {
		true, false, false, true, true, false, false, true, 
		true, true, true, true, true, false, true, true
	};//39419
	//bool Result[16];//0b1 0100001011010110
	//bool o = BinAdd(TESTA, 16, TESTB, 16, Result, 16);
	//bool hnc;
	//o = BinMinus(TESTA, 16, TESTB, 16, Result, 16, hnc);//Result = 0b 1110 1110 0000
	//int oo;
	//oo = BinCmp(TESTA, 16, TESTB, 16);
	//oo = BinCmp(TESTB, 16, TESTA, 16);
	//oo = BinCmp(TESTA, 16, TESTA, 16);
	//BinLeftShift(TESTA, 16, 20, R, 32);
	//BinMul(TESTA, 16, TESTB, 16, R, 32);
	//bool First[7] = { true, true, false, false, true, false, false };
	//bool Div[2] = { true, true };
	//bool R[7];
	//bool M[7];
	//BinDivMod(First, 7, Div, 2, R, 7, M, 7);
	return 0;
}