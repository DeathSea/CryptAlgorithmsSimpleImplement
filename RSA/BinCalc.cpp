#include "BinCalc.h"
#include <stdlib.h>
#include <time.h>
#if Convert
unsigned int convert(BinNum &A)
{
	unsigned  int r = 0, index = 0;
	while (index < MAXDIGIT)
	{
		r <<= 1;
		if (A.High[index] == true){ r += 1; }
		
		index++;
	}
	index = 0;
	while (index < MAXDIGIT)
	{
		r <<= 1;
		if (A.Low[index] == true){ r += 1; }

		index++;
	}
	return r;
}
#endif
int BinCmp(BinNum &A, BinNum &B)
{
	if (A.sign == false && B.sign == true)return 1;
	else if (A.sign == true && B.sign == false)return -1;
	int Aindex = 0; int Bindex = 0;
	if (!A.HighisZero && !B.HighisZero)
	{
		while (Aindex != MAXDIGIT)
		{
			if (A.High[Aindex] && !B.High[Bindex])return 1;
			if (!A.High[Aindex] && B.High[Bindex])return -1;
			Aindex++; Bindex++;
		}
	}
	else if (A.HighisZero && !B.HighisZero)
	{
		Bindex = 0;
		while (Bindex != MAXDIGIT)
		{
			if (B.High[Bindex])return -1;
			Bindex++;
		}
	}
	else if (!A.HighisZero && B.HighisZero)
	{
		Aindex = 0;
		while (Aindex != MAXDIGIT)
		{
			if (A.High[Aindex])return 1;
			Aindex++;
		}
	}
	Aindex = 0; Bindex = 0;
	while (Aindex != MAXDIGIT)
	{
		if (A.Low[Aindex] && !B.Low[Bindex])return 1;
		if (!A.Low[Aindex] && B.Low[Bindex])return -1;
		Aindex++; Bindex++;
	}
	return 0;
}
bool baseBinAdd(bool Ai, bool Bi, bool Ci, bool &Cip1)
{
	bool S = Ai ^ Bi ^ Ci;
	Cip1 = (Ai & Bi) | (Bi & Ci) | (Ci & Ai);
	return S;
}
BinNum::BinNum(bool *Sour, unsigned int length, bool sign)
{
	if (length > MAXDIGIT)
	{
		throw std::length_error("Too Long Binary Num");
	}
	this->Low = new bool[MAXDIGIT];
	this->High = new bool[MAXDIGIT];
	memset(this->Low, false, MAXDIGIT);
	memset(this->High, false, MAXDIGIT);
	this->HighisZero = true;
	if (Sour)
	{
		memmove_s(this->Low + MAXDIGIT - length, MAXDIGIT, Sour, length);
	}
	this->sign = sign;
}
BinNum::BinNum(BinNum&B)
{
	this->Low = new bool[MAXDIGIT];
	this->High = new bool[MAXDIGIT];
	memmove_s(this->Low, MAXDIGIT, B.Low, MAXDIGIT);
	memmove_s(this->High, MAXDIGIT, B.High, MAXDIGIT);
	this->sign = B.sign;
	this->HighisZero = B.HighisZero;
}
BinNum::BinNum()
{
	this->Low = new bool[MAXDIGIT];
	this->High = new bool[MAXDIGIT];
	memset(this->Low, false, MAXDIGIT);
	memset(this->High, false, MAXDIGIT);
	this->sign = false;
	this->HighisZero = true;
}
bool BinNum::TestHighisZero()
{
	bool t = false; int index = 0;
	while (index < MAXDIGIT){ t |= High[index]; index++; }
	return !t;
}
bool BinNum::isZero()
{
	bool t = false; int index = 0;
	while (index < MAXDIGIT){ t |= Low[index]; index++; }
	if (!this->HighisZero)
	{
		index = 0;
		while (index < MAXDIGIT){ t |= High[index]; index++; }
	}
	return !t;
}

BinNum BinNum::operator+(BinNum &B)
{
	BinNum R = BinNum();
	bool C = false;
	for (int index = MAXDIGIT - 1; index >= 0; index--)
	{
		R.Low[index] = baseBinAdd(this->Low[index], B.Low[index], C, C);
	}
	if (!this->HighisZero)
	{
		R.HighisZero = false;
		if (!B.HighisZero)
		{
			for (int index = MAXDIGIT - 1; index >= 0; index--)
			{
				R.High[index] = baseBinAdd(this->High[index], B.High[index], C, C);
			}
		}
		else
		{
			for (int index = MAXDIGIT - 1; index >= 0; index--)
			{
				R.High[index] = baseBinAdd(this->High[index], false, C, C);
			}
		}
	}
	else if (!B.HighisZero)
	{
		R.HighisZero = false;
		for (int index = MAXDIGIT - 1; index >= 0; index--)
		{
			R.High[index] = baseBinAdd(false, B.High[index], C, C);
		}
	}
	//if (this->sign == B.sign && C){
	//		throw std::overflow_error("over flow on A+B");
	//}
	R.sign = baseBinAdd(this->sign, B.sign, C, C);
	return R;
}
BinNum BinNum::Complement()
{
	if (this->sign == false)
	{
		BinNum R = BinNum(*this);
		return R;
	}
	else
	{
		BinNum R = BinNum(NULL, MAXDIGIT, true);
		bool C = true;
		for (int index = MAXDIGIT - 1; index >= 0; index--)
		{
			R.Low[index] = baseBinAdd(!this->Low[index], false, C, C);
		}
		if (!this->HighisZero)
		{
			R.HighisZero = false;
			for (int index = MAXDIGIT - 1; index >= 0; index--)
			{
				R.High[index] = baseBinAdd(!this->High[index], false, C, C);
			}
		}
		R.sign = this->sign;
		return R;
	}
}
BinNum BinNum::operator-(BinNum &B)
{
	if (B.isZero()){ return *this; }
	BinNum Result = BinNum();
	BinNum A = BinNum(*this);
	if (A.sign && !B.HighisZero)
	{
		A = A.Complement();
		A.HighisZero = false;
		A = A.Complement();
	}
	if (B.sign == false)
	{
		BinNum CB = BinNum(B);
		if (!this->HighisZero || !B.HighisZero)
		{
			CB.HighisZero = false; 
		}
		CB.sign = true;
		CB = CB.Complement();
		Result = A + CB;
		Result.HighisZero = Result.TestHighisZero();
	}
	else
	{
		BinNum CB = BinNum(B);
		if (!this->HighisZero || !B.HighisZero){ 
			CB.HighisZero = false;
		}
		CB = CB.Complement();
		CB.sign = false;
		Result = A + CB;
		Result.HighisZero = Result.TestHighisZero();
	}
	return Result;
}
BinNum BinNum::operator<<(int shift)
{
	BinNum R = BinNum();
	int index = 0;
	memmove_s(R.Low, MAXDIGIT, this->Low + shift, MAXDIGIT - shift);
	if (!this->HighisZero)
	{
		memmove_s(R.High, MAXDIGIT, this->High + shift, MAXDIGIT - shift);
	}
	memmove(R.High + MAXDIGIT - shift, this->Low, shift);
	R.HighisZero = R.TestHighisZero();
	return R;
}
BinNum BinNum::operator>>(int shift)
{
	BinNum R = BinNum(NULL, MAXDIGIT, this->sign);
	R.HighisZero = this->HighisZero;
	memmove_s(R.Low + shift, MAXDIGIT, this->Low, MAXDIGIT - shift);
	if (!this->HighisZero)
	{
		memmove_s(R.High + shift, MAXDIGIT, this->High, MAXDIGIT - shift);
		for (int Lindex = 0, Hindex = MAXDIGIT - shift; Lindex < shift; Lindex++, Hindex++)
		{
			R.Low[Lindex] = this->High[Hindex];
		}
	}
	return R;
}
bool BinNum::operator==(BinNum &B)
{
	if (this->sign != B.sign){ return false; }
	int thisindex = 0,Bindex = 0;
	while (thisindex < MAXDIGIT)
	{
		if (this->Low[thisindex] != B.Low[Bindex])return false;
		thisindex++; Bindex++;
	}
	return true;
}
BinNum BinNum::operator*(BinNum &B)
{
	BinNum Result = BinNum(NULL, MAXDIGIT);
	Result.HighisZero = false;
	BinNum RA = BinNum(*this); 
	if (RA.sign){
		RA = RA.Complement();
		RA.HighisZero = false;
		RA = RA.Complement();
	}
	else{ RA.HighisZero = false; }
	BinNum RB = BinNum(B); 
	if (RB.sign){
		RB = RB.Complement();
		RB.HighisZero = false;
		RB = RB.Complement();
	}
	else{ RB.HighisZero = false; }
	while (!RB.isZero())
	{
		if (RB.Low[MAXDIGIT - 1] == true)
		{
			Result = Result + RA;
		}
		RA = RA << 1;
		RB = RB >> 1;
	}
	if (Result.TestHighisZero()){ Result.HighisZero = true; }
	bool _;
	Result.sign = baseBinAdd(this->sign, B.sign, false, _);
	return Result;
}
BinNum BinNum::operator/(BinNum &B)
{
	BinNum Result = BinNum(NULL, MAXDIGIT, false);
	if (this->isZero()){ return Result; }
	if (B.isZero()){ return Result; }
	if (BinCmp(*this, B) == -1)
	{
		return Result;
	}
	BinNum x = BinNum(B);
	BinNum y = BinNum(NULL, MAXDIGIT, false);
	y.Low[MAXDIGIT - 1] = true;
	while (BinCmp(*this, x << 1) != -1 && BinCmp(x,x<<1)!=1)
	{
		x = x << 1;
		y = y << 1;
	}
	Result = (*this - x) / B + y;
	return Result;
}
BinNum BinNum::operator%(BinNum &B)
{
	BinNum Result = BinNum();
	if (this->isZero()){ return Result; }
	if (B.isZero()){ return *this; }
	if (BinCmp(*this, B) == -1)
	{
		return *this;
	}
	BinNum x = BinNum(B);
	while (BinCmp(*this, x << 1) != -1 && BinCmp(x,x<<1)!=1)
	{

		x = x << 1;
	}
	return (*this - x) % B;
}

BinNum ExGCD(BinNum A, BinNum B, BinNum &x, BinNum &y)
{
	if (B.isZero())
	{
		memset(x.Low, false, MAXDIGIT);
		x.Low[MAXDIGIT - 1] = true;
		memset(y.Low, false, MAXDIGIT);
		return A;
	}
	else
	{
		BinNum r = ExGCD(B, A%B, x, y);
		BinNum t = BinNum(x);
		x = BinNum(y);
		y = t - (A / B) * y;
		return r;
	}
}
BinNum ModMutli(BinNum &A, BinNum &B, BinNum &n)
{
	//return (a*b) % n
	BinNum x = BinNum(), y = A % n,CopyB = BinNum(B);
	x.HighisZero = false;
	y.HighisZero = false;
	while (!CopyB.isZero())
	{
		x.HighisZero = false;
		y.HighisZero = false;
		BinNum xpy = x + y;
		if (CopyB.Low[MAXDIGIT - 1] == true)
		{
			x = (x  + y)%n;
		}
		y = (y << 1) % n;
		CopyB = CopyB >> 1;
	}
	x = x % n;
	x.HighisZero = x.TestHighisZero();
	return x;
}
BinNum ModNsquare(BinNum &A, BinNum &B, BinNum &n)
{
	BinNum result = BinNum(NULL, MAXDIGIT);
	result.Low[MAXDIGIT - 1] = true;
	BinNum base = BinNum(A);
	BinNum copyB = BinNum(B);
	while (!copyB.isZero())
	{
		//std::cout << " base : " << base.sign << " " << convert(base) << std::endl <<
		//	" result : " << result.sign << " " << convert(result) << std::endl <<
		//	" copyB : " << copyB.sign << " " << convert(copyB) << std::endl <<
		//	" A : " << A.sign << " " << convert(A) << std::endl <<
		//	" B : " << B.sign << " " << convert(B) << std::endl << 
		//	" N : " << n.sign << " " << convert(n) << std::endl << "RN" << std::endl;;
		if (copyB.Low[MAXDIGIT - 1])
		{
			result = ModMutli(result,base,n);
		}
		base = ModMutli(base, base, n);
		copyB = copyB >> 1;
		//std::cout << " base : " << base.sign << " " << convert(base) << std::endl <<
		//	" result : " << result.sign << " " << convert(result) << std::endl <<
		//	" copyB : " << copyB.sign << " " << convert(copyB) << std::endl <<
		//	" A : " << A.sign << " " << convert(A) << std::endl <<
		//	" B : " << B.sign << " " << convert(B) << std::endl << 
		//	" N : " << n.sign << " " << convert(n) << std::endl << "HA" << std::endl << std::endl;
	}
	return result;
}
bool randbool()
{
	static bool firstcall = false;
	if (!firstcall){ srand((unsigned int)time(NULL)); firstcall = true; }
	return rand() < (RAND_MAX >> 1);

}
BinNum randChoice(BinNum & refren)
{
	BinNum result = BinNum(NULL, MAXDIGIT);
	int first1 = 0;
	while (first1 < MAXDIGIT){ if (refren.Low[first1])break; first1++; }
	int index = first1,createfirst1 = -1;
	int tindex = index;
	bool testfirst = true;
	while (tindex < MAXDIGIT)
	{
		bool t = randbool();
		result.Low[tindex] = t;
		if (t && testfirst) { createfirst1 = tindex; testfirst = false; }
		if (!testfirst)
		{
			if (first1 < createfirst1){ tindex++; continue; }
			else if (first1 == createfirst1)
			{
				testfirst = true;
				first1++;
				while (first1 < MAXDIGIT){ if (refren.Low[first1])break; first1++; }
			}
			else if (first1 > createfirst1)
			{
				result.Low[tindex] = false;
				testfirst = true;
			}
		}
		tindex++;
	}
	return result;
}
//Miller�CRabin primality test
bool isPrime(BinNum TestNum)
{
	BinNum One = BinNum(NULL, 1);
	One.Low[MAXDIGIT - 1] = true;
	BinNum copyTestNum = BinNum(TestNum);
	copyTestNum.Low[MAXDIGIT - 1] = false;
	int index = MAXDIGIT - 1,s = 0;
	while (index >= 0){ if (copyTestNum.Low[index]){ break; }s++; index--; }
	//n - 1 = 2**s * d
	BinNum d = copyTestNum >> s;
	
	for (int times = 0; times < TIMES; times++)
	{
		//choice a num A between 1 to n - 1
		BinNum A = randChoice(copyTestNum);
		while (A.isZero())
		{
			A = randChoice(copyTestNum);
		}
		//for all num R between 0 to s - 1
		BinNum x = ModNsquare(A, d, TestNum);
		if (x == One || x == copyTestNum)continue;
		bool flag = false;
		for (int r = 1; r < s; r++)
		{
			x = ModMutli(x, x, TestNum);
			if (x == One)
			{
				return false;
			}
			if (x == copyTestNum)
			{
				flag = true;
				break;
			}
			// if a ** d mod n != 1 and a ** (2**r * d) mod N != N-1 retuen false;
		}
		if (!flag)return false;
	}
	return true;
}
