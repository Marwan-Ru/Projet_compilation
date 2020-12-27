#include "tabledecl.h"
#include <stdio.h>

int main(){
    int n;


    td_init();
    tl_init();

    tl_ajout("test1");
    tl_ajout("test2");
    tl_ajout("test3");
    tl_ajout("test4");

    /* On va tester l'ajout dans a table de declaration */
    td_ajout(TYPE_S, "test1", 1, 1, sizeof(int));
    n = td_getlastdeclnum("pipi");
    td_ajout(TYPE_S, "test1", 1, 1, sizeof(int) * 2);

    printf("nature %d, suivant %d, numregion %d, index %d, exec %d\n", tabledecl[n].NATURE, tabledecl[n].suivant, tabledecl[n].numregion, tabledecl[n].index, tabledecl[n].exec);

    exit(0);
}