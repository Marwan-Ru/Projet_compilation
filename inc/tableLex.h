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

lexeme *initTableLex ();

typedef int *hashTable;

hashTable initHashTable();

/* Ajoute le lexeme au tableau tl de longueur longTableLex. La table de hashage ht permet un accès plus rapide */
void addLex (lexeme *tl, int *longTabLex, hashTable ht, char *lexeme);

/* Renvoie le lexeme stocké à la position num de la table tl */
lexeme getLex (lexeme *tl, int *longTabLex, unsigned int num);

/* Renvoie la position de lexeme dans le tableau tl */
int getLexNum (lexeme *tl, hashTable ht, char *lexeme);

/* Renvoie 1 si le lexeme existe dans tl, 0 sinon */
int lexemeExiste (lexeme *tl, hashTable ht, char *lexeme);

#endif