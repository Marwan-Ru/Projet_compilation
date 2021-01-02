#ifndef ARBREABSTRAIT
#define ARBREABSTRAIT

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "allocation.h"

typedef enum enum_id {
    A_VIDE,
    A_LISTE,
    A_IDF,
    A_CSTE_ENT,
    A_CSTE_REELE, 
    A_CSTE_BOOL,
    A_CSTE_CAR,
    A_CSTE_CHAINE,
    A_APPEL_FONC,
    A_LISTEPARAMS,
    A_OPAFF,
    A_IF_THEN_ELSE,
    A_WHILE,
    A_DO_WHILE,
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
    A_OP_OU,
    A_OP_ET,
    A_OP_NON,
    A_LISTE_INDICES,
    A_CHAMP,
    A_AFFICHER,
    A_RETOURNER
} Identifiant;

typedef struct struct_arbre {
    Identifiant id;
    int valeur;
	struct struct_arbre *frere;
	struct struct_arbre *fils;
} *arbre;

arbre aa_vide ();

arbre aa_creerNoeud (Identifiant id, int valeur);

/* Renvoie pere */
arbre aa_concatPereFrere (arbre pere, arbre frere);

/* Renvoie pere */
arbre aa_concatPereFils (arbre pere, arbre fils);

void aa_afficher (arbre a);

/* Détruit seulement la racine de l'arbre a */
void aa_detruire (arbre a);

/* Détruit récursivement tous les noeuds de l'arbre a */
void aa_detruire_rec (arbre a);

#endif
