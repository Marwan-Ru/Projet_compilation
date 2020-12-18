#ifndef ARBREABSTRAIT
#define ARBREABSTRAIT

#include <stdlib.h>

typedef enum enum_id {
    A_VIDE,
    A_LISTE,
    A_IDF,
    A_CSTE_ENT,
    A_CSTE_REELE, 
    A_CSTE_BOOL,
    A_CSTE_CAR,
    A_CSTE_CHAINE,
    A_APPEL_PROC,
    A_APPEL_FONC,
    A_LISTE_PARAMS,
    A_OPAFF,
    A_IF_THEN_ELSE,
    A_WHILE,
    A_FOR,
    A_OP_PLUS,
    A_OP_MOINS,
    A_OP_MULT,
    A_OP_DIV,
    A_OP_EXP,
    A_OP_MODUL,
    A_OP_INF,
    A_OP_SUP,
    A_OP_INFE,
    A_OP_SUPE,
    A_OP_EGAL,
    A_OP_DIFF,
    A_LISTE_INDICES,
    A_CHAMPS,
    A_AFFICHER,
    A_RETOURNER
} Identifiant;

typedef struct struct_arbre {
    Identifiant id;
    int valeur;
	struct struct_arbre *frere;
	struct struct_arbre *fils;
} arbre;

arbre creerNoeud (Identifiant id, int valeur);

void concatPereFrere (arbre *pere, arbre *frere);

void concatPereFils (arbre *pere, arbre *fils);

#endif