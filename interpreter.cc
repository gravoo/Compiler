/*
 * Kod interpretera maszyny rejestrowej do projektu z JFTT2014s
 *
 * Autor: Maciek Gębala
 * http://mgc.im.pwr.wroc.pl/
 * 2014-11-17
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<map>

#include<stdlib.h> 	// rand()
#include<time.h>

using namespace std;

const int READ = 0;
const int WRITE = 1;
const int LOAD = 2;
const int STORE = 3;
const int ADD = 4;
const int SUB = 5;
const int SHR = 6;
const int SHL = 7;
const int INC = 8;
const int RESET = 9;
const int JUMP = 10;
const int JZERO = 11;
const int JODD = 12;
const int HALT = 13;

int main(int argc, char* argv[])
{
    vector< pair<int,int> > program;
    map<int,long long> pam;

    long long a;
    int lr;

    int k=0;
    long long i;
    int i1, i2;
    string com;

    if( argc!=2 )
    {
	cout << "Sposób użycia programu: interpreter kod" << endl;
	return -1;
    }

    cout << "Czytanie programu." << endl;
    ifstream plik( argv[1] );
    if( !plik )
    {
	cout << "Błąd: Nie można otworzyć pliku " << argv[1] << endl;
	return -1;
    }
    while( !plik.eof() )
    {
	plik >> com;
	i1 = -1;
	if( com=="READ"  ) { i1 = READ;
			   }
	if( com=="WRITE" ) { i1 = WRITE;
			   }

	if( com=="LOAD"  ) { i1 = LOAD; plik >> i2;
			     if(i2<0) { cout << "Błąd: zły adress w instrukcji " << k << endl; return -1; }
			   }
	if( com=="STORE" ) { i1 = STORE; plik >> i2;
			     if(i2<0) { cout << "Błąd: zły adress w instrukcji " << k << endl; return -1; }
			   }

	if( com=="ADD"   ) { i1 = ADD; plik >> i2;
			     if(i2<0) { cout << "Błąd: zły adress w instrukcji " << k << endl; return -1; }
			   }
	if( com=="SUB"   ) { i1 = SUB; plik >> i2;
			     if(i2<0) { cout << "Błąd: zły adress w instrukcji " << k << endl; return -1; }
			   }

	if( com=="SHR"   ) { i1 = SHR; plik >> i2;
			     if(i2<0) { cout << "Błąd: zły adress w instrukcji " << k << endl; return -1; }
			   }
	if( com=="SHL"   ) { i1 = SHL; plik >> i2;
			     if(i2<0) { cout << "Błąd: zły adress w instrukcji " << k << endl; return -1; }
			   }
	if( com=="INC"   ) { i1 = INC; i2 = 0;
			   }
	if( com=="RESET"  ) { i1 = RESET; i2 = 0;
			   }

	if( com=="JUMP"  ) { i1 = JUMP; plik >> i2;
			     if(i2<0) { cout << "Błąd: zły adress w instrukcji " << k << endl; return -1; }
			   }
	if( com=="JZERO"    ) { i1 = JZERO; plik >> i2;
			     if(i2<0) { cout << "Błąd: zły adress w instrukcji " << k << endl; return -1; }
			   }
	if( com=="JODD"  ) { i1 = JODD; plik >> i2;
			     if(i2<0) { cout << "Błąd: zły adress w instrukcji " << k << endl; return -1; }
			   }

	if( com=="HALT"  ) { i1 = HALT; i2 = 0;
                           }
	if( i1==-1 )
	{
	    cout << "Błąd: Nieznana instrukcja w linii " << program.size()+1 << "." << endl;
	    return -1;
	}

	if( plik.good() )
	{
	    pair<int,int> temp(i1,i2);
	    program.push_back( temp );
	}
	k++;
    }
    plik.close();
    cout << "Skończono czytanie programu (linii: " << program.size() << ")." << endl;

    cout << "Uruchamianie programu." << endl;
    lr = 0;
    srand(time(NULL));
    a = rand();
    i = 0;
    while( program[lr].first!=HALT )	// HALT
    {
	switch( program[lr].first )
	{
	    case READ:	cout << "? "; cin >> a; i+=100; lr++; break;
	    case WRITE:	cout << "> " << a << endl; i+=100; lr++; break;

	    case LOAD:	a=pam[program[lr].second]; i+=10; lr++; break;
	    case STORE:	pam[program[lr].second]=a; i+=10; lr++; break;

	    case ADD:	a+=pam[program[lr].second]; i+=30; lr++; break;
	    case SUB:	a-=pam[program[lr].second]; if( a<0 ) a=0; i+=30; lr++; break;
	    case SHR:   a>>=pam[program[lr].second]; i+=12; lr++; break;
	    case SHL:   a<<=pam[program[lr].second]; i+=12; lr++; break;

	    case INC:	a++; i++; lr++; break;
	    case RESET:	a=0; i++; lr++; break;

	    case JUMP: 	lr = program[lr].second; i++; break;
	    case JZERO:	if( a==0 ) lr = program[lr].second; else lr++; i++; break;
	    case JODD:	if( a%2!=0 ) lr = program[lr].second; else lr++; i++; break;
	}
	if( lr<0 || lr>=(int)program.size() )
	{
	    cout << "Błąd: Wywołanie nieistniejącej instrukcji nr " << lr << "." << endl;
	    return -1;
	}

    }
    cout << "Skończono program (wykonano kroków: " << i << ")." << endl;

    return 0;
}
