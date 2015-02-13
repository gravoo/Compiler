%option noyywrap
%option yylineno
%{
#include "kompilator.tab.h"
#include "AST.h"
#include <stdio.h>
#include <math.h>
int yylex();
%}
 
%x comment

%%

<INITIAL>"(*"			BEGIN(comment);
<comment>.				;
<comment>"*)"			BEGIN(INITIAL);
[ \t\n]					;

[_a-z]*	 				{ 	yylval.symbol = new_symbol_node(yytext);
						return identifier;
						}
[0-9]+					{	yylval.number = strdup(yytext);
							return num;
						}

"DECLARE"				{return DECLARE;}
"END"					{return END;}
"IN"					{return IN;}
"PLUS"					{return PLUS;}
"MINUS"					{return MINUS;}
"TIMES"					{return TIMES;}
"DIV"					{return DIV;}
"MOD"					{return MOD;}
"EQ"					{return EQ;}
"DIFF"					{return DIFF;}
"LE"					{return LE;}
"GE"					{return GE;}
"LEQ"					{return LEQ;}
"GEQ"					{return GEQ;}
"PUT"					{return PUT;}
"GET"					{return GET;}
"ASSIGN"				{return ASSIGN;}
"IF"					{return IF;}
"THEN"					{return THEN;}
"ELSE"					{return ELSE;}
"ENDIF"					{return ENDIF;}
"WHILE"					{return WHILE;}
"DO"					{return DO;}
"ENDWHILE"				{return ENDWHILE;}
";"					{return ';';}
.					{return ERROR;}












%%
