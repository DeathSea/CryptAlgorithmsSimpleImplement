#include <string>
template < typename Type > 
inline Type max(Type A, Type B){ return A > B ? A : B; };
template <typename Type>
inline Type min(Type A, Type B){ return A > B ? B : A; };
int ExGCD(int a, int b, int * x, int * y);
bool baseBinAdd(bool Ai, bool Bi, bool Ci, bool &Cip1);
//��λ��� ciǰһ��λ��cipi���ؼ����λ��Bi��������Ai���������ؽ��
bool BinAdd(bool * A, int Adigit, bool * B, int Bdigit, bool * result, int Rdigit);
//�����Ƽӷ���result=A+B��Adigit A��λ�� Bdigit��Rdigitͬ�����ؼ����λ��Ϊ1���
void BinComplement(bool *N, int Adigit);
//����
bool BinMinus(bool * A, int Adigit, bool * B, int Bdigit, bool * result, int Rdigit, bool &hnc);
//���ؼ���ķ���λ��result = A - B��hnc����λ��Ӻ�Ľ�λ
int BinCmp(bool *A, int Adigit, bool *B, int Bdigit);
//�Ƚ����������� A>B����1 A<B����-1 A=B����0
void BinLeftShift(bool * A, int Adigit, int Shift, bool * Result, int Rdigit);
//����
bool BinMul(bool * A, int Adigit, bool * B, int Bdigit, bool * Result, int Rdigit);
bool BinDivMod(bool *A, int Adigit, bool *B, int Bdigit,
	bool * DivResult, int Ddigit,
	bool * ModResult, int Mdigit);
