#include "arbreAbstrait.h"
#include <stdio.h>

int main () {
    arbre a, b, c, tmp;
	int *entier;
	float *reel;
	char *caractere;

    entier = allocation_mem(1, sizeof(int));
    *entier = 22;

    reel = allocation_mem(1, sizeof(float));
    *reel = 2345.345544;

    caractere = allocation_mem(1, sizeof(char));
    *caractere = 'B';
    
    a = aa_creerVide();
    printf("Arbre a vide ? %d\n", aa_estVide(a));

    a = aa_creerFeuille(A_VIDE, "test");
    printf("Arbre a: Vide? %d, Fils?: %d, Frère?: %d, id: %d, donnée: %s\n", 
            aa_estVide(a), aa_estVide(aa_getFils(a)), aa_estVide(aa_getFrere(a)), 
            aa_idCellule(aa_getRacine(a)), (char *) aa_donneesCellule(aa_getRacine(a)));

    /* On doit manuellement libérer la cellule lorsqu'elle contient une chaine de caractères
       définie sur la pile */
    libere_mem(&(a->val));
    aa_detruire(a, 0);
    a = aa_creerFeuille(A_CSTE_REELE, reel);
    printf("Arbre a: Vide? %d, Fils?: %d, Frère?: %d, id: %d, donnée: %f\n", 
            aa_estVide(a), aa_estVide(aa_getFils(a)), aa_estVide(aa_getFrere(a)), 
            aa_idCellule(aa_getRacine(a)), *(float *) aa_donneesCellule(aa_getRacine(a)));

	b = aa_creerNoeud(A_IDF, caractere, NULL, a);
	c = aa_creerNoeud(A_OP_PLUS, NULL, b, NULL);

	printf("Arbre c: Vide? %d, Fils?: %d, Frère?: %d, id: %d, donnée: %p\n", 
            aa_estVide(c), aa_estVide(aa_getFils(c)), aa_estVide(aa_getFrere(c)), 
            aa_idCellule(aa_getRacine(c)), aa_donneesCellule(aa_getRacine(c)));
	
	tmp = aa_getFils(c);
	printf("fils(c): Vide? %d, Fils?: %d, Frère?: %d, id: %d, donnée: %c\n", 
            aa_estVide(tmp), aa_estVide(aa_getFils(tmp)), aa_estVide(aa_getFrere(tmp)), 
            aa_idCellule(aa_getRacine(tmp)), *(char *) aa_donneesCellule(aa_getRacine(tmp)));

	tmp = aa_getFrere(tmp);
	printf("frere(fils(c)): Vide? %d, Fils?: %d, Frère?: %d, id: %d, donnée: %f\n", 
            aa_estVide(tmp), aa_estVide(aa_getFils(tmp)), aa_estVide(aa_getFrere(tmp)), 
            aa_idCellule(aa_getRacine(tmp)), *(float *) aa_donneesCellule(aa_getRacine(tmp)));

	a = aa_detruire(a, 1);
	printf("Arbre a vide ? %d\n", aa_estVide(a));

    exit(EXIT_SUCCESS);
}