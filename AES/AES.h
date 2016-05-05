#ifndef AESHEAD

#define AESHEAD
#include <string.h>
#include <iostream>
#include <iomanip>

#define STATEROW 4
void outputSTATE();
void SetKeyLength(int length);
void EncdeAES(char * Source,char * key,char * result);
void DecdeAES(char * S, char *K,char * result);
void AES_256_CFB_encrypt(char * s, char * k, char * res, char * IV);
void AES_256_CFB_decrypt(char * s, char * k, char * res, char * IV);
void AES_256_CBC_encrypt(char * s, char * k, char * res, char * IV);
void AES_256_CBC_decrypt(char * s, char * k, char * res, char * IV);
void AES_256_OFB_encrypt(char * s, char * k, char * res, char * IV);
void AES_256_OFB_decrypt(char * s, char * k, char * res, char * IV);
#endif