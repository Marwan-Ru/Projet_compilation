#include "tabledecl.h"
#include <stdio.h>

int main(){

    td_init();
    tl_init();

    tl_ajout("test1");
    tl_ajout("test2");
    tl_ajout("test3");
    tl_ajout("test4");

    /* On va tester le calcul du decalage des variables dans la table de declaration */
    td_ajout(tl_getLexNum("test1"), TYPE_S, 0, 0, 3);
    td_ajout(tl_getLexNum("test1"), VARI, 0, 4, 0);
    td_ajout(tl_getLexNum("test2"), VARI, 0, 4, 0);

    td_afficher();

    exit(0);
}