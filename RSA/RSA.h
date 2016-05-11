#include <string>
template < typename Type > 
inline Type max(Type A, Type B){ return A > B ? A : B; };
template <typename Type>
inline Type min(Type A, Type B){ return A > B ? B : A; };
int ExGCD(int a, int b, int * x, int * y);
bool baseBinAdd(bool Ai, bool Bi, bool Ci, bool &Cip1);
//单位相加 ci前一进位，cipi返回加完进位，Bi被加数，Ai加数，返回结果
bool BinAdd(bool * A, int Adigit, bool * B, int Bdigit, bool * result, int Rdigit);
//二进制加法，result=A+B，Adigit A的位数 Bdigit，Rdigit同理，返回加完进位（为1溢出
void BinComplement(bool *N, int Adigit);
//求补数
bool BinMinus(bool * A, int Adigit, bool * B, int Bdigit, bool * result, int Rdigit, bool &hnc);
//返回减后的符号位，result = A - B，hnc符号位相加后的进位
int BinCmp(bool *A, int Adigit, bool *B, int Bdigit);
//比较两个二进制 A>B返回1 A<B返回-1 A=B返回0
void BinLeftShift(bool * A, int Adigit, int Shift, bool * Result, int Rdigit);
//左移
bool BinMul(bool * A, int Adigit, bool * B, int Bdigit, bool * Result, int Rdigit);
bool BinDivMod(bool *A, int Adigit, bool *B, int Bdigit,
	bool * DivResult, int Ddigit,
	bool * ModResult, int Mdigit);
