kompilator: kompilator.y kompilator.l aritmetic.c parser.c
	bison -d kompilator.y
	flex kompilator.l
	gcc -o  kompilator lex.yy.c  kompilator.tab.c aritmetic.c parser.c counter.c AST.c -lgmp -w
	
