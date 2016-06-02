#include "RSA.h"
#include "BinPrime4096.h"
#include <time.inl>
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

int ExGCD(int a, int b, int * x, int *y)
{
	if (b == 0)
	{
		*x = 1;
		*y = 0;
		return a;
	}
	else
	{
		int r = ExGCD(b, a%b, x, y);
		int t = *x;
		*x = *y;
		*y = t - (a / b) * *y;
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
int randint(int start, int end)
{
	static bool first = false;
	if (!first){ 
		srand((unsigned int)time(NULL));
		first = true;
	}
	int thisint = rand() % (end - start + 1) + start;
	return thisint;
}
void outputboolarray(bool *N, int length)
{
	int index = 0;
	while (index < length)
	{
		if (N[index]){ std::cout << "1"; }
		else{ std::cout << "0"; }
		index++;
		if (index % 4 == 0){ std::cout << " "; }
	}
}
void outputB(BinNum &A)
{
	if (!A.HighisZero){ 
		outputboolarray(A.High, MAXDIGIT); 
		std::cout << " "; 
	}
	outputboolarray(A.Low, MAXDIGIT); 
	std::cout << std::endl;
}
extern BinNum p = BinNum();
extern BinNum q = BinNum();
bool one[1] = { true };
extern BinNum publicKeyN = BinNum();
extern BinNum publicKeyE = BinNum();
extern BinNum privateKeyD = BinNum();
extern BinNum One = BinNum(one, 1);

void createprime()
{
	p.Low[MAXDIGIT - 1] = true;
	p.Low[0] = true;
	q.Low[MAXDIGIT - 1] = true;
	q.Low[0] = true;
	int changebit, times, bit;
	while (1)
	{
		changebit = randint(1, MAXDIGIT - 2);
		for (times = 0; times < changebit; times++)
		{
			bit = randint(1, MAXDIGIT - 2);
			if (!p.Low[bit]){ p.Low[bit] = true; }
			else{ times--; }
		}
		if (isPrime(p))break;
		else
		{
			memset(p.Low, false, MAXDIGIT);
			p.Low[MAXDIGIT - 1] = true;
			p.Low[0] = true;
		}
	}
	while (1)
	{
		changebit = randint(1, MAXDIGIT - 2);
		for (times = 0; times < changebit; times++)
		{
			bit = randint(1, MAXDIGIT - 2);
			if (!q.Low[bit]){ q.Low[bit] = true; }
			else{ times--; }
		}
		if (isPrime(q))break;
		else
		{
			memset(q.Low, false, MAXDIGIT);
			q.Low[MAXDIGIT - 1] = true;
			q.Low[0] = true;
		}
	}
	////p = 0b1011 1001 1110 1111
	//bool * Q = new bool[16]{
	//true,false,true,true ,
	//	true,false,false,true,
	//	true,true,true,false,
	//	true,true,true,true
	//};
	////q = 0b1111 1111 1110 1111
	//bool * P = new bool[16]{
	//true,true,true,true,
	//	true,true,true,true,
	//	true,true,true,false,
	//	true,true,true,true
	//};
	//q = BinNum(Q, 16);
	//p = BinNum(P, 16);
	std::cout << "the prime num p is: " << std::endl;
	outputB(p);
	std::cout << "the prime num q is: " << std::endl;
	outputB(q);
}
void calcKey()
{
	publicKeyN = p * q;
	BinNum omegaN = (p - One)*(q - One);
	BinNum Tmp = BinNum();
	BinNum x = BinNum();
	BinNum y = BinNum();
	for (int Pindex = 0; Pindex < 564;Pindex++)
	{
		Tmp = BinNum(allBinPrime[Pindex],12);
		BinNum result = ExGCD(Tmp, omegaN, x, y);
		if (result == One)
		{
			publicKeyE = BinNum(Tmp);
			while (x.sign == true){ x = x + omegaN; }
			privateKeyD = BinNum(x);
			break;
		}
	}
	std::cout << "the private key D is: " << std::endl;
	outputB(privateKeyD);
	std::cout << "the public key E is: " << std::endl;
	outputB(publicKeyE);
	std::cout << "the public key N is: " << std::endl;
	outputB(publicKeyN);
	std::cout << "the omega N is: " << std::endl;
	outputB(omegaN);
}
BinNum Encrypt(bool * M,int length)
{
	BinNum m = BinNum(M, length);
	return ModNsquare(m, publicKeyE, publicKeyN);
}
BinNum Decrypt(BinNum c)
{
	return ModNsquare(c, privateKeyD, publicKeyN);
}