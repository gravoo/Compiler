#ifndef ARITMETIC_H
#define ARITMETIC_H
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <gmp.h>

void _Assign(char *tab,int adres,int adresTMP);
char* toBit(char *tab);
void CountAssign(char *tab,int adres,int adresTMP);
/*************************************************/
char* operationConst(char *ptr,char *ptr2,int operationTYPE);/*1->DODAJ 2->ODEJMIJ 3->POMNOZ 4->PODZIEL 5 ->MOD*/
/*************************************************/
void loga2(mpz_t rop,const mpz_t val1);
int compareNumbers(char *ptr1,char *ptr2);
#endif
