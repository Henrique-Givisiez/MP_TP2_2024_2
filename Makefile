all: testa_conta_palavra.cpp   conta_palavra.c conta_palavra.h conta_palavra.o
	g++ -std=c++11 -Wall conta_palavra.o testa_conta_palavra.cpp -o testa_conta_palavra.exe
	./testa_conta_palavra.exe

compile: testa_conta_palavra.cpp   conta_palavra.c conta_palavra.h conta_palavra.o
	g++ -std=c++11 -Wall conta_palavra.o testa_conta_palavra.cpp -o testa_conta_palavra.exe

conta_palavra.o : conta_palavra.c conta_palavra.h
	g++ -std=c++11 -Wall -c conta_palavra.c
	
testa_conta_palavra: 	testa_conta_palavra.cpp   conta_palavra.c conta_palavra.h conta_palavra.o
	g++ -std=c++11 -Wall conta_palavra.o testa_conta_palavra.cpp -o testa_conta_palavra.exe
	
test: testa_conta_palavra	
	./testa_conta_palavra.exe
	
cpplint: testa_conta_palavra.cpp   conta_palavra.c conta_palavra.h
	cpplint   --exclude=catch.hpp  *.*
	
gcov: testa_conta_palavra.cpp   conta_palavra.c conta_palavra.h 
	g++ -std=c++11 -Wall -fprofile-arcs -ftest-coverage -c conta_palavra.c
	g++ -std=c++11 -Wall -fprofile-arcs -ftest-coverage conta_palavra.o testa_conta_palavra.cpp -o testa_conta_palavra.exe
	./testa_conta_palavra.exe
	gcov *.cpp	
	 
debug: testa_conta_palavra.cpp   conta_palavra.c conta_palavra.h 
	g++ -std=c++11 -Wall -g -c conta_palavra.c
	g++ -std=c++11 -Wall  -g conta_palavra.o testa_conta_palavra.cpp -o testa_conta_palavra
	gdb testa_conta_palavra.exe
	
	
cppcheck: testa_conta_palavra.cpp   conta_palavra.c conta_palavra.h
	cppcheck  --enable=warning .

valgrind: testa_conta_palavra
	valgrind --leak-check=yes --log-file=valgrind.rpt ./testa_conta_palavra.exe


clean:
	rm -rf *.o *.exe *.gc* *.rpt
	
	
