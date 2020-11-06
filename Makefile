CC = @gcc
CFLAGS = -Wall -ansi -pedantic-errors -O0 -I "inc" -g -fsanitize=address
CIBLELEXYACC=inst

inst : CIBLELEXYACC=inst
inst : lexyacc

decl : CIBLELEXYACC=decl
decl : lexyacc

lexyacc : cleanCIBLELexYacc $(CIBLELEXYACC).tab.c lex.yy.o 
	$(CC) -Wall -DYYDEBUG=1 -o bin/$(CIBLELEXYACC) obj/$(CIBLELEXYACC).tab.c obj/lex.yy.o -lfl

lex.yy.o : lex.yy.c
	$(CC) -Wall -c -o obj/lex.yy.o obj/lex.yy.c

$(CIBLELEXYACC).tab.c : src/LexYacc/$(CIBLELEXYACC)/$(CIBLELEXYACC).y
	@bison -d -v src/LexYacc/$(CIBLELEXYACC)/$(CIBLELEXYACC).y -b obj/$(CIBLELEXYACC)

lex.yy.c : src/LexYacc/$(CIBLELEXYACC)/$(CIBLELEXYACC).l
	@flex -o obj/lex.yy.c src/LexYacc/$(CIBLELEXYACC)/$(CIBLELEXYACC).l

cleanCIBLELexYacc :
	@rm -f bin/$(CIBLELEXYACC) obj/*
	@mkdir -p obj
	@mkdir -p bin




tst_liste : clean obj/tst_liste.o obj/liste.o obj/allocation.o
	$(CC) $(CFLAGS) -o bin/tst_liste $(wildcard obj/*.o)

tst_tabLex : clean obj/tst_tabLex.o obj/tableLex.o obj/allocation.o
	$(CC) $(CFLAGS) -o bin/tst_tabLex $(wildcard obj/*.o)

tst_tabTypes : clean obj/tst_tabTypes.o obj/tableTypes.o obj/allocation.o
	$(CC) $(CFLAGS) -o bin/tst_tabTypes $(wildcard obj/*.o)

obj/tst_%.o: tst/tst_%.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o : src/tables/%.c inc/%.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -f bin/* obj/*
	@mkdir -p obj
	@mkdir -p bin
