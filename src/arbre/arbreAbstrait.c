#include "arbreAbstrait.h"

arbre creerNoeud (Identifiant id, int valeur) {
	arbre a;
	a.id = id;
	a.valeur = valeur;
    a.fils = NULL;
    a.frere = NULL;
    return a;
}

void concatPereFrere (arbre *pere, arbre *frere) {
	pere->frere = frere;
} 

void concatPereFils (arbre *pere, arbre *fils) {
	pere->fils = fils;
} 