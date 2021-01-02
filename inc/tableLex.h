/*       Auteur: Gustav Hubert
 * Description: - Module implémentant une table lexicographique. 
 *             Celle-ci permet le stockage de lexèmes (chaînes 
 *             de caractères) ainsi que leurs association à un
 *             numéro lexicographique unique (entier).
 *              - Pour utiliser le module il suffit de le charger 
 *             puis d'appeler tl_init().
 *              - Ne pas oublier d'appeler tl_detruire() après
 *             utilisation.
 */

#ifndef TABLELEX
#define TABLELEX

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "allocation.h"

#define T_TABLELEX 500

typedef struct s_lexeme {
    int longueur;
    char *lexeme;
    int suivant;
} lexeme;

/* Initialise la table lexicographique avec les types de base et des lignes vides */
void tl_init ();

/* Ajoute le lexeme à la table lexicographique de longueur longTableLex.
   Renvoie le nouveau numéro lexicographique associé au lexème */
int tl_ajout (char *lexeme);

/* Renvoie le lexeme stocké à la position num de la table lexicographique */
char *tl_getLex (unsigned int num);

/* Renvoie le numéro lexicographique du lexeme */
int tl_getLexNum (char *lexeme);

/* Renvoie 1 si le lexeme existe dans la table lexicographique, 0 sinon */
int tl_existe (char *lexeme);

/* Renvoie le nombre de lexeme stocké dans la table lexicographique */
int tl_longTabLex();

/* Affiche tous les lexèmes avec le numéro lexicographique la longueur et le lexème suivant s'il y a */
void tl_afficher();

/* Ecrit la table vers f */
void tl_ecrireFichier (FILE *f);

/* Libère la mémoire associé à la table lexicographique */
void tl_detruire ();

#endif
