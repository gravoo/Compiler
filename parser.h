#ifndef PARSER_H
#define PARSER_H
#include<stdio.h>
#include "aritmetic.h"
#include<string.h>
#include<math.h>
#include "AST.h"
#include "counter.h"
void _reset();
void _halt();
void _load(int adres);
void _put(ast_node *v,int adres);
void _assign(symbol_node *v,ast_node *v2,int adres);
void _get(symbol_node *v);
/******************************************************/
char* _addStale(char* ptr,char* ptr2);
void _addZmienneGet(int adres1,int adres2);
void _addStala_Zmienna(char *value,int adres,int ad);
/******************************************************/
char* _subStale(char* ptr,char* ptr2);
void _subZmienneGet(int adres1,int adres2);
void _subStala_Zmienna(char *value,int adres,int ad);
/******************************************************/
char* _timesStale(char* ptr,char* ptr2);
void _timesZmienneGet(int adres1,int adres2,int adresTMP);
void _timesStala_Zmienna(char *value,int adres,int ad);
/******************************************************/
char* _divStale(char* ptr,char* ptr2);
void _divStala_Zmienna(char *value,int adres,int ad);
void _fastDiv(int adres1,int adres2,int adresTMP);
/******************************************************/
char* _modStale(char* ptr,char* ptr2);
void _modStala_Zmienna(char *value,int adres,int ad);
void _fastMod(int adres1,int adres2,int adresTMP);
/******************************************************/
void _store(int adres);
void _EQ(int adres1,int adres2);/*jesli zmienne sa takie same w akm jest 1, w przeciwnym przypadku 0*/
void _NEQ(int adres1,int adres2);
void _GE(int adres1,int adres2);
void _LE(int adres1,int adres2);
void _GEQ(int adres1,int adres2);
void _LEQ(int adres1,int adres2);
void _IF(struct ast_if_node *v,int adres);
void _inicializeVariable(struct symbol_node *v);
void _WHILE(struct ast_while_node *v,int adres);
/******************************************************/
int checkTwo(char *ptr,int ln);
void preorder(ast_node *v,int adres);
void _OPERATE(struct ast_equality_node *operate,int adres);
#endif
