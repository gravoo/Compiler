#ifndef COUNTER_H
#define COUNTER_H
#include<stdio.h>
#include "aritmetic.h"
#include<string.h>
#include<math.h>
#include "AST.h"
#include "parser.h"
/******************funkcje liczace*********************/
void  Countreset();
void  Counthalt();
void  Countload(int adres);
void  Countput(ast_node *v,int adres);
void  Countassign(symbol_node *v,ast_node *v2,int adres);
void  Countget(symbol_node *v);
/******************************************************/
char*  CountaddStale(char* ptr,char* ptr2);
void  CountaddZmienneGet(int adres1,int adres2);
void  CountaddStala_Zmienna(char *value,int adres,int ad);
/******************************************************/
char*  CountsubStale(char* ptr,char* ptr2);
void  CountsubZmienneGet(int adres1,int adres2);
void  CountsubStala_Zmienna(char *value,int adres,int ad);
/******************************************************/
char*  CounttimesStale(char* ptr,char* ptr2);
void  CounttimesZmienneGet(int adres1,int adres2,int adresTMP);
void  CounttimesStala_Zmienna(char *value,int adres,int ad);
/******************************************************/
char*  CountdivStale(char* ptr,char* ptr2);
void  CountdivStala_Zmienna(char *value,int adres,int ad);
void CountfastDiv(int adres1,int adres2,int adresTMP);
/******************************************************/
char*  CountmodStale(char* ptr,char* ptr2);
void  CountmodStala_Zmienna(char *value,int adres,int ad);
void CountfastMod(int adres1,int adres2,int adresTMP);
/******************************************************/
void  Countstore(int adres);
void  CountEQ(int adres1,int adres2);/*jesli zmienne sa takie same w akm jest 1, w przeciwnym przypadku 0*/
void  CountNEQ(int adres1,int adres2);
void  CountIF(struct ast_if_node *v,int adres);
void  CountinicializeVariable(int adres);
void  CountLEQ(int adres1,int adres2);
void  CountWHILE(struct ast_while_node *v,int adres);
void  CountGEQ(int adres1,int adres2);
void  CountLE(int adres1,int adres2);
void  CountGE(int adres1,int adres2);
void  CountOPERATE(struct ast_equality_node *operate,int adres);
void count(ast_node *v,int adres);

#endif
