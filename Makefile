CC = @gcc -Wall

inst : clean inst.tab.c lex.yy.o 
	$(CC) -DYYDEBUG=1 -o inst inst.tab.c lex.yy.o -lfl

lex.yy.o : lex.yy.c inst.tab.h  

inst.tab.c : inst.y
	@bison -d -v inst.y

lex.yy.c : inst.l
	@flex inst.l

clean:
	@rm -f *.c *.h *.o
