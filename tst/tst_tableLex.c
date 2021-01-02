#include "tableLex.h"
#include "stdio.h"

int main () {
    FILE *f;

    tl_init();

    tl_ajout("test1");
    tl_ajout("test2");
    tl_ajout("test3");
    tl_ajout("test4");

    printf("longueur: %d\n", tl_longTabLex());
    printf("lex 4: %s\n", tl_getLex(3));
    printf("num 'test3': %d\n", tl_getLexNum("test3"));
    printf("'test2' existe?: %d\n", tl_existe("test2"));
    printf("'test5' existe?: %d\n", tl_existe("test5"));

    tl_afficher();

    f = fopen("obj/tabLexInter.txt", "a+");
    tl_ecrireFichier(f);
    fclose(f);

    tl_detruire();

    exit(EXIT_SUCCESS);
}