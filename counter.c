
#include "counter.h"
extern int counter;
#include "parser.h"
extern int counter;
void  Countreset()
{
	counter++;
}
void  Counthalt()
{
	counter++;
}
void  Countput(ast_node *v,int adres)
{	

	if(v->node_type=='S')
	{	
		struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(v);
		struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
		 Countload(symb->adres);
	}
	else if(v->node_type=='N')
	{
		struct ast_number_node *num=(struct ast_number_node*)(v);
		int adresTMP=++adres+1;
		 CountAssign(num->value,adres,adresTMP);
		adres--;
	}
	counter++;
}
void  Countload(int adres)
{
	counter++;
}
void  CountinicializeVariable(int adres)
{
}
void  Countassign(symbol_node *v,ast_node *v2,int adres)
{	
	int adresTMP=adres+2;
	int adresTMP2=adresTMP+1;
	if(v2->node_type=='V')
	{	v2=v2->left;
		if(v2->node_type=='S')
		{	
		struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(v2);
		struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
		 Countload(symb->adres);
		}
		else if(v2->node_type=='N')
		{
		struct ast_number_node *num=(struct ast_number_node*)(v2);
		 CountAssign(num->value,adres,adresTMP);
		adres--;
		}
	}
	else if(v2->node_type=='+')
	{	
		ast_node *v3=v2->right;
		v2=v2->left;
		if(v2->node_type=='S'&&v3->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(v2);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v3);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			 CountaddZmienneGet(symb->adres,symb2->adres);
		}
		else if(v2->node_type=='N'&&v3->node_type=='N')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v2);
			struct ast_number_node *num2=(struct ast_number_node*)(v3);
			 CountAssign( CountaddStale(num->value,num2->value),adres,adresTMP);
		}
		else if(v2->node_type=='N'&&v3->node_type=='S')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v2);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v3);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			 CountaddStala_Zmienna(num->value,symb2->adres,adresTMP);
		}
		else if(v2->node_type=='S'&&v3->node_type=='N')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v3);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v2);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			 CountaddStala_Zmienna(num->value,symb2->adres,adresTMP);
		}
	}
	else if(v2->node_type=='-')
	{	
		ast_node *v3=v2->right;
		v2=v2->left;
		if(v2->node_type=='S'&&v3->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(v2);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v3);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			 CountsubZmienneGet(symb->adres,symb2->adres);
		}
		else if(v2->node_type=='N'&&v3->node_type=='N')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v2);
			struct ast_number_node *num2=(struct ast_number_node*)(v3);
			 CountAssign( CountsubStale(num->value,num2->value),adres,adresTMP);
		}
		else if(v2->node_type=='N'&&v3->node_type=='S')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v2);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v3);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			 CountsubStala_Zmienna(num->value,symb2->adres,adresTMP);
			counter++;
		}
		else if(v2->node_type=='S'&&v3->node_type=='N')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v3);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v2);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			 CountsubStala_Zmienna(num->value,symb2->adres,adresTMP);
			 Countstore(adresTMP);
			 CountsubZmienneGet(symb2->adres,adresTMP);
		}
	}
	else if(v2->node_type=='*')
	{	
		ast_node *v3=v2->right;
		v2=v2->left;
		if(v2->node_type=='S'&&v3->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(v2);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v3);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			 CounttimesZmienneGet(symb->adres,symb2->adres,adresTMP);
		}
		else if(v2->node_type=='N'&&v3->node_type=='N')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v2);
			struct ast_number_node *num2=(struct ast_number_node*)(v3);
			 CountAssign( CounttimesStale(num->value,num2->value),adres,adresTMP);
		}
		else if(v2->node_type=='N'&&v3->node_type=='S')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v2);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v3);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			if(checkTwo(num->value,strlen(num->value)))
			{
				counter++;
				counter++;
			}
			else{
				CounttimesStala_Zmienna(num->value,adresTMP2,adresTMP);
				counter++;
				CounttimesZmienneGet(symb2->adres,adresTMP,adresTMP2);
			}
		}
		else if(v2->node_type=='S'&&v3->node_type=='N')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v3);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v2);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			if(checkTwo(num->value,strlen(num->value)))
			{
				counter++;
				counter++;
			}
			else{
				CounttimesStala_Zmienna(num->value,adresTMP2,adresTMP);
				counter++;
				CounttimesZmienneGet(symb2->adres,adresTMP,adresTMP2);
			}
		}
	}
	else if(v2->node_type=='/')
	{	
		ast_node *v3=v2->right;
		v2=v2->left;
		if(v2->node_type=='S'&&v3->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(v2);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v3);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			 CountfastDiv(symb->adres,symb2->adres,adresTMP);
		}
		else if(v2->node_type=='N'&&v3->node_type=='N')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v2);
			struct ast_number_node *num2=(struct ast_number_node*)(v3);
			 CountAssign( CountdivStale(num->value,num2->value),adres,adresTMP);
		}
		else if(v2->node_type=='N'&&v3->node_type=='S')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v2);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v3);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			 CountdivStala_Zmienna(num->value,symb2->adres,adresTMP);
			counter++;
			 CountfastDiv(symb2->adres,adresTMP,adresTMP2);
		}
		else if(v2->node_type=='S'&&v3->node_type=='N')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v3);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v2);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			if(checkTwo(num->value,strlen(num->value)))
			{
				counter++;
				counter++;
			}
			else{
				 CountdivStala_Zmienna(num->value,symb2->adres,adresTMP);
				counter++;
				 CountfastDiv(symb2->adres,adresTMP,adresTMP2);
			}
			
		}
	}
	else if(v2->node_type=='%')
	{	
		ast_node *v3=v2->right;
		v2=v2->left;
		if(v2->node_type=='S'&&v3->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(v2);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v3);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			 CountfastMod(symb->adres,symb2->adres,adresTMP);
		}
		else if(v2->node_type=='N'&&v3->node_type=='N')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v2);
			struct ast_number_node *num2=(struct ast_number_node*)(v3);
			 CountAssign( CountmodStale(num->value,num2->value),adres,adresTMP);
		}
		else if(v2->node_type=='N'&&v3->node_type=='S')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v2);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v3);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			 CountmodStala_Zmienna(num->value,symb2->adres,adresTMP);
			counter++;
			 CountfastMod(symb2->adres,adresTMP,adresTMP2);
		}
		else if(v2->node_type=='S'&&v3->node_type=='N')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v3);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v2);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			 CountmodStala_Zmienna(num->value,symb2->adres,adresTMP);
			counter++;
			 CountfastMod(symb2->adres,adresTMP,adresTMP2);
		}
	}
	counter++;

}
void  Countstore(int adres)
{
	counter++;
}
void  Countget(symbol_node *v)
{
	counter++;
	counter++;

}
/*************************************************/
char*  CountaddStale(char* ptr,char* ptr2)
{
	counter++;
	return operationConst(ptr,ptr2,1);
}
void  CountaddZmienneGet(int adres1,int adres2)
{
	counter++;
	counter++;
}
void  CountaddStala_Zmienna(char *value,int adres,int ad)
{
	counter++;
	int adres2=ad+1;
	
	mpz_t tmp;
	mpz_init (tmp);
	mpz_set_str(tmp,value,10);
	
	mpz_t tmp2;
	mpz_init (tmp2);
	mpz_set_str(tmp2,"25",10);
	
	
	if(mpz_cmp(tmp,tmp2)<0)
	{
		mpz_set_str(tmp2,"1",10);	
		counter++;
		while(mpz_cmp(tmp,tmp2)>=0)
		{
			counter++;
			mpz_sub(tmp,tmp,tmp2);
			
		}
		
	}
	else
	{
		CountAssign(value,ad,adres2);
		counter++;
	}
	 mpz_clear(tmp);
	 mpz_clear(tmp2);
}
/*************************************************/
char*  CountsubStale(char* ptr,char* ptr2)
{
	counter++;
	return operationConst(ptr,ptr2,2);
}
void  CountsubZmienneGet(int adres1,int adres2)
{
	counter++;
	counter++;
}
void  CountsubStala_Zmienna(char *value,int adres,int ad)
{
	counter++;
	int adres2=ad+1;
	 CountAssign(value,adres,adres2);

}
/*************************************************/
char*  CounttimesStale(char* ptr,char* ptr2)
{	
	counter++;
	return operationConst(ptr,ptr2,3);
}
void  CounttimesZmienneGet(int adres1,int adres2,int adresTMP)
{
/** to do zrobienia -> szybkie mnozenie popracowac nad mnozeniem***/
	CountGE(adres1,adres2);
	
	counter++;
	/**********************9*****/
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	
	/**********************9*****/
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	
	/////*****************16**********************/
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	/**********************3**********************/
	counter++;
	counter++;
	counter++;
}	
void  CounttimesStala_Zmienna(char *value,int adres,int ad)
{
	counter++;
	int adres2=ad+1;
	 CountAssign(value,adres,adres2);

}
/*************************************************/
char*  CountdivStale(char* ptr,char* ptr2)
{
	counter++;
	return operationConst(ptr,ptr2,4);
}
void CountfastDiv(int adres1,int adres2,int adresTMP)
{

	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	/*************dzielimy **********1**************/
	counter++;
	/**********sciagamy flage przeniesienia ***9***/
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	/******** sprawdzamy warunek konca ***4***///
	counter++;
	counter++;
	counter++;
	counter++;
	/**przesowamy dzielna i reszte ***14*/
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	/************** sprawdzamy czy cos zostaje by dopisad do reszty**********12**********/
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	/*************wczytujemy wynik*********************/
	counter++;
	counter++;
	counter++;

}
void  CountdivStala_Zmienna(char *value,int adres,int ad)
{
	counter++;
	int adres2=ad+1;
	 CountAssign(value,adres,adres2);

}
/*************************************************/
char*  CountmodStale(char* ptr,char* ptr2)
{
	counter++;
	return operationConst(ptr,ptr2,5);
}
void CountfastMod(int adres1,int adres2,int adresTMP)
{

	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	/*************dzielimy **********1**************/
	counter++;
	/**********sciagamy flage przeniesienia ***9***/
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	/******** sprawdzamy warunek konca ***4***///
	counter++;
	counter++;
	counter++;
	counter++;
	/**przesowamy dzielna i reszte ***14*/
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	/************** sprawdzamy czy cos zostaje by dopisad do reszty**********12**********/
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	counter++;
	/*************wczytujemy wynik*********************/
	counter++;
	counter++;
	counter++;

}
void  CountmodStala_Zmienna(char *value,int adres,int ad)
{
	counter++;
	 int adres2=ad+1;
	 CountAssign(value,adres,adres2);

}
/**10*/
void  CountEQ(int adres1,int adres2)
{
	counter+=10;
}
void  CountNEQ(int adres1,int adres2)
{
	counter+=10;
}
void  CountGE(int adres1,int adres2)
{
	counter+=4;
}
void  CountLE(int adres1,int adres2)
{
	 CountGE(adres2,adres1);
}
void  CountGEQ(int adres1,int adres2)
{
	counter+=10;
}
void  CountLEQ(int adres1,int adres2)
{
	 CountGEQ(adres2,adres1);
}
void  CountWHILE(struct ast_while_node *v,int adres)
{
	struct ast_node * condition=v->condition;

	struct ast_node * while_branch=v->while_branch;

	CountOPERATE(condition,adres);
	
	int etykietaCond=counter;
	
	int etykietaif=counter;
	count(while_branch,adres);
	counter++;
	counter++;

}
void  CountIF(struct ast_if_node *v,int adres)
{
	struct ast_node * condition=v->condition;

	struct ast_node * if_branch=v->if_branch;

	struct ast_node * else_branch=v->else_branch;
	
	CountOPERATE(condition,adres);
	
	int etykietaif=counter;
	int koniecIF;
	if(else_branch)
		koniecIF=2;	else	koniecIF=1;
		
	count(if_branch,adres);
	counter++;
	if(else_branch){
		etykietaif=counter;
		count(else_branch,adres);
		counter++;
	}
	
}
void  CountOPERATE(struct ast_equality_node *operate,int adres)
{
	struct ast_equality_node* condition=(struct ast_equality_node*)operate;
	
	if(operate->opr=='=')
	{
		struct ast_equality_node* leftCondition=(struct ast_equality_node*)condition;
		struct ast_equality_node* rightCondition=(struct ast_equality_node*)condition;
		leftCondition=leftCondition->left;
		rightCondition=rightCondition->right;
		if(leftCondition->node_type=='S'&&rightCondition->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(leftCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(rightCondition);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			 CountEQ(symb->adres,symb2->adres);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='N')
		{	
			struct ast_number_node *num=(struct ast_number_node*)(leftCondition);
			struct ast_number_node *num2=(struct ast_number_node*)(rightCondition);
			if(compareNumbers(num->value,num2->value)==0)
			{
				counter++;
			}
			else{
				counter++;
				}
		}
		else if(leftCondition->node_type=='S'&&rightCondition->node_type=='N')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(leftCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_number_node *num2=(struct ast_number_node*)(rightCondition);
			int tmp1=adres+1;
			int tmp2=adres+2;
			counter++;
			 CountAssign(num2->value,tmp1,tmp2);
			counter++;
			 CountEQ(tmp1,symb->adres);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(rightCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_number_node *num2=(struct ast_number_node*)(leftCondition);
			int tmp1=adres+1;
			int tmp2=adres+2;
			counter++;
			 CountAssign(num2->value,tmp1,tmp2);
			counter++;
			 CountEQ(tmp1,symb->adres);
		}
	}
	else if(operate->opr=='!')
	{
		struct ast_equality_node* leftCondition=(struct ast_equality_node*)condition;
		struct ast_equality_node* rightCondition=(struct ast_equality_node*)condition;
		leftCondition=leftCondition->left;
		rightCondition=rightCondition->right;
		if(leftCondition->node_type=='S'&&rightCondition->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(leftCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(rightCondition);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			 CountNEQ(symb->adres,symb2->adres);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='N')
		{	
			struct ast_number_node *num=(struct ast_number_node*)(leftCondition);
			struct ast_number_node *num2=(struct ast_number_node*)(rightCondition);
			if(compareNumbers(num->value,num2->value)!=0)
			{
				counter++;
			}
			else{	
				counter++;
				}
		}
		else if(leftCondition->node_type=='S'&&rightCondition->node_type=='N')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(leftCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_number_node *num2=(struct ast_number_node*)(rightCondition);
			int tmp1=adres+1;
			int tmp2=adres+2;
			counter++;
			 CountAssign(num2->value,tmp1,tmp2);
			counter++;
			 CountNEQ(tmp1,symb->adres);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(rightCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_number_node *num2=(struct ast_number_node*)(leftCondition);
			int tmp1=adres+1;
			int tmp2=adres+2;
			counter++;
			 CountAssign(num2->value,tmp1,tmp2);
			counter++;
			 CountNEQ(tmp1,symb->adres);
		}
	}
	else if(operate->opr=='l')
	{
		struct ast_equality_node* leftCondition=(struct ast_equality_node*)condition;
		struct ast_equality_node* rightCondition=(struct ast_equality_node*)condition;
		leftCondition=leftCondition->left;
		rightCondition=rightCondition->right;
		if(leftCondition->node_type=='S'&&rightCondition->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(leftCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(rightCondition);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			 CountLE(symb->adres,symb2->adres);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='N')
		{	
			struct ast_number_node *num=(struct ast_number_node*)(leftCondition);
			struct ast_number_node *num2=(struct ast_number_node*)(rightCondition);
			if(compareNumbers(num->value,num2->value)<0)
			{
				counter++;
			}
			else{	
				counter++;
				}
		}
		else if(leftCondition->node_type=='S'&&rightCondition->node_type=='N')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(leftCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_number_node *num2=(struct ast_number_node*)(rightCondition);
			int tmp1=adres+1;
			int tmp2=adres+2;
			counter++;
			 CountAssign(num2->value,tmp1,tmp2);
			counter++;
			 CountLE(symb->adres,tmp1);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(rightCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_number_node *num2=(struct ast_number_node*)(leftCondition);
			int tmp1=adres+1;
			int tmp2=adres+2;
			counter++;
			 CountAssign(num2->value,tmp1,tmp2);
			counter++;
			 CountLE(tmp1,symb->adres);
		}
	}
	else if(operate->opr=='g')
	{
		struct ast_equality_node* leftCondition=(struct ast_equality_node*)condition;
		struct ast_equality_node* rightCondition=(struct ast_equality_node*)condition;
		leftCondition=leftCondition->left;
		rightCondition=rightCondition->right;
		if(leftCondition->node_type=='S'&&rightCondition->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(leftCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(rightCondition);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			 CountGE(symb->adres,symb2->adres);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='N')
		{	
			struct ast_number_node *num=(struct ast_number_node*)(leftCondition);
			struct ast_number_node *num2=(struct ast_number_node*)(rightCondition);
			if(compareNumbers(num->value,num2->value)>0)
			{
				counter++;
			}
			else{	
				counter++;
				}
		}
		else if(leftCondition->node_type=='S'&&rightCondition->node_type=='N')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(leftCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_number_node *num2=(struct ast_number_node*)(rightCondition);
			int tmp1=adres+1;
			int tmp2=adres+2;
			counter++;
			 CountAssign(num2->value,tmp1,tmp2);
			counter++;
			 CountGE(symb->adres,tmp1);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(rightCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_number_node *num2=(struct ast_number_node*)(leftCondition);
			int tmp1=adres+1;
			int tmp2=adres+2;
			counter++;
			 CountAssign(num2->value,tmp1,tmp2);
			counter++;
			 CountGE(tmp1,symb->adres);
		}
	}
	else if(operate->opr=='L')
	{
		struct ast_equality_node* leftCondition=(struct ast_equality_node*)condition;
		struct ast_equality_node* rightCondition=(struct ast_equality_node*)condition;
		leftCondition=leftCondition->left;
		rightCondition=rightCondition->right;
		if(leftCondition->node_type=='S'&&rightCondition->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(leftCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(rightCondition);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			 CountLEQ(symb->adres,symb2->adres);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='N')
		{	
			struct ast_number_node *num=(struct ast_number_node*)(leftCondition);
			struct ast_number_node *num2=(struct ast_number_node*)(rightCondition);
			if(compareNumbers(num->value,num2->value)==0||(compareNumbers(num->value,num2->value)<0))
			{
				counter++;
			}
			else{	
				counter++;
				}
		}
		else if(leftCondition->node_type=='S'&&rightCondition->node_type=='N')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(leftCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_number_node *num2=(struct ast_number_node*)(rightCondition);
			int tmp1=adres+1;
			int tmp2=adres+2;
			counter++;
			 CountAssign(num2->value,tmp1,tmp2);
			counter++;
			 CountLEQ(symb->adres,tmp1);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(rightCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_number_node *num2=(struct ast_number_node*)(leftCondition);
			int tmp1=adres+1;
			int tmp2=adres+2;
			counter++;
			 CountAssign(num2->value,tmp1,tmp2);
			counter++;
			 CountLEQ(tmp1,symb->adres);
		}
	}
	else if(operate->opr=='G')
	{
		struct ast_equality_node* leftCondition=(struct ast_equality_node*)condition;
		struct ast_equality_node* rightCondition=(struct ast_equality_node*)condition;
		leftCondition=leftCondition->left;
		rightCondition=rightCondition->right;
		if(leftCondition->node_type=='S'&&rightCondition->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(leftCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(rightCondition);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			 CountGEQ(symb->adres,symb2->adres);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='N')
		{	
			struct ast_number_node *num=(struct ast_number_node*)(leftCondition);
			struct ast_number_node *num2=(struct ast_number_node*)(rightCondition);
			if(compareNumbers(num->value,num2->value)==0||(compareNumbers(num->value,num2->value)>0))
			{
				counter++;
			}
			else{	
				counter++;
				}
		}
		else if(leftCondition->node_type=='S'&&rightCondition->node_type=='N')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(leftCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_number_node *num2=(struct ast_number_node*)(rightCondition);
			int tmp1=adres+1;
			int tmp2=adres+2;
			counter++;
			 CountAssign(num2->value,tmp1,tmp2);
			counter++;
			 CountGEQ(symb->adres,tmp1);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(rightCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_number_node *num2=(struct ast_number_node*)(leftCondition);
			int tmp1=adres+1;
			int tmp2=adres+2;
			counter++;
			 CountAssign(num2->value,tmp1,tmp2);
			counter++;
			 CountGEQ(tmp1,symb->adres);
		}
	}
}
void count(ast_node *v,int adres)
{
  if(v)
  {
	switch (v->node_type){
	case 'D':
		CountinicializeVariable(adres);
		adres++;
		count(v->left,adres);
		return;
		break;
	case 'P':
		Countput(v->right,adres);
		return;
		break;
	case 'A':
		Countassign(v->left,v->right,adres);
		return;
		break;
	case 'G':
		Countget(v->left);
		return;
		break;
	case 'I':
		CountIF(v,adres);
		return;
		break;
	case 'W':
		CountWHILE(v,adres);	
		return;
		break;
	default :
		break;
	break;
    }
    count(v->left,adres);     
    count(v->right,adres);    
  }
}


