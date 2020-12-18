CC = @gcc
CFLAGS = -Wall -ansi -pedantic-errors -O0 -I "inc" -g
CIBLELEXYACC = main


main : CIBLELEXYACC=main
main : lexyacc

inst : CIBLELEXYACC=inst
inst : lexyacc

decl : CIBLELEXYACC=decl
decl : lexyacc

lexyacc : cleanTarget $(CIBLELEXYACC).tab.c lex.yy.o obj/tableLex.o obj/tablereg.o obj/allocation.o
	$(CC) -Wall -DYYDEBUG=1 -I "inc" -o bin/$(CIBLELEXYACC) obj/$(CIBLELEXYACC).tab.c $(wildcard obj/*.o) -ly -lfl

lex.yy.o : lex.yy.c
	$(CC) -Wall -c -o obj/lex.yy.o obj/lex.yy.c

$(CIBLELEXYACC).tab.c : src/LexYacc/$(CIBLELEXYACC)/$(CIBLELEXYACC).y
	@bison -d -v src/LexYacc/$(CIBLELEXYACC)/$(CIBLELEXYACC).y -b obj/$(CIBLELEXYACC)

lex.yy.c : src/LexYacc/$(CIBLELEXYACC)/$(CIBLELEXYACC).l
	@flex -o obj/lex.yy.c src/LexYacc/$(CIBLELEXYACC)/$(CIBLELEXYACC).l



tst_arbreAbstrait: cleanTarget obj/arbreAbstrait.o obj/tst_arbreAbstrait.o
	$(CC) $(CFLAGS) -o bin/tst_arbreAbstrait obj/arbreAbstrait.o obj/tst_arbreAbstrait.o

tst_% : cleanTarget obj/%.o obj/tst_%.o obj/allocation.o
	$(CC) $(CFLAGS) -o bin/$@ $(filter-out $<,$^)

obj/tst_%.o: tst/tst_%.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/table%.o : src/tables/table%.c inc/table%.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/arbre%.o : src/arbre/arbre%.c inc/arbre%.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o : src/%.c inc/%.h
	$(CC) $(CFLAGS) -c $< -o $@


cleanTarget:
	@rm -f obj/*
	@if [ "$(MAKECMDGOALS)" != "" ]; then\
		rm -f bin/$(MAKECMDGOALS);\
	else\
		rm -f bin/$(CIBLELEXYACC);\
	fi
	@mkdir -p obj
	@mkdir -p bin

clean: cleanTarget
	@rm -f bin/*
