0. interpreter.cc - program interpretujacy interpretujacy dany asembler.
1. Projekt kompilator -Języki formalne i teoria translacji 
2. Do uruchomienia kompilatora niezbędna jest biblioteka GMP do ściągnięcia z https://gmplib.org/ umożliwiająca obsługę dużych liczb
4. Idęą działania parsera, jest budowa drzewa AST na poziomie syntezy składniowej a następnie dokonywane jest wyprowadzenie 
za pomocą metody preorder() zawartej w pliku kompilator.y.
5. Kompilacja:
		a.)kompilujemy program za pomocą polecenia make. Utworzony zostaje plik wykonywalny ./kompilator
		b.)za pomocą strumienia wejściowego podajemy plik mający zostać przetłumaczony na maszynę rejestorwą 
			NP: ./kompilator < test 
		c.)za pomocą strumienia wyjściowego wypisujemy wynik do kolejnego pliku 
			NP: ./kompilator < test > binary
		d.)tak wygenerowany plik podajemy jako argument do interpretera 
			NP: ./interpreter.out binary
