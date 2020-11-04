#include "tableLex.h"
#include "stdio.h"

int main () {
    lexeme *tl = initTableLex();
    hashTable ht = initHashTable();
    int l = 0;

    addLex(tl, &l, ht, "test1");
    addLex(tl, &l, ht, "test2");
    addLex(tl, &l, ht, "test3");
    addLex(tl, &l, ht, "test4");

    printf("longueur: %d\n", l);
    printf("lex 4: %s\n", getLex(tl, &l, 3).lexeme);
    printf("num 'test3': %d\n", getLexNum(tl, ht, "test3"));

    exit(EXIT_SUCCESS);
}