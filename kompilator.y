%{

#include<stdio.h>
extern int yylineno;  // z lex-a//
#include<string.h>
#include<stdlib.h>
#include <math.h>
#include "parser.h"
#include "tablica_symboli.h"
#include "AST.h"
int nawiasy=0;
unsigned int adres=0;
unsigned long long counter=0;
unsigned int jedynka;
int last_command=0;
symrec *sym_table;
symbol_node *s;
symbol_node *s2;
symrec *s1;
ast_node *root;
symbol_node *sym_table2;
%}
%union 
{
	char * text;
	char * number;
	int val;
	struct ast_node *ast;
	 struct symbol_node * symbol;
	int operator;
}



%token<text> DECLARE IN END ERROR GET 
%token<text> PUT ASSIGN IF ENDIF WHILE ENDWHILE DO
%token<text> PLUS MINUS DIV TIMES
%token<symbol> identifier 
%token<number> num 
%type <ast> command commands vdeclarations  expression  value program condition

%left<operator> EQ DIFF LE GE LEQ GEQ
%left PLUS MINUS 
%left DIV TIMES MOD 
%left IF THEN DO ELSE WHILE  
%left ENDIF ENDWHILE 
%nonassoc ';'
%start pr
%%
pr:
program		{root=$1;}
;
program:
    | DECLARE vdeclarations IN commands END {$$ = new_ast_node ('R', $2, $4);        }	
	| error 	{yyerror("error","blad w skladni w linii",yylineno-1); return 1;}
	;
vdeclarations:  
	vdeclarations identifier	{s=find_symbol($2);
					 	if(!(s==NULL)){	
					 			yyerror("error","zmienna juz istnieje linii",yylineno-1);
					 			 YYERROR;}
					s = allocate_symbol ($2,adres);
					$$ = new_ast_node ('D', $1, s);
					*((symbol_node**) &yylval) = s;
					adres++;
					
					}
	|				{ $$ =NULL;}
	;
commands:
	commands command		{ $$ = new_ast_node ('L',$1 ,$2);}
	|				{ $$ = NULL;}
	;

command:
	identifier ASSIGN expression ';'		{ s=find_symbol($1);
							 if(checkDeclared(s)) YYERROR;
							 ;if(checkInicialized($3->left,$3->right)) YYERROR;
							 if(inicjalize($3));
							 	s->type=1;
							 $$ = new_ast_assignment_node (s, $3);
							}
	| IF condition THEN commands  ENDIF			{$$ = new_ast_if_node ($2, $4, NULL);}
	| IF condition THEN commands ELSE commands ENDIF 	{$$ = new_ast_if_node ($2, $4, $6);}
	| WHILE condition DO commands ENDWHILE		{$$ = new_ast_while_node ($2, $4);}
	| GET identifier ';'				{{	s=find_symbol($2);
							if(checkDeclared(s)) YYERROR;
							s->type=1;
							$$ = new_ast_node ('G',s, NULL);
							}}			
	| PUT value ';'					{$$ = new_ast_node ('P',NULL, $2);	if(checkInicialized($2,$2)) YYERROR;}
	;

expression:
	value				{$$ = new_ast_node ('V',$1, $1);					
					 }
	| value PLUS value		{$$ = new_ast_node ('+',$1, $3);if(checkInicialized($1,$3)) YYERROR;}
	| value MINUS value		{$$ = new_ast_node ('-',$1, $3);if(checkInicialized($1,$3)) YYERROR;}
	| value TIMES value		{$$ = new_ast_node ('*',$1, $3);if(checkInicialized($1,$3)) YYERROR;}
	| value DIV value		{$$ = new_ast_node ('/',$1, $3);if(checkInicialized($1,$3)) YYERROR;}
	| value MOD value		{$$ = new_ast_node ('%',$1, $3);if(checkInicialized($1,$3)) YYERROR;}
	;
condition:
	 value EQ value			{$$ = new_ast_equality_node ('=', $1, $3);if(checkInicialized($1,$3)) YYERROR;}
	| value DIFF value		{$$ = new_ast_equality_node ('!', $1, $3);if(checkInicialized($1,$3)) YYERROR;}
	| value LE value		{$$ = new_ast_relational_node ('l', $1, $3);if(checkInicialized($1,$3)) YYERROR;}
	| value GE value		{$$ = new_ast_relational_node ('g', $1, $3);if(checkInicialized($1,$3)) YYERROR;}
	| value LEQ value		{$$ = new_ast_relational_node ('L', $1, $3);if(checkInicialized($1,$3)) YYERROR;}
	| value GEQ value		{$$ = new_ast_relational_node ('G', $1, $3);if(checkInicialized($1,$3)) YYERROR;}
value:		
	num		{			$$ = new_ast_number_node($1);}			
	| identifier 	{			s=find_symbol($1);
						if(checkDeclared(s)) YYERROR;
						$$ = new_ast_symbol_reference_node (s);
			}
	;

%%
int yyerror(char *error,char *var,int n)
{
  	printf("%s %s %d\n",error,var,n);	
    return 0;
}
int checkInicialized(ast_node *tmp1,ast_node *tmp2)
{
struct ast_symbol_reference_node* tmpy=(struct ast_symbol_reference_node *)(tmp1);
struct ast_symbol_reference_node* tmpx=(struct ast_symbol_reference_node *)(tmp2);
struct symbol_node* symb=(struct symbol_node *)(tmpy->symbol);
struct symbol_node* symb2=(struct symbol_node *)(tmpx->symbol);

if(tmp1->node_type=='S'&&symb->type==0||tmp2->node_type=='S'&&symb2->type==0)
{
	yyerror("error","zmienna nie zainicjalizowana w linii",yylineno-1);
	return 1;
}

return 0;
}
int checkDeclared(symbol_node* tmp)
{
if(tmp==0)
{
	yyerror("error","zmienna nie zadeklarowana w linii",yylineno-1);
	return 1;
}
//////////
return 0;
}
int inicjalize(ast_node* s)
{	

	ast_node* tmp1=s->left;
	ast_node* tmp2=s->right;
	
	if(tmp1->node_type=='N'&&tmp2->node_type=='N')
		return 1;
	return 0;

}
void preorder(ast_node *v,int adres)
{
////
  if(v)
  {
	switch (v->node_type){
	case 'D':
		_inicializeVariable(v->right);
		preorder(v->left,adres);
		return;
		break;
	case 'P':
		_put(v->right,adres);
/////		free_ast_tree(v->right);
		return;
		break;
	case 'A':
		_assign(v->left,v->right,adres);
//		free_ast_tree(v);
		return;
		break;
	case 'G':
		_get(v->left);
//		free_ast_tree(v->left);
		return;
		break;
	case 'I':
		_IF(v,adres);
//		free_ast_tree(v);
		return;
		break;
	case 'W':
		_WHILE(v,adres);
//		free_ast_tree(v);	
		return;
		break;
	default :
		break;
	break;
    }
    preorder(v->left,adres);     
    preorder(v->right,adres);    
  }
//	free(v);//

}

int main()
{
	//
	if(yyparse())
	{
		printf("kompilacja przerwana \n");
		return 0;
	}
	
	
	jedynka=adres;
	printf("RESET \n");
	counter++;
	printf("INC \n");
	counter++;
	printf("STORE %d\n",jedynka);
	counter++;

	adres++;
	preorder(root,adres);
	 _halt();

    return 0;
}
