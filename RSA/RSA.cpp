#include "RSA.h"
int prime[305] = {
	2, 3, 5, 7, 11,
	13, 17, 19, 23, 29,
	31, 37, 41, 43, 47,
	53, 59, 61, 67, 71,
	73, 79, 83, 89, 97,
	101, 103, 107, 109, 113,
	127, 131, 137, 139, 149,
	151, 157, 163, 167, 173,
	179, 181, 191, 193, 197,
	199, 211, 223, 227, 229,
	233, 239, 241, 251, 257,
	263, 269, 271, 277, 281,
	283, 293, 307, 311, 313,
	317, 331, 337, 347, 349,
	353, 359, 367, 373, 379,
	383, 389, 397, 401, 409,
	419, 421, 431, 433, 439,
	443, 449, 457, 461, 463,
	467, 479, 487, 491, 499,
	503, 509, 521, 523, 541,
	547, 557, 563, 569, 571,
	577, 587, 593, 599, 601,
	607, 613, 617, 619, 631,
	641, 643, 647, 653, 659,
	661, 673, 677, 683, 691,
	701, 709, 719, 727, 733,
	739, 743, 751, 757, 761,
	769, 773, 787, 797, 809,
	811, 821, 823, 827, 829,
	839, 853, 857, 859, 863,
	877, 881, 883, 887, 907,
	911, 919, 929, 937, 941,
	947, 953, 967, 971, 977,
	983, 991, 997, 1009, 1013,
	1019, 1021, 1031, 1033, 1039,
	1049, 1051, 1061, 1063, 1069,
	1087, 1091, 1093, 1097, 1103,
	1109, 1117, 1123, 1129, 1151,
	1153, 1163, 1171, 1181, 1187,
	1193, 1201, 1213, 1217, 1223,
	1229, 1231, 1237, 1249, 1259,
	1277, 1279, 1283, 1289, 1291,
	1297, 1301, 1303, 1307, 1319,
	1321, 1327, 1361, 1367, 1373,
	1381, 1399, 1409, 1423, 1427,
	1429, 1433, 1439, 1447, 1451,
	1453, 1459, 1471, 1481, 1483,
	1487, 1489, 1493, 1499, 1511,
	1523, 1531, 1543, 1549, 1553,
	1559, 1567, 1571, 1579, 1583,
	1597, 1601, 1607, 1609, 1613,
	1619, 1621, 1627, 1637, 1657,
	1663, 1667, 1669, 1693, 1697,
	1699, 1709, 1721, 1723, 1733,
	1741, 1747, 1753, 1759, 1777,
	1783, 1787, 1789, 1801, 1811,
	1823, 1831, 1847, 1861, 1867,
	1871, 1873, 1877, 1879, 1889,
	1901, 1907, 1913, 1931, 1933,
	1949, 1951, 1973, 1979, 1987,
	1993, 1997, 1999, 2003, 2011
};
bool q[256], p[256];
bool baseBinAdd(bool Ai, bool Bi, bool Ci, bool &Cip1)
{
	bool S = Ai ^ Bi ^ Ci;
	Cip1 = (Ai & Bi) | (Bi & Ci) | (Ci & Ai);
	return S;
}
bool BinAdd(bool * A, int Adigit, bool * B, int Bdigit, bool * result, int Rdigit)
{
	//if (Rdigit != max<int>(Adigit, Bdigit)){ return true; }
	int maxLength = max<int>(Adigit, Bdigit);
	int minLength = min<int>(Adigit, Bdigit);
	bool *LongestOne, *ShortestOne;
	if (maxLength == Adigit){ LongestOne = A; ShortestOne = B; }
	else{ LongestOne = B; ShortestOne = A; }
	bool c = false;
	int lIndex = maxLength - 1;
	int RIndex = Rdigit - 1;
	for (int index = minLength - 1; index >= 0; index--,RIndex--,lIndex--)
	{
		result[RIndex] = baseBinAdd(ShortestOne[index], LongestOne[lIndex], c, c);
	}
	while (RIndex >= 0)
	{
		result[RIndex] = baseBinAdd(LongestOne[lIndex], 0, c, c);
		lIndex--; RIndex--;
	}
	return c;
}
void BinComplement(bool *N,int Adigit)
{
	int index = Adigit - 1;
	while (index >= 0)
	{
		N[index] = !N[index];
		index--;
	}
	bool One[1] = { true };
	BinAdd(N, Adigit, One, 1, N, Adigit);
}
bool BinMinus(bool * A, int Adigit, bool * B, int Bdigit, bool * result, int Rdigit,bool &hnc)
{
	int MaxLength = max<int>(Adigit, Bdigit);
	int MinLength = min<int>(Adigit, Bdigit);
	bool * ShortOne = MinLength == Bdigit ? B : A;
	bool * LongestOne = MaxLength == Adigit ? A : B;
	bool * Tmp = (bool *)malloc(sizeof(bool)*MaxLength);
	memset(Tmp, false, MaxLength);
	int sIndex = MinLength - 1;
	int cIndex = MaxLength - 1;
	while (sIndex >= 0)
	{
		Tmp[cIndex--] = ShortOne[sIndex--];
	}
	bool sign;
	if (MaxLength == Adigit)
	{
		BinComplement(Tmp, MaxLength);
		bool c = BinAdd(A, Adigit, Tmp, MaxLength, result, Rdigit);
		sign = baseBinAdd(false, true, c, hnc);
		free(Tmp);
		return sign;
	}
	else
	{
		bool * D = (bool *)malloc(sizeof(bool)*MaxLength);
		memcpy_s(D, MaxLength, B, MaxLength);
		BinComplement(D, Bdigit);
		bool c = BinAdd(Tmp, MaxLength, D, Bdigit, result, Rdigit);
		sign = baseBinAdd(false, true, c, hnc);
		free(D);
		free(Tmp);
		return sign;
	}

}
int BinCmp(bool *A, int Adigit, bool *B, int Bdigit)
{
	//wrong
	int Afirst1 = 0,Bfirst1 = 0;
	int Aindex = 0, Bindex = 0;
	bool tmp = false;
	for (; Aindex < Adigit; Aindex++)
	{
		tmp |= A[Aindex];
	}
	if (!tmp)return -1;
	tmp = false;
	for (; Bindex < Bdigit; Bindex++)
	{
		tmp |= B[Bindex];
	}
	if (!tmp)return 1;
	for (Aindex = Afirst1; Aindex < Adigit; Aindex++)
	{
		if (A[Aindex] == true){ Afirst1 = Aindex; break; }
	}
	for (Bindex = Bfirst1; Bindex < Bdigit; Bindex++)
	{
		if (B[Bindex] == true){ Bfirst1 = Bindex; break; }
	}

	if ((Adigit - Afirst1) < (Bdigit - Bfirst1)) return -1;
	else if ((Adigit - Afirst1) > (Bdigit - Bfirst1))return 1;
	else if ((Afirst1 == Adigit - 1) && (Bfirst1 == Bdigit - 1))return 0;

	for (Bindex = Bfirst1; Bindex < Bdigit; Bindex++,Afirst1++)
	{
		if (B[Bindex] && !A[Afirst1])return -1;
		else if (!B[Bindex] && A[Afirst1])return 1;
	}
	return 0;
}
void BinLeftShift(bool * A,int Adigit,int Shift,bool * Result,int Rdigit)
{
	if (Rdigit < Adigit){ return; }
	int index = Adigit - 1,j;
	memset(Result, false, Rdigit);
	for (j = Rdigit - Shift - 1;j >= 0 && j > Rdigit - Shift - Adigit - 1; j--,index --)
	{
		Result[j] = A[index];
	}
}
bool BinMul(bool * A, int Adigit, bool * B, int Bdigit, bool * Result, int Rdigit)
{
	if (Rdigit < Adigit + Bdigit - 1)return true;
	bool * Tmp = (bool *)malloc(sizeof(bool)*Rdigit);
	bool * TT = (bool *)malloc(sizeof(bool)*Rdigit);
	memset(Result, false, Rdigit);
	memset(Tmp, false, Rdigit);
	int Bindex = Bdigit - 1,Tindex = Rdigit - 1,Aindex = Adigit - 1;
	for (; Aindex >= 0; )
	{
		Tmp[Tindex--] = A[Aindex--];
	}
	bool C;
	while (Bindex >= 0)
	{
		if (B[Bindex--] == true)
		{
			C = BinAdd(Tmp, Rdigit, Result, Rdigit, Result, Rdigit);
		}
		BinLeftShift(Tmp, Rdigit, 1, TT, Rdigit);
		memcpy_s(Tmp,Rdigit,TT,Rdigit);
	}
	free(Tmp); free(TT);
	return C;
}
//http://www.cnblogs.com/AndyJee/p/4575152.html
bool BinDivMod(bool *A, int Adigit, bool *B, int Bdigit, 
	bool * DivResult, int Ddigit,
	bool * ModResult,int Mdigit)
{
	if (BinCmp(A, Adigit, B, Bdigit) == -1)
	{
		memset(DivResult, false, Ddigit);
		int offset = Adigit - Mdigit > 0?Adigit - Mdigit:0;
		memmove_s(ModResult,Mdigit,A+offset,Mdigit);
		return false;
	}
	bool *x = (bool *)malloc(sizeof(bool)*(Adigit + 1));
	memset(x, false, Adigit + 1);
	memmove_s(x + (Adigit + 1 - Bdigit),Adigit + 1,B,Bdigit);
	bool *lsx = (bool *)malloc(sizeof(bool)*(Adigit + 1));
	bool *y = (bool *)malloc(sizeof(bool)*(Adigit + 1));
	memset(y, false, Adigit + 1);
	y[Adigit] = true;
	BinLeftShift(x, Adigit + 1, 1, lsx, Adigit + 1);
	while (BinCmp(A, Adigit, lsx, Adigit + 1) != -1)
	{
		memcpy_s(x, Adigit + 1, lsx, Adigit + 1);
		//BinLeftShift(x, Adigit + 1, 1, lsx, Adigit + 1);
		BinLeftShift(y, Adigit + 1, 1, lsx, Adigit + 1);
		memcpy_s(y, Adigit + 1, lsx, Adigit + 1);
		BinLeftShift(x, Adigit + 1, 1, lsx, Adigit + 1);
	}
	bool hnc;
	BinMinus(A, Adigit, x, Adigit + 1, lsx, Adigit + 1, hnc);
	BinDivMod(lsx, Adigit + 1, B, Bdigit, DivResult, Ddigit, ModResult, Mdigit);
	return BinAdd(DivResult,Ddigit,y,Adigit+1,DivResult,Ddigit);
}

int ExGCD(int a, int b, int * x, int *y)
{
	if (b == 0)
	{
		return a;
	}
	else
	{
		int r = ExGCD(b, a%b, x, y);
		int t = *x;
		*x = *y;
		*y = (t - a / b) * *y;
		return r;
	}
}
int mod(int a, int b, int n)
{
	//return pow(a,b) % n
	int result = 1;
	int base = a;
	while (b > 0)
	{
		if (b & 1){ result = (result * base) % n; }
		base = (base * base) % n;
		b >>= 1;
	}
	return result;
}