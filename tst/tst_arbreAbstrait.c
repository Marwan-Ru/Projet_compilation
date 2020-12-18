#include "arbreAbstrait.h"
#include <stdio.h>

int main () {
    arbre a, b, c;

    a = creerNoeud(A_OPAFF, -1);
    b = creerNoeud(A_IDF, 6); /* numlex */
    c = creerNoeud(A_CSTE_CAR, '2');

    concatPereFrere(&b, &c);
    concatPereFils(&a, &b);

    printf("a (%p): id=%2d val=%2d frere=%14p fils=%14p\n", (void *)&a, a.id, a.valeur, (void *)a.frere, (void *)a.fils);
    printf("b (%p): id=%2d val=%2d frere=%14p fils=%14p\n", (void *)&b, b.id, b.valeur, (void *)b.frere, (void *)b.fils);
    printf("c (%p): id=%2d val=%2d frere=%14p fils=%14p\n", (void *)&c, c.id, c.valeur, (void *)c.frere, (void *)c.fils);

    exit(EXIT_SUCCESS);
}