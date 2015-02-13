#include "aritmetic.h"
extern counter;
extern int jedynka;
void _Assign(char *tab,int adres,int adresTMP)
{
	
	mpz_t value1; 
	mpz_t value2;
	
	mpz_init (value1); 
	mpz_init (value2);
	
	mpz_set_str(value1,tab,10);
	mpz_set_str(value2,"0",10);
	
	if((mpz_cmp(value1,value2)==0))
	{
		 mpz_clear(value1);
		 mpz_clear(value2);
		printf("RESET\n");
		counter++;
		return ;
	}
	mpz_set_str(value2,"1",10);
	
	printf("RESET\n");
	counter++;
	
	if((mpz_cmp(value1,value2)==0))
	{
		 mpz_clear(value1);
		 mpz_clear(value2);
		printf("INC\n");
		counter++;
		return ;
	}
	mpz_set_str(value2,"13",10);
	
	
	if((mpz_cmp(value1,value2)<0))
	{
		mpz_t zero;
		mpz_init (zero); 
		mpz_set_str(zero,"0",10);
		mpz_set_str(value2,"1",10);
		while((mpz_cmp(zero,value1)))
		{
		mpz_sub(value1,value1,value2);
		printf("INC\n");
		counter++;
		}
		mpz_clear(value1);
		mpz_clear(value2);
		mpz_clear(zero);
		return ;
	}
	
	
	char *bits=toBit(tab);
	int i=1;
	printf("INC\n");
	counter++;
	for(i;bits[i]!=0;i++){
		printf("SHL %d\n",jedynka);
		counter++;
		if(bits[i]=='1')
			{
			printf("INC \n");
			counter++;
			}
		}
		
	free(bits);
	mpz_clear(value1);
	mpz_clear(value2);
		
}
char* toBit(char *tab)
{
	
	char *tyy;

	int i=0;
	
	mpz_t tmp;
	mpz_init (tmp);
	mpz_set_str(tmp,tab,10);
	
	mpz_t rr;
	mpz_init (rr);
	mpz_set_str(rr,"0",10);
	
	mpz_t dwa;
	mpz_init (dwa);
	mpz_set_str(dwa,"2",10);
	
	mpz_t zero;
	mpz_init (zero);
	mpz_set_str(zero,"0",10);
	
	while((mpz_cmp(zero,tmp))!=0)
	{
		mpz_fdiv_r(rr,tmp,dwa);
		mpz_fdiv_q(tmp,tmp,dwa);
		i++;
	}
	
	mpz_set_str(tmp,tab,10);
	
	char *temp=(char*)malloc((i * sizeof(char))+1);
	char *tempR=(char*)malloc((i * sizeof(char))+1);
	i=0;
	
	while((mpz_cmp(zero,tmp))!=0)
	{
		mpz_fdiv_r(rr,tmp,dwa);
		mpz_fdiv_q(tmp,tmp,dwa);
		if(mpz_cmp(rr,zero)==0)
			temp[i]='0';
		else
			temp[i]='1';
		i++;
	}
	temp[i]=0;
	
	int j=0;
	i--;
	for(j;i>=0;j++,i--){
	tempR[j]=temp[i];
	}
	tempR[j]=0;
	i=0;
	
	free(temp);
	
	mpz_clear(tmp);
	mpz_clear(rr);
	mpz_clear(zero);
	mpz_clear(dwa);
	
	return tempR;

}
void CountAssign(char *tab,int adres,int adresTMP)
{
	
	mpz_t value1; 
	mpz_t value2;
	
	mpz_init (value1); 
	mpz_init (value2);
	
	mpz_set_str(value1,tab,10);
	mpz_set_str(value2,"0",10);
	
	if((mpz_cmp(value1,value2)==0))
	{
		 mpz_clear(value1);
		 mpz_clear(value2);
		counter++;
		return ;
	}
	mpz_set_str(value2,"1",10);
	
	counter++;
	
	if((mpz_cmp(value1,value2)==0))
	{
		 mpz_clear(value1);
		 mpz_clear(value2);
		counter++;
		return ;
	}
	mpz_set_str(value2,"13",10);
	
	
	if((mpz_cmp(value1,value2)<0))
	{
		mpz_t zero;
		mpz_init (zero); 
		mpz_set_str(zero,"0",10);
		mpz_set_str(value2,"1",10);
		while((mpz_cmp(zero,value1)))
		{
		mpz_sub(value1,value1,value2);
		counter++;
		}
		mpz_clear(value1);
		mpz_clear(value2);
		mpz_clear(zero);
		return ;
	}
	
	
	char *bits=toBit(tab);
	int i=1;
	counter++;
	for(i;bits[i]!=0;i++){
		counter++;
		if(bits[i]=='1')
			{
			counter++;
			}
		}
		
	free(bits);
	mpz_clear(value1);
	mpz_clear(value2);
		
}
void loga2(mpz_t rop,const mpz_t val1)
{
	mpz_t jeden;
	mpz_t dwa;
	mpz_t bound;
		
	mpz_init (bound);
	mpz_init (dwa);
	mpz_init (jeden);
	
	mpz_set_str(bound,"1",10);
	mpz_set_str(rop,"0",10);
	mpz_set_str(jeden,"1",10);
	mpz_set_str(dwa,"2",10);
	
	while(mpz_cmp(bound,val1)<0||mpz_cmp(bound,val1)==0)
	{
		mpz_mul(bound,bound,dwa);
		mpz_add(rop,rop,jeden);
	}

	mpz_sub(rop,rop,jeden);
	
	mpz_clear(jeden);
	mpz_clear(bound);
	mpz_clear(dwa);
}

char* operationConst(char *ptr,char *ptr2,int operationTYPE)
{
	
	if((operationTYPE==3 ||operationTYPE==4||operationTYPE==5)&&(*ptr=='0'||*ptr2=='0'))
		return "0";
	
	mpz_t value1; 
	mpz_t value2;
	mpz_t result;
	mpz_init (value1); 
	mpz_init (value2);
	mpz_init (result);
	
	mpz_set_str(value1,ptr,10);
	mpz_set_str(value2,ptr2,10);
	
	if((operationTYPE==2)&&(mpz_cmp(value1,value2)<=0))
		return "0";
	
	switch(operationTYPE){
	case 1:
		mpz_add(result,value1,value2);
		break;
	case 2:
		mpz_sub(result,value1,value2);
		break;
	case 3:
		mpz_mul(result,value1,value2);
		break;
	case 4:
		mpz_cdiv_q(result,value1,value2);
		break;
	case 5:
		mpz_mod(result,value1,value2);
		break;
	default:
		return "0" ;
	}


	
	char *ptrOut=mpz_get_str(NULL,10,result);
	
	 mpz_clear(value1);
	 mpz_clear(value2);
	 mpz_clear(result);
	 
	// printf("%s\n",ptrOut);
	return ptrOut;

}
int compareNumbers(char *ptr1,char *ptr2)
{
	mpz_t value1; 
	mpz_t value2;
	mpz_init (value1); 
	mpz_init (value2);
	
	mpz_set_str(value1,ptr1,10);
	mpz_set_str(value2,ptr2,10);
	int result=mpz_cmp(value1,value2);
	mpz_clear(value1);
	mpz_clear(value2);
	
	return result;

}
