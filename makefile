mycomp: mycomp.o complex.o syntaxhandle.o syntaxhandle.h complex.h mycomp.h
	gcc -g -Wall -ansi -pedantic -std=c90 mycomp.o complex.o syntaxhandle.o -o mycomp -lm

mycomp.o: mycomp.c complex.h mycomp.h syntaxhandle.c syntaxhandle.h
	gcc -c -Wall -ansi -pedantic -std=c90 mycomp.c -o mycomp.o -lm

complex.o: complex.c complex.h
	gcc -c -Wall -ansi -pedantic -std=c90 complex.c -o complex.o -lm

syntaxhandle.o: syntaxhandle.c syntaxhandle.h
	gcc -c -Wall -ansi -pedantic -std=c90 syntaxhandle.c -o syntaxhandle.o -lm
