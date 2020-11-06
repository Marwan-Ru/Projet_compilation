#ifndef TABLELEX
#define TABLELEX

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "allocation.h"

#define T_TABLELEX 500

/* Dan Bernstein http://www.cse.yorku.ca/~oz/hash.html */
unsigned long
hash(char *str);

typedef struct s_lexeme {
    int longueur;
    char *lexeme;
    int suivant;
} lexeme;

lexeme *tl_init ();

typedef int *hashTable;

hashTable ht_init();

/* Ajoute le lexeme au tableau tl de longueur longTableLex. La table de hashage ht permet un accès plus rapide */
void tl_ajout (lexeme *tl, int *longTabLex, hashTable ht, char *lexeme);

/* Renvoie le lexeme stocké à la position num de la table tl */
lexeme tl_getLex (lexeme *tl, int *longTabLex, unsigned int num);

/* Renvoie la position de lexeme dans le tableau tl */
int tl_getLexNum (lexeme *tl, hashTable ht, char *lexeme);

/* Renvoie 1 si le lexeme existe dans tl, 0 sinon */
int tl_existe (lexeme *tl, hashTable ht, char *lexeme);

/* Libère la mémoire associé à la table lexicographique tl et sa table de hashage ht */
void tl_detruire (lexeme *tl, hashTable ht);

#endif