#include "parser.h"
extern int counter;
extern int jedynka;
void _reset()
{
	printf("RESET \n");
	counter++;
}
void _halt()
{
	printf("HALT \n");
	counter++;
}
void _put(ast_node *v,int adres)
{	
	if(v->node_type=='S')
	{	
		struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(v);
		struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
		_load(symb->adres);
	}
	else if(v->node_type=='N')
	{
		struct ast_number_node *num=(struct ast_number_node*)(v);
		int adresTMP=++adres+1;
		_Assign(num->value,adres,adresTMP);
		adres--;
	}
	printf("WRITE \n");
	counter++;
}
void _load(int adres)
{
	printf("LOAD %d\n",adres);
	counter++;
}
void _inicializeVariable(struct symbol_node *v)
{
	
}
void _assign(symbol_node *v,ast_node *v2,int adres)
{	
	int adresTMP=adres+20;
	int adresTMP2=adresTMP+10;
	if(v2->node_type=='V')
	{	v2=v2->left;
		if(v2->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(v2);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			_load(symb->adres);
		}
		else if(v2->node_type=='N')
		{
		struct ast_number_node *num=(struct ast_number_node*)(v2);
		_Assign(num->value,adres,adresTMP);
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
			_addZmienneGet(symb->adres,symb2->adres);
		}
		else if(v2->node_type=='N'&&v3->node_type=='N')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v2);
			struct ast_number_node *num2=(struct ast_number_node*)(v3);
			_Assign(_addStale(num->value,num2->value),adres,adresTMP);
		}
		else if(v2->node_type=='N'&&v3->node_type=='S')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v2);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v3);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			_addStala_Zmienna(num->value,symb2->adres,adresTMP);
		}
		else if(v2->node_type=='S'&&v3->node_type=='N')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v3);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v2);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			_addStala_Zmienna(num->value,symb2->adres,adresTMP);
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
			_subZmienneGet(symb->adres,symb2->adres);
		}
		else if(v2->node_type=='N'&&v3->node_type=='N')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v2);
			struct ast_number_node *num2=(struct ast_number_node*)(v3);
			_Assign(_subStale(num->value,num2->value),adres,adresTMP);
		}
		else if(v2->node_type=='N'&&v3->node_type=='S')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v2);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v3);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			_subStala_Zmienna(num->value,symb2->adres,adresTMP);
			printf("SUB %d\n",symb2->adres);
			counter++;
		}
		else if(v2->node_type=='S'&&v3->node_type=='N')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v3);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v2);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			_subStala_Zmienna(num->value,adresTMP,adresTMP);
			_store(adresTMP);
			_subZmienneGet(symb2->adres,adresTMP);
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
			_timesZmienneGet(symb->adres,symb2->adres,adresTMP);
		}
		else if(v2->node_type=='N'&&v3->node_type=='N')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v2);
			struct ast_number_node *num2=(struct ast_number_node*)(v3);
			_Assign(_timesStale(num->value,num2->value),adres,adresTMP);
		}
		else if(v2->node_type=='N'&&v3->node_type=='S')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v2);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v3);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			
			if(checkTwo(num->value,strlen(num->value)))
			{
				printf("LOAD %d\n",symb2->adres);
				counter++;
				printf("SHL %d\n",jedynka);
				counter++;
			}
			else{
				_timesStala_Zmienna(num->value,adresTMP2,adresTMP);
				printf("STORE %d\n",adresTMP);
				counter++;
				_timesZmienneGet(symb2->adres,adresTMP,adresTMP2);
			}
		}
		else if(v2->node_type=='S'&&v3->node_type=='N')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v3);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v2);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			if(checkTwo(num->value,strlen(num->value)))
			{
				printf("LOAD %d\n",symb2->adres);
				counter++;
				printf("SHL %d\n",jedynka);
				counter++;
			}
			else{
				_timesStala_Zmienna(num->value,adresTMP2,adresTMP);
				printf("STORE %d\n",adresTMP);
				counter++;
				_timesZmienneGet(symb2->adres,adresTMP,adresTMP2);
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
			_fastDiv(symb->adres,symb2->adres,adresTMP);
		}
		else if(v2->node_type=='N'&&v3->node_type=='N')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v2);
			struct ast_number_node *num2=(struct ast_number_node*)(v3);
			_Assign(_divStale(num->value,num2->value),adres,adresTMP);
		}
		else if(v2->node_type=='N'&&v3->node_type=='S')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v2);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v3);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
				_divStala_Zmienna(num->value,adresTMP2,adresTMP);
				printf("STORE %d\n",adresTMP);
				counter++;
				_fastDiv(adresTMP,symb2->adres,adresTMP2);
			
		}
		else if(v2->node_type=='S'&&v3->node_type=='N')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v3);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v2);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			if(checkTwo(num->value,strlen(num->value)))
			{
				printf("LOAD %d\n",symb2->adres);
				counter++;
				printf("SHR %d\n",jedynka);
				counter++;
			}
			else{
				_divStala_Zmienna(num->value,adresTMP2,adresTMP);
				printf("STORE %d\n",adresTMP);
				counter++;
				_fastDiv(symb2->adres,adresTMP,adresTMP2);
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
			_fastMod(symb->adres,symb2->adres,adresTMP);
		}
		else if(v2->node_type=='N'&&v3->node_type=='N')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v2);
			struct ast_number_node *num2=(struct ast_number_node*)(v3);
			_Assign(_modStale(num->value,num2->value),adres,adresTMP);
		}
		else if(v2->node_type=='N'&&v3->node_type=='S')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v2);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v3);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			_modStala_Zmienna(num->value,adresTMP2,adresTMP);
			printf("STORE %d\n",adresTMP);
			counter++;
			_fastMod(adresTMP,symb2->adres,adresTMP2);
		}
		else if(v2->node_type=='S'&&v3->node_type=='N')
		{
			struct ast_number_node *num=(struct ast_number_node*)(v3);
			struct ast_symbol_reference_node* tmp2=(struct ast_symbol_reference_node *)(v2);
			struct symbol_node* symb2=(struct symbol_node *)(tmp2->symbol);
			_modStala_Zmienna(num->value,adresTMP2,adresTMP);
			printf("STORE %d\n",adresTMP);
			counter++;
			_fastMod(symb2->adres,adresTMP,adresTMP2);
		}
	}
	printf("STORE %d\n",v->adres);
	counter++;

}
void _store(int adres)
{
	printf("STORE %d\n",adres);
	counter++;
}
void _get(symbol_node *v)
{
	printf("READ\n");
	counter++;
	printf("STORE %d\n",v->adres);
	counter++;

}
/*************************************************/
char* _addStale(char* ptr,char* ptr2)
{
	printf("RESET\n");
	counter++;
	return operationConst(ptr,ptr2,1);
}
void _addZmienneGet(int adres1,int adres2)
{
	printf("LOAD %d\n",adres1);
	counter++;
	printf("ADD %d\n",adres2);
	counter++;
}
void _addStala_Zmienna(char *value,int adres,int ad)
{
	printf("RESET \n");
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
		printf("LOAD %d\n",adres);
		counter++;
		while(mpz_cmp(tmp,tmp2)>=0)
		{
			printf("INC\n");
			counter++;
			mpz_sub(tmp,tmp,tmp2);
			
		}
		
	}
	else
	{
		_Assign(value,ad,adres2);
		printf("ADD %d\n",adres);
		counter++;
	}
	 mpz_clear(tmp);
	 mpz_clear(tmp2);
}
/*************************************************/
char* _subStale(char* ptr,char* ptr2)
{
	printf("RESET\n");
	counter++;
	return operationConst(ptr,ptr2,2);
}
void _subZmienneGet(int adres1,int adres2)
{
	printf("LOAD %d\n",adres1);
	counter++;
	printf("SUB %d\n",adres2);
	counter++;
}
void _subStala_Zmienna(char *value,int adres,int ad)
{
	printf("RESET \n");
	counter++;
	int adres2=ad+1;
	_Assign(value,ad,adres2);

}
/*************************************************/
char* _timesStale(char* ptr,char* ptr2)
{	
	printf("RESET\n");
	counter++;
	return operationConst(ptr,ptr2,3);
}
void _timesZmienneGet(int adres1,int adres2,int adresTMP)
{
	int back_line;
	int front_line;
	int tmp1=adresTMP+1;
	int out=tmp1+1;
	int dwa = out +1;
	int tmp2 = dwa +1;
	
	_GE(adres1,adres2);
	printf("JZERO %d\n",counter+10);
	counter++;
	/**********************9*****/
	printf("RESET\n");
	counter++;
	printf("STORE %d\n",out);
	counter++;
	printf("LOAD %d\n",adres2);
	counter++;
	printf("JZERO %d\n",counter+34);
	counter++;
	printf("STORE %d\n",tmp1);
	counter++;
	printf("LOAD %d\n",adres1);
	counter++;
	printf("JZERO %d\n",counter+31);
	counter++;
	printf("STORE %d\n",tmp2);
	counter++;
	printf("JUMP %d\n",counter+11);
	counter++;
	
	/**********************9*****/
	printf("RESET\n");
	counter++;
	printf("STORE %d\n",out);
	counter++;
	printf("LOAD %d\n",adres2);
	counter++;
	printf("JZERO %d\n",counter+23);
	counter++;
	printf("STORE %d\n",tmp2);
	counter++;
	printf("LOAD %d\n",adres1);
	counter++;
	printf("JZERO %d\n",counter+20);
	counter++;
	printf("STORE %d\n",tmp1);
	counter++;
	
	/////*****************16**********************/
	printf("LOAD %d\n",tmp2);
	counter++;
	printf("JZERO %d\n",counter+15);
	counter++;
	printf("LOAD %d\n",tmp1);
	counter++;
	printf("JZERO %d\n",counter+13);
	counter++;
	printf("JODD %d\n",counter+2);
	counter++;
	printf("JUMP %d\n",counter+4);
	counter++;
	printf("LOAD %d\n",tmp2);
	counter++;
	printf("ADD %d\n",out);
	counter++;
	printf("STORE %d\n",out);
	counter++;
	printf("LOAD %d\n",tmp2);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("STORE %d\n",tmp2);
	counter++;
	printf("LOAD %d\n",tmp1);
	counter++;
	printf("SHR %d\n",jedynka);
	counter++;
	printf("STORE %d\n",tmp1);
	counter++;
	printf("JUMP %d\n",counter-15);
	counter++;
	/**********************3**********************/
	printf("LOAD %d\n",out);
	counter++;
	printf("JUMP %d\n",counter+2);
	counter++;
	printf("RESET \n");
	counter++;
	
}	
void _timesStala_Zmienna(char *value,int adres,int ad)
{
	printf("RESET \n");
	counter++;
	int adres2=ad+1;
	_Assign(value,adres,adres2);

}
int checkTwo(char *ptr,int ln)
{
	int i=0;
	ln=0;
		
	if((ptr[0]-48)==2)
		return 1;
	
	return 0;
}
/*************************************************/
char* _divStale(char* ptr,char* ptr2)
{
	printf("RESET\n");
	counter++;
	return operationConst(ptr,ptr2,4);
}
void _fastDiv(int adres1,int adres2,int adresTMP)
{
	int tmp1=adresTMP+1;
	int reszta=tmp1+1;
	int tmpr=reszta+1;
	int licznik=tmpr+1;
	
	printf("RESET \n");
	counter++;
	printf("STORE %d\n",licznik);
	counter++;
	printf("STORE %d\n",reszta);
	counter++;
	/*** sprawdzamy czy zero **6*/
	printf("LOAD %d\n",adres1);
	counter++;
	printf("STORE %d\n",tmp1);
	counter++;
	printf("JZERO %d\n",counter+92);
	counter++;
	printf("LOAD %d\n",adres2);
	counter++;
	printf("JZERO %d\n",counter+90);
	counter++;
	/***** szukamy pierwszej jedynki ***12**/
	int	petla=counter;
	printf("LOAD %d\n",tmp1);
	counter++;
	printf("JODD %d\n",counter+8);
	counter++;
	printf("SHR %d\n",jedynka);
	counter++;
	printf("STORE %d\n",tmp1);
	counter++;
	printf("LOAD %d\n",licznik);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("INC \n");
	counter++;
	printf("STORE %d\n",licznik);
	counter++;
	printf("JUMP %d\n",petla);
	/************znalazlem *********9*****/
	counter++;
	printf("SHR %d\n",jedynka);
	counter++;
	printf("STORE %d\n",tmp1);
	counter++;
	printf("RESET \n");
	counter++;
	printf("INC \n");
	counter++;
	printf("STORE %d\n",tmpr);
	counter++;
	printf("LOAD %d\n",licznik);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("INC \n");
	counter++;
	printf("STORE %d\n",licznik);
	/***pozostala czesc odwrotnosc*****13********/
	counter++;
	int petla2=counter;
	printf("LOAD %d\n",tmp1);
	counter++;
	printf("JZERO %d\n",counter+23);
	counter++;
	printf("JODD %d\n",counter+11);
	counter++;
	printf("SHR %d\n",jedynka);
	counter++;
	printf("STORE %d\n",tmp1);
	counter++;
	printf("LOAD %d\n",tmpr);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("STORE %d\n",tmpr);
	counter++;
	printf("LOAD %d\n",licznik);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("INC \n");
	counter++;
	printf("STORE %d\n",licznik);
	counter++;
	printf("JUMP %d\n",petla2);
	/********************************11**********/
	counter++;
	printf("SHR %d\n",jedynka);
	counter++;
	printf("STORE %d\n",tmp1);
	counter++;
	printf("LOAD %d\n",tmpr);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("INC \n");
	counter++;
	printf("STORE %d\n",tmpr);
	counter++;
	printf("LOAD %d\n",licznik);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("INC \n");
	counter++;
	printf("STORE %d\n",licznik);
	counter++;
	printf("JUMP %d\n",petla2);
	/*************zwiekszamy ilosc bitow licznika o 1****************4******/
	counter++;
	printf("LOAD %d\n",licznik);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("INC \n");
	counter++;
	printf("STORE %d\n",licznik);
	/*************dzielimy **********1**************/
	counter++;
	printf("RESET \n");
	/**********sciagamy flage przeniesienia ***9***/
	counter++;
	petla2=counter;
	printf("JZERO %d\n",counter+6);
	counter++;
	printf("LOAD %d\n",tmp1);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("INC\n");
	counter++;
	printf("STORE %d\n",tmp1);
	counter++;
	printf("JUMP %d\n",counter+4);
	counter++;
	printf("LOAD %d\n",tmp1);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("STORE %d\n",tmp1);
	/******** sprawdzamy warunek konca ***4***///
	counter++;
	printf("LOAD %d\n",licznik);
	counter++;
	printf("SHR %d\n",jedynka);
	counter++;
	printf("JZERO %d\n",counter+28);
	counter++;
	printf("STORE %d\n",licznik);
	/**przesowamy dzielna i reszte ***14*/
	counter++;
	printf("LOAD %d\n",tmpr);
	counter++;
	printf("JODD %d\n",counter+7);
	counter++;
	printf("SHR %d\n",jedynka);
	counter++;
	printf("STORE %d\n",tmpr);
	counter++;
	printf("LOAD %d\n",reszta);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("STORE %d\n",reszta);
	counter++;
	printf("JUMP %d\n",counter+7);
	counter++;
	printf("SHR %d\n",jedynka);
	counter++;
	printf("STORE %d\n",tmpr);
	counter++;
	printf("LOAD %d\n",reszta);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("INC\n");
	counter++;
	printf("STORE %d\n",reszta);
	/************** sprawdzamy czy cos zostaje by dopisad do reszty**********12**********/
	counter++;
	printf("JZERO %d\n",counter+10);
	counter++;
	printf("SUB %d\n",adres2);
	counter++;
	printf("JZERO %d\n",counter+5);
	counter++;
	printf("STORE %d\n",reszta);
	counter++;
	printf("RESET \n");
	counter++;
	printf("INC\n");
	counter++;
	printf("JUMP %d\n",petla2);
	counter++;
	printf("LOAD %d\n",adres2);
	counter++;
	printf("SUB %d\n",reszta);
	counter++;
	printf("JZERO %d\n",counter-6);
	counter++;
	printf("RESET \n");
	counter++;
	printf("JUMP %d\n",petla2);
	counter++;
	/*************wczytujemy wynik*********************/
	printf("LOAD %d\n",tmp1);
	counter++;
	printf("JUMP %d\n",counter+2);
	counter++;
	printf("RESET \n");
	counter++;
	
}
void _divStala_Zmienna(char *value,int adres,int ad)
{
	printf("RESET \n");
	counter++;
	int adres2=ad+1;
	_Assign(value,adres,adres2);

}
/*************************************************/
char* _modStale(char* ptr,char* ptr2)
{
	printf("RESET\n");
	counter++;
	return operationConst(ptr,ptr2,5);
}
void _fastMod(int adres1,int adres2,int adresTMP)
{

	int tmp1=adresTMP+1;
	int reszta=tmp1+1;
	int tmpr=reszta+1;
	int licznik=tmpr+1;
	
	printf("RESET \n");
	counter++;
	printf("STORE %d\n",licznik);
	counter++;
	printf("STORE %d\n",reszta);
	counter++;
	/*** sprawdzamy czy zero **6*/
	printf("LOAD %d\n",adres1);
	counter++;
	printf("STORE %d\n",tmp1);
	counter++;
	printf("JZERO %d\n",counter+92);
	counter++;
	printf("LOAD %d\n",adres2);
	counter++;
	printf("JZERO %d\n",counter+90);
	counter++;
	/***** szukamy pierwszej jedynki ***12**/
	int	petla=counter;
	printf("LOAD %d\n",tmp1);
	counter++;
	printf("JODD %d\n",counter+8);
	counter++;
	printf("SHR %d\n",jedynka);
	counter++;
	printf("STORE %d\n",tmp1);
	counter++;
	printf("LOAD %d\n",licznik);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("INC \n");
	counter++;
	printf("STORE %d\n",licznik);
	counter++;
	printf("JUMP %d\n",petla);
	/************znalazlem *********9*****/
	counter++;
	printf("SHR %d\n",jedynka);
	counter++;
	printf("STORE %d\n",tmp1);
	counter++;
	printf("RESET \n");
	counter++;
	printf("INC \n");
	counter++;
	printf("STORE %d\n",tmpr);
	counter++;
	printf("LOAD %d\n",licznik);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("INC \n");
	counter++;
	printf("STORE %d\n",licznik);
	/***pozostala czesc odwrotnosc*****13********/
	counter++;
	int petla2=counter;
	printf("LOAD %d\n",tmp1);
	counter++;
	printf("JZERO %d\n",counter+23);
	counter++;
	printf("JODD %d\n",counter+11);
	counter++;
	printf("SHR %d\n",jedynka);
	counter++;
	printf("STORE %d\n",tmp1);
	counter++;
	printf("LOAD %d\n",tmpr);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("STORE %d\n",tmpr);
	counter++;
	printf("LOAD %d\n",licznik);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("INC \n");
	counter++;
	printf("STORE %d\n",licznik);
	counter++;
	printf("JUMP %d\n",petla2);
	/********************************11**********/
	counter++;
	printf("SHR %d\n",jedynka);
	counter++;
	printf("STORE %d\n",tmp1);
	counter++;
	printf("LOAD %d\n",tmpr);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("INC \n");
	counter++;
	printf("STORE %d\n",tmpr);
	counter++;
	printf("LOAD %d\n",licznik);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("INC \n");
	counter++;
	printf("STORE %d\n",licznik);
	counter++;
	printf("JUMP %d\n",petla2);
	/*************zwiekszamy ilosc bitow licznika o 1****************4******/
	counter++;
	printf("LOAD %d\n",licznik);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("INC \n");
	counter++;
	printf("STORE %d\n",licznik);
	/*************dzielimy **********1**************/
	counter++;
	printf("RESET \n");
	/**********sciagamy flage przeniesienia ***9***/
	counter++;
	petla2=counter;
	printf("JZERO %d\n",counter+6);
	counter++;
	printf("LOAD %d\n",tmp1);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("INC\n");
	counter++;
	printf("STORE %d\n",tmp1);
	counter++;
	printf("JUMP %d\n",counter+4);
	counter++;
	printf("LOAD %d\n",tmp1);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("STORE %d\n",tmp1);
	/******** sprawdzamy warunek konca ***4***///
	counter++;
	printf("LOAD %d\n",licznik);
	counter++;
	printf("SHR %d\n",jedynka);
	counter++;
	printf("JZERO %d\n",counter+28);
	counter++;
	printf("STORE %d\n",licznik);
	/**przesowamy dzielna i reszte ***14*/
	counter++;
	printf("LOAD %d\n",tmpr);
	counter++;
	printf("JODD %d\n",counter+7);
	counter++;
	printf("SHR %d\n",jedynka);
	counter++;
	printf("STORE %d\n",tmpr);
	counter++;
	printf("LOAD %d\n",reszta);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("STORE %d\n",reszta);
	counter++;
	printf("JUMP %d\n",counter+7);
	counter++;
	printf("SHR %d\n",jedynka);
	counter++;
	printf("STORE %d\n",tmpr);
	counter++;
	printf("LOAD %d\n",reszta);
	counter++;
	printf("SHL %d\n",jedynka);
	counter++;
	printf("INC\n");
	counter++;
	printf("STORE %d\n",reszta);
	/************** sprawdzamy czy cos zostaje by dopisad do reszty**********12**********/
	counter++;
	printf("JZERO %d\n",counter+10);
	counter++;
	printf("SUB %d\n",adres2);
	counter++;
	printf("JZERO %d\n",counter+5);
	counter++;
	printf("STORE %d\n",reszta);
	counter++;
	printf("RESET \n");
	counter++;
	printf("INC\n");
	counter++;
	printf("JUMP %d\n",petla2);
	counter++;
	printf("LOAD %d\n",adres2);
	counter++;
	printf("SUB %d\n",reszta);
	counter++;
	printf("JZERO %d\n",counter-6);
	counter++;
	printf("RESET \n");
	counter++;
	printf("JUMP %d\n",petla2);
	counter++;
	/*************wczytujemy wynik*********************/
	printf("LOAD %d\n",reszta);
	counter++;
	printf("JUMP %d\n",counter+2);
	counter++;
	printf("RESET \n");
	counter++;

}
void _modStala_Zmienna(char *value,int adres,int ad)
{
	printf("RESET \n");
	counter++;
	int adres2=ad+1;
	_Assign(value,adres,adres2);

}
/**10*/
void _EQ(int adres1,int adres2)
{
	printf("LOAD %d\n",adres1);
	counter++;
	printf("SUB %d\n",adres2);
	counter++;
	printf("JZERO %d\n",counter+2);
	counter++;
	printf("JUMP %d\n",counter+4);
	counter++;
	printf("LOAD %d\n",adres2);
	counter++;
	printf("SUB %d\n",adres1);
	counter++;
	printf("JZERO %d\n",counter+3);
	counter++;
	printf("RESET \n");
	counter++;
	printf("JUMP %d\n",counter+2);
	counter++;
	printf("INC \n");
	counter++;
}
/**10*/
void _NEQ(int adres1,int adres2)
{
	printf("LOAD %d\n",adres1);
	counter++;
	printf("SUB %d\n",adres2);
	counter++;
	printf("JZERO %d\n",counter+2);
	counter++;
	printf("JUMP %d\n",counter+4);
	counter++;
	printf("LOAD %d\n",adres2);
	counter++;
	printf("SUB %d\n",adres1);
	counter++;
	printf("JZERO %d\n",counter+2);
	counter++;
	printf("INC \n");
	counter++;
	printf("JUMP %d\n",counter+2);
	counter++;
	printf("RESET \n");
	counter++;
}
/**4*/
void _GE(int adres1,int adres2)
{
	printf("LOAD %d\n",adres1);
	counter++;
	printf("SUB %d\n",adres2);
	counter++;
	printf("JZERO %d\n",counter+2);
	counter++;
	printf("INC \n");
	counter++;
}
void _LE(int adres1,int adres2)
{
	_GE(adres2,adres1);
}
/**10*/
void _GEQ(int adres1,int adres2)
{
	printf("LOAD %d\n",adres1);
	counter++;
	printf("SUB %d\n",adres2);
	counter++;
	printf("JZERO %d\n",counter+2);
	counter++;
	printf("JUMP %d\n",counter+6);
	counter++;
	printf("LOAD %d\n",adres2);
	counter++;
	printf("SUB %d\n",adres1);
	counter++;
	printf("JZERO %d\n",counter+3);
	counter++;
	printf("RESET \n");
	counter++;
	printf("JUMP %d\n",counter+2);
	counter++;
	printf("INC \n");
	counter++;
}
void _LEQ(int adres1,int adres2)
{
	_GEQ(adres2,adres1);
}
void _WHILE(struct ast_while_node *v,int adres)
{
	struct ast_node * condition=v->condition;

	struct ast_node * while_branch=v->while_branch;
	
	
	int etykietaCond=counter;
	
	_OPERATE(condition,adres);
	
	int etykietaif=counter;
	count(while_branch,adres);
	printf("JZERO %d\n",counter+2);
	counter++;
	counter=etykietaif+1;
	preorder(while_branch,adres);
	printf("JUMP %d\n",etykietaCond);
	counter++;

}
void _IF(struct ast_if_node *v,int adres)
{
	struct ast_node * condition=v->condition;

	struct ast_node * if_branch=v->if_branch;

	struct ast_node * else_branch=v->else_branch;
	
	
	_OPERATE(condition,adres);
	int etykietaif=counter;
	int koniecIF;
	if(else_branch)
		koniecIF=2;	else	koniecIF=1;
		
	count(if_branch,adres);
	printf("JZERO %d\n",counter+koniecIF);
	counter++;
	counter=etykietaif+1;
	preorder(if_branch,adres);
	if(else_branch){
		etykietaif=counter;
		count(else_branch,adres);
		printf("JUMP %d\n",counter+1);
		counter++;
		counter=etykietaif+1;
		preorder(else_branch,adres);
	}
	
}
void _OPERATE(struct ast_equality_node *operate,int adres)
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
			_EQ(symb->adres,symb2->adres);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='N')
		{	
			struct ast_number_node *num=(struct ast_number_node*)(leftCondition);
			struct ast_number_node *num2=(struct ast_number_node*)(rightCondition);
			if(compareNumbers(num->value,num2->value)==0)
			{
				printf("INC \n");
				counter++;
			}
			else{	printf("RESET \n");
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
			printf("RESET\n");
			counter++;
			_Assign(num2->value,tmp1,tmp2);
			printf("STORE %d\n",tmp1);
			counter++;
			_EQ(tmp1,symb->adres);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(rightCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_number_node *num2=(struct ast_number_node*)(leftCondition);
			int tmp1=adres+1;
			int tmp2=adres+2;
			printf("RESET\n");
			counter++;
			_Assign(num2->value,tmp1,tmp2);
			printf("STORE %d\n",tmp1);
			counter++;
			_EQ(tmp1,symb->adres);
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
			_NEQ(symb->adres,symb2->adres);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='N')
		{	
			struct ast_number_node *num=(struct ast_number_node*)(leftCondition);
			struct ast_number_node *num2=(struct ast_number_node*)(rightCondition);
			if(compareNumbers(num->value,num2->value)!=0)
			{
				printf("INC \n");
				counter++;
			}
			else{	printf("RESET \n");
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
			printf("RESET\n");
			counter++;
			_Assign(num2->value,tmp1,tmp2);
			printf("STORE %d\n",tmp1);
			counter++;
			_NEQ(tmp1,symb->adres);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(rightCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_number_node *num2=(struct ast_number_node*)(leftCondition);
			int tmp1=adres+1;
			int tmp2=adres+2;
			printf("RESET\n");
			counter++;
			_Assign(num2->value,tmp1,tmp2);
			printf("STORE %d\n",tmp1);
			counter++;
			_NEQ(tmp1,symb->adres);
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
			_LE(symb->adres,symb2->adres);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='N')
		{	
			struct ast_number_node *num=(struct ast_number_node*)(leftCondition);
			struct ast_number_node *num2=(struct ast_number_node*)(rightCondition);
			if(compareNumbers(num->value,num2->value)<0)
			{
				printf("INC \n");
				counter++;
			}
			else{	printf("RESET \n");
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
			printf("RESET\n");
			counter++;
			_Assign(num2->value,tmp1,tmp2);
			printf("STORE %d\n",tmp1);
			counter++;
			_LE(symb->adres,tmp1);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(rightCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_number_node *num2=(struct ast_number_node*)(leftCondition);
			int tmp1=adres+1;
			int tmp2=adres+2;
			printf("RESET\n");
			counter++;
			_Assign(num2->value,tmp1,tmp2);
			printf("STORE %d\n",tmp1);
			counter++;
			_LE(tmp1,symb->adres);
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
			_GE(symb->adres,symb2->adres);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='N')
		{	
			struct ast_number_node *num=(struct ast_number_node*)(leftCondition);
			struct ast_number_node *num2=(struct ast_number_node*)(rightCondition);
			if(compareNumbers(num->value,num2->value)>0)
			{
				printf("INC \n");
				counter++;
			}
			else{	printf("RESET \n");
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
			printf("RESET\n");
			counter++;
			_Assign(num2->value,tmp1,tmp2);
			printf("STORE %d\n",tmp1);
			counter++;
			_GE(symb->adres,tmp1);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(rightCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_number_node *num2=(struct ast_number_node*)(leftCondition);
			int tmp1=adres+1;
			int tmp2=adres+2;
			printf("RESET\n");
			counter++;
			_Assign(num2->value,tmp1,tmp2);
			printf("STORE %d\n",tmp1);
			counter++;
			_GE(tmp1,symb->adres);
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
			_LEQ(symb->adres,symb2->adres);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='N')
		{	
			struct ast_number_node *num=(struct ast_number_node*)(leftCondition);
			struct ast_number_node *num2=(struct ast_number_node*)(rightCondition);
			if(compareNumbers(num->value,num2->value)==0||(compareNumbers(num->value,num2->value)<0))
			{
				printf("INC \n");
				counter++;
			}
			else{	printf("RESET \n");
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
			printf("RESET\n");
			counter++;
			_Assign(num2->value,tmp1,tmp2);
			printf("STORE %d\n",tmp1);
			counter++;
			_LEQ(symb->adres,tmp1);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(rightCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_number_node *num2=(struct ast_number_node*)(leftCondition);
			int tmp1=adres+1;
			int tmp2=adres+2;
			printf("RESET\n");
			counter++;
			_Assign(num2->value,tmp1,tmp2);
			printf("STORE %d\n",tmp1);
			counter++;
			_LEQ(tmp1,symb->adres);
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
			_GEQ(symb->adres,symb2->adres);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='N')
		{	
			struct ast_number_node *num=(struct ast_number_node*)(leftCondition);
			struct ast_number_node *num2=(struct ast_number_node*)(rightCondition);
			if(compareNumbers(num->value,num2->value)==0||(compareNumbers(num->value,num2->value)>0))
			{
				printf("INC \n");
				counter++;
			}
			else{	printf("RESET \n");
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
			printf("RESET\n");
			counter++;
			_Assign(num2->value,tmp1,tmp2);
			printf("STORE %d\n",tmp1);
			counter++;
			_GEQ(symb->adres,tmp1);
		}
		else if(leftCondition->node_type=='N'&&rightCondition->node_type=='S')
		{	
			struct ast_symbol_reference_node* tmp=(struct ast_symbol_reference_node *)(rightCondition);
			struct symbol_node* symb=(struct symbol_node *)(tmp->symbol);
			struct ast_number_node *num2=(struct ast_number_node*)(leftCondition);
			int tmp1=adres+1;
			int tmp2=adres+2;
			printf("RESET\n");
			counter++;
			_Assign(num2->value,tmp1,tmp2);
			printf("STORE %d\n",tmp1);
			counter++;
			_GEQ(tmp1,symb->adres);
		}
	}
}


