#include "arbreAbstrait.h"
#include <stdio.h>
#include <math.h>
#include "allocation.h"

int main () {
    int **tabVal, hauteur, maxNoeud, i;

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

    hauteur = aa_hauteur(a);
    maxNoeud = pow(2, hauteur) - 1;
    tabVal = allocation_mem(maxNoeud, sizeof(int *));

    for (i = 0; i < maxNoeud; i++) {
        tabVal[i] = allocation_mem(2, sizeof(int));
    }

    aa_arbreVersTableau(a, tabVal, maxNoeud);

    printf("\nArbre vers tableau : \n");
    for (i = 0; i < maxNoeud; i++) {
        printf("{%d, %d} ", tabVal[i][0], tabVal[i][1]);
    }
    printf("\n\nTableau vers arbre : \n");

    aa_detruire_rec(a);

    a = aa_tableauVersArbre(tabVal, maxNoeud);
    aa_afficher(a);
    
    aa_detruire_rec(a);
    for (i = 0; i < maxNoeud; i++) {
        libere_mem(&(tabVal[i]));
    }
    libere_mem(&tabVal);

    exit(EXIT_SUCCESS);
}