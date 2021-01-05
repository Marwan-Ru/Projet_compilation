#include "tabledecl.h"
#include <stdio.h>

int main(){

    td_init();
    tl_init();

    tl_ajout("test1");
    tl_ajout("test2");
    tl_ajout("test3");
    tl_ajout("test4");

    /* On va tester l'ajout dans a table de declaration */
    td_ajout(TYPE_S, "test1", 1, 1, sizeof(int));
    
    td_ajout(TYPE_S, "test1", 1, 1, sizeof(int) * 2);

    td_affiche();

    exit(0);
}