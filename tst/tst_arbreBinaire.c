#include "arbreBinaire.h"
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
    
    a = ab_creerVide();
    printf("Arbre a vide ? %d\n", ab_estVide(a));

    a = ab_creerFeuille(NULL);
    printf("Arbre a: Vide? %d, Hauteur: %d, Fils: %d\n", 
            ab_estVide(a), ab_hauteur(a), ab_nombreFils(a));

    ab_detruire(a);
    a = ab_creerFeuille(entier);
    printf("Arbre a: Vide? %d, Hauteur: %d, Fils: %d\n", 
            ab_estVide(a), ab_hauteur(a), ab_nombreFils(a));

	b = ab_creerNoeud(reel, NULL, ab_creerFeuille(entier));
	c = ab_creerNoeud(caractere, ab_creerFeuille(entier), NULL);

    ab_setFilsGauche(a, b);
    ab_setFilsDroit(a, c);
	printf("Arbre a: Vide? %d, Hauteur: %d, Fils: %d\n", 
            ab_estVide(a), ab_hauteur(a), ab_nombreFils(a));
	
	tmp = ab_getFilsGauche(a);
	printf("filsGauche(a): Vide? %d, Hauteur: %d, Fils: %d\n", 
            ab_estVide(tmp), ab_hauteur(tmp), ab_nombreFils(tmp));

	tmp = ab_getFilsDroit(a);
	printf("filsDroit(a): Vide? %d, Hauteur: %d, Fils: %d\n", 
            ab_estVide(tmp), ab_hauteur(tmp), ab_nombreFils(tmp));

	a = ab_detruire(a);
	printf("Arbre a vide ? %d\n", ab_estVide(a));

	libere_mem(&entier);
	libere_mem(&reel);
	libere_mem(&caractere);

    exit(EXIT_SUCCESS);
}