#include <stdlib.h>
#include <string.h>

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
    char *suivant;
} *tableLex;

tableLex initTableLex () {
    tableLex tl[T_TABLELEX];
    return tl;
}

void addLex (tableLex tl, char *lexeme) {
    int longueurLex = strlen(lexeme);
    long hashLex = hash(lexeme) % T_TABLELEX;

}