#include "tableLex.h"
#include "stdio.h"

int main () {
    lexeme *tl = tl_init();
    hashTable ht = ht_init();
    int l = 0;

    tl_ajout(tl, &l, ht, "test1");
    tl_ajout(tl, &l, ht, "test2");
    tl_ajout(tl, &l, ht, "test3");
    tl_ajout(tl, &l, ht, "test4");

    printf("longueur: %d\n", l);
    printf("lex 4: %s\n", tl_getLex(tl, &l, 3).lexeme);
    printf("num 'test3': %d\n", tl_getLexNum(tl, ht, "test3"));
    printf("'test2' existe?: %d\n", tl_existe(tl, ht, "test2"));
    printf("'test5' existe?: %d\n", tl_existe(tl, ht, "test5"));

    tl_detruire(tl, ht);

    exit(EXIT_SUCCESS);
}