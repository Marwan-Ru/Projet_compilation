/*
 * Auteur: Gustav Hubert
 * Desciption: - Module implémentant un arbre abstrait à l'aide 
 *            du TAD arbreBinaire. L'arbre abstrait permet la
 *            représentation d'une liste d'instructions.
 *             - Pour l'utiliser, il suffit de charger ce module
 *             puis de lancer aa_init().
 *             - Ne pas oublier de libérer la mémoire avec
 *             aa_detruire() après utilisation.
 */

#ifndef ARBREABSTRAIT
#define ARBREABSTRAIT

#include <stdlib.h>
#include "arbreBinaire.h"

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

typedef struct struct_celluleAA {
    Identifiant id;
    void *donnees;
} *celluleAA;

/* GESTION DES CELLULES DE L'ARBRE */

/* Renvoie une nouvelle cellule composée d'id et de val */
celluleAA aa_creerCellule (Identifiant id, void *val);

/* Renvoie l'identifiant de la cellule cel */
Identifiant aa_idCellule (celluleAA cel);

/* Renvoie la donnée associée à la cellule cel */
void *aa_donneesCellule (celluleAA cel);

/* Libère la mémoire associée à la cellule pointé par celPtr */
void aa_detruireCellule (void *celPtr);

/* GESTION DE L'ARBRE */

/* Renvoie un abrbre abstrait vide */
arbre aa_creerVide ();

/* Vérifie si l'arbre abstrait a est vide */
int aa_estVide (arbre a);

/* Renvoie un arbre abstrait identifié par id et 
   n'ayant ni fils, ni frère. val correspond à la
   donnée potentiellement associé à id */
arbre aa_creerFeuille (Identifiant id, void *val);

/* Crée et renvoie un arbre abstrait identifié par id.
   Les abres fils et frère peuvent également être indiqués. 
   val correspond à la donnée potentiellement associé à id */
arbre aa_creerNoeud (Identifiant id, void *val, arbre fils, arbre frere);

/* Remplace le fils de l'arbre abstrait a par 
   l'arbre fils donné en argument (de façon "in-place").
   Renvoie le même arbre abstrait a */
arbre aa_setFils (arbre a, arbre fils);

/* Remplace le frère de l'arbre abstrait a par 
   l'arbre frère donné en argument (de façon "in-place").
   Renvoie le même arbre abstrait a */
arbre aa_setFrere (arbre a, arbre frere);

/* Renvoie la cellule de la racine de l'arbre abstrait a */
celluleAA aa_getRacine (arbre a);

/* Renvoie le fils de l'arbre abstrait a */
arbre aa_getFils (arbre a);

/* Renvoie le frère de l'arbre abstrait a */
arbre aa_getFrere (arbre a);

/* Libère récursivement la mémoire allouée à l'arbre 
   abstrait a et ses descendants. Si detruireValeur
   vaut 1 les cellules de l'arbre sont également détruites */
arbre aa_detruire (arbre a, int detruireValeur);

#endif