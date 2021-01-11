#include "arbreAbstrait.h"
#include <stdio.h>
#include <math.h>
#include "allocation.h"

int main () {
    FILE *f;

    arbre a = aa_vide(), 
          b = aa_vide(), 
          c = aa_vide();

    a = aa_creerNoeud(A_OPAFF, -1);
    b = aa_creerNoeud(A_IDF, 6); /* numlex */
    c = aa_creerNoeud(A_CSTE_CAR, '2');

    aa_concatPereFrere(b, c);
    aa_concatPereFils(a, b);

    printf("a (%p): id=%2d val=%2d frere=%14p fils=%14p\n", (void *)a, a->id, a->valeur, (void *)a->frere, (void *)a->fils);
    printf("b (%p): id=%2d val=%2d frere=%14p fils=%14p\n", (void *)b, b->id, b->valeur, (void *)b->frere, (void *)b->fils);
    printf("c (%p): id=%2d val=%2d frere=%14p fils=%14p\n\n", (void *)c, c->id, c->valeur, (void *)c->frere, (void *)c->fils);

    aa_afficher(a);

    f = fopen("obj/arbreAbstrait.txt", "a");
    aa_ecrireFichier(f, a);
    fclose(f);
    
    aa_detruire_rec(a);

    exit(EXIT_SUCCESS);
}