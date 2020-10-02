CC = gcc -Wall

inst : inst.tab.c lex.yy.o 
	gcc -o inst inst.tab.c lex.yy.o -ll

lex.yy.o : lex.yy.c inst.tab.h  

inst.tab.c : inst.y
	bison -d -v inst.y

lex.yy.c : inst.l
	flex inst.l

clean:
	rm *.c *.h *.o