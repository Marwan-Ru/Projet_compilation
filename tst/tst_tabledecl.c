#include "tabledecl.h"
#include <stdio.h>

int main(){
    int n;
    decl d;

    td_init();
    tl_init();

    tl_ajout("test1");
    tl_ajout("test2");
    tl_ajout("test3");
    tl_ajout("test4");

    /* On va tester l'ajout dans a table de declaration */
    td_ajout(TYPE_S, "test1", 1, 1, sizeof(int));
    n = td_getlastdeclnum("test1");
    td_ajout(TYPE_S, "test1", 1, 1, sizeof(int) * 2);

    d = td_getdecl(n);
    printf("nature %d, suivant %d, numregion %d, index %d, exec %d\n", d.NATURE, d.suivant, d.numregion, d.index, d.exec);

    exit(0);
}