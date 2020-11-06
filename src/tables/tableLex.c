#include "tableLex.h"

/* Dan Bernstein http://www.cse.yorku.ca/~oz/hash.html */
/* Légèrement modifiée */
unsigned long
hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ( (c = *str++) > 0)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % T_TABLELEX;
}

lexeme *tl_init () {
    lexeme *tl = allocation_mem(T_TABLELEX, sizeof(struct s_lexeme));
    return tl;
}

hashTable ht_init () {
    int i;
    hashTable ht = allocation_mem(T_TABLELEX, sizeof(int));
    for (i = 0; i < T_TABLELEX; i++) {
        ht[i] = -1;
    }
    return ht;
}

/* Ajoute le lexeme au tableau tl de longueur longTableLex. La table de hashage ht permet un accès plus rapide */
void tl_ajout (lexeme *tl, int *longTabLex, hashTable ht, char *lexeme) {
    int longueurLex = strlen(lexeme), posTab;
    long hashLex = hash(lexeme);

    if (*longTabLex + 1 >= T_TABLELEX) {
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

/* Renvoie le lexeme stocké à la position num de la table tl */
lexeme tl_getLex (lexeme *tl, int *longTabLex, unsigned int num) {
    if (num >= *longTabLex) {
        fprintf(stderr, "Erreur! Accès à un lexeme inexistant.\n");
        exit(EXIT_FAILURE);
    }
    return tl[num];
}

/* Renvoie la position de lexeme dans le tableau tl */
int tl_getLexNum (lexeme *tl, hashTable ht, char *lexeme) {
    long hashLex = hash(lexeme);
    int longueurLex = strlen(lexeme), posTab;

    posTab = ht[hashLex];

    while (posTab != -1 && (tl[posTab].longueur != longueurLex || strcmp(tl[posTab].lexeme, lexeme) != 0)) {
        posTab = tl[posTab].suivant;
    }

    return posTab;
}

/* Renvoie 1 si le lexeme existe dans tl, 0 sinon */
int tl_existe (lexeme *tl, hashTable ht, char *lexeme) {
    return tl_getLexNum(tl, ht, lexeme) != -1;
}

/* Libère la mémoire associé à la table lexicographique tl et sa table de hashage ht */
void tl_detruire (lexeme *tl, hashTable ht) {
    if (tl != NULL) libere_mem(&tl);
    if (ht != NULL) libere_mem(&ht);
}