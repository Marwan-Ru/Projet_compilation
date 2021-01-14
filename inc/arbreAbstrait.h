/* Auteur : Gustav HUBERT
   Description : Représente un arbre abstrait */

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
    A_RETOURNER,
    A_LIRE
} Identifiant;

typedef struct struct_arbre {
    Identifiant id;
    int valeur;
    int num_decl;
	struct struct_arbre *frere;
	struct struct_arbre *fils;
} *arbre;

/* Renvoie un arbre vide */
arbre aa_vide ();

/* Crée le noueud d'un arbre à partir de son identifiant, sa valeur et son numéro de déclaration */
arbre aa_creerNoeud (Identifiant id, int valeur, int num_decl);

/* Concatène l'arbre père avec l'arbre frere. Renvoie l'arbre pere */
arbre aa_concatPereFrere (arbre pere, arbre frere);

/* Concatène l'arbre père avec l'arbre fils. Renvoie l'arbre pere */
arbre aa_concatPereFils (arbre pere, arbre fils);

/* Affiche l'arbre dans le terminal */
void aa_afficher (arbre a);

/* Renvoie le frere de la racine de a */
arbre aa_frere (arbre a);

/* Renvoie le fils de la racine de a */
arbre aa_fils (arbre a);

/* Renvoie la valeur de la racine de a */
int aa_valeur (arbre a);

/* Renvoie le numéro lexical de la racine de a */
int aa_num_decl (arbre a);

/* Renvoie l'identifiant de de la racine de a */
Identifiant aa_id (arbre a);

/* Ecrit l'arbre vers le fichier ouver f */
void aa_ecrireFichier (FILE *f, arbre a);

/* Détruit seulement la racine de l'arbre a */
void aa_detruire (arbre a);

/* Détruit récursivement tous les noeuds de l'arbre a */
void aa_detruire_rec (arbre a);

#endif
