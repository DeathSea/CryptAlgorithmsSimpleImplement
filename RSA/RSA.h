#include <string>
#include <iostream>
#include "BinCalc.h"
#ifndef RSA
#define RSA
void outputboolarray(bool *N, int length);
void outputB(BinNum &A);
void createprime();
void calcKey();
BinNum Encrypt(bool * M, int length);
BinNum Decrypt(BinNum c);
#endif