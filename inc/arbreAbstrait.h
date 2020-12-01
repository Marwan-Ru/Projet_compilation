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

enum Identifiant {
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
}

typedef struct struct_celluleAA {
    enum Identifiant id;
    void *donnees;
} *celluleAA;

#endif ARBREABSTRAIT