CC = gcc -Wall
LexYaccCible = inst

inste: LexYaccCible = inst
inste: lexyacc

decl: LexYaccCible = decl
decl: lexyacc

lexyacc : clean $(LexYaccCible).tab.c lex.yy.o 
	$(CC) -DYYDEBUG=1 -o bin/$(LexYaccCible) obj/$(LexYaccCible).tab.c obj/lex.yy.o -lfl

lex.yy.o : obj/lex.yy.c obj/$(LexYaccCible).tab.h  

$(LexYaccCible).tab.c : src/$(LexYaccCible).y
	@bison -d -v src/$(LexYaccCible).y

lex.yy.c : src/$(LexYaccCible).l
	@flex src/$(LexYaccCible).l

clean:
	@rm -f *.c *.h *.o
