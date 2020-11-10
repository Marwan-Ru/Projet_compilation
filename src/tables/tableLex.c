#include "tableLex.h"

int hashTable[T_TABLELEX];
lexeme tableLex[T_TABLELEX];
int longTabLex;

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

void ht_init () {
    int i;
    for (i = 0; i < T_TABLELEX; i++) {
        hashTable[i] = -1;
    }
}

/* Initialise la table lexicographique avec les types de base et des lignes vides */
void tl_init () {
    int i;

    ht_init();
    longTabLex = 0;

    tl_ajout("int");
    tl_ajout("float");
    tl_ajout("bool");
    tl_ajout("char");

    for (i = 4; i < T_TABLELEX; i++) {
        tableLex[i].longueur = -1;
        tableLex[i].suivant = -1;
    }
}

/* Ajoute le lexeme à la table lexicographique de longueur longTableLex */
void tl_ajout (char *lexeme) {
    int longueurLex = strlen(lexeme), posTab;
    long hashLex = hash(lexeme);

    if (longTabLex + 1 >= T_TABLELEX) {
        fprintf(stderr, "Erreur! Dépassement de la limite de lexèmes autorisées!\n");
        exit(EXIT_FAILURE);
    }

    tableLex[longTabLex].lexeme = allocation_mem(strlen(lexeme)+1, sizeof(char));
    strcpy(tableLex[longTabLex].lexeme, lexeme);
    tableLex[longTabLex].longueur = longueurLex;
    tableLex[longTabLex].suivant = -1;
    
    if (hashTable[hashLex] == -1) hashTable[hashLex] = longTabLex; 
    else {
        posTab = hashTable[hashLex];
        while (tableLex[posTab].suivant != -1) posTab = tableLex[posTab].suivant;
        tableLex[posTab].suivant = longTabLex;
    }
    longTabLex++;
}

/* Renvoie le lexeme stocké à la position num de la table lexicographique */
char *tl_getLex (unsigned int num) {
    if (num >= longTabLex) {
        fprintf(stderr, "Erreur! Accès à un lexeme inexistant.\n");
        exit(EXIT_FAILURE);
    }
    return tableLex[num].lexeme;
}

/* Renvoie le numéro lexicographique du lexeme */
int tl_getLexNum (char *lexeme) {
    long hashLex = hash(lexeme);
    int longueurLex = strlen(lexeme), posTab;

    posTab = hashTable[hashLex];

    while (posTab != -1 && (tableLex[posTab].longueur != longueurLex || strcmp(tableLex[posTab].lexeme, lexeme) != 0)) {
        posTab = tableLex[posTab].suivant;
    }

    return posTab;
}

/* Renvoie 1 si le lexeme existe dans la table lexicographique, 0 sinon */
int tl_existe (char *lexeme) {
    return tl_getLexNum(lexeme) != -1;
}

/* Renvoie le nombre de lexeme stocké dans la table lexicographique */
int tl_longTabLex() {
    return longTabLex;
}

/* Libère la mémoire associé à la table lexicographique */
void tl_detruire () {
    int i;
    for (i = 0; i < T_TABLELEX; i++) {
        libere_mem(&(tableLex[i].lexeme));
    }
}