#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "allocation.h"

#define T_TABLELEX 500

/* Dan Bernstein http://www.cse.yorku.ca/~oz/hash.html */
unsigned long
hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

typedef struct struct_tableLex {
    int longueur;
    char *lexeme;
    int suivant;
} *tableLex;

tableLex initTableLex () {
    int i;
    tableLex tl[T_TABLELEX];
    return tl;
}

typedef int *hashTable;

hashTable initHashTable() {
    int i;
    hashTable ht[T_TABLELEX];
    for (i = 0; i < T_TABLELEX; i++) {
        ht[i] = -1;
    }
    return ht;
}

void addLex (tableLex tl, int *longTabLex, hashTable ht, char *lexeme) {
    int longueurLex = strlen(lexeme), posTab;
    long hashLex = hash(lexeme) % T_TABLELEX;

    if (longTabLex + 1 >= T_TABLELEX) {
        fprintf(stderr, "Erreur! Dépassement de la limite de lexèmes autorisées!\n");
        exit(EXIT_FAILURE);
    }

    tl[*longTabLex].lexeme = lexeme;
    tl[*longTabLex].longueur = longueurLex;
    tl[*longTabLex].suivant = -1;
    
    if (ht[hashLex] == -1) ht[hashLex] = *longTabLex; 
    else {
        posTab = ht[hashLex];
        while (tl[posTab].suivant != -1) posTab = tl[posTab].suivant;
        tl[posTab].suivant = *longTabLex;
    }
    (*longTabLex)++;
}

