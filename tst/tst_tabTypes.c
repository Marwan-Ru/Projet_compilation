#include "tableTypes.h"
#include <stdio.h>

void afficherTabTypes (tableType tt, int l) {
    int i;

    printf("[");
    for (i = 0; i < l-1; i++) {
        printf("%d, ", tt[i]);
    }
    printf("%d]\n", tt[i]);
}

int main () {
    tableType tt = tt_init();
    int l = 0, pos;

    /* Structures */
    pos = tt_ajoutStruct(tt, &l, 2, 1, 2, 3, 4, 5, 6);
    afficherTabTypes(tt, l);
    /* Utilisation normale */
    printf("nb champs struct1: %d\n", tt_structNbChamps(tt, pos));
    pos = tt_ajoutStruct(tt, &l, 1, 7, 8, 9, 10, 11, 12);
    afficherTabTypes(tt, l);
    /* Ignore 10, 11, 12 */
    printf("index champ 1 struct2: %d\n", tt_structIndexChamp(tt, pos, 0));
    pos = tt_ajoutStruct(tt, &l, 1, 13, 14);
    afficherTabTypes(tt, l);
    /* Comportement imprévu */
    printf("NumLex champ 1 struct3: %d\n", tt_structNumLexChamp(tt, pos, 0));
    printf("Deplacement champ 2 struct1: %d\n", tt_structDeplacementChamp(tt, 0, 1));
    

    /* Tableaux */
    pos = tt_ajoutTab(tt, &l, 234, 2, 0, 5, 10, 15);
    afficherTabTypes(tt, l);
    printf("Type elements tab: %d\n", tt_tabTypeElem(tt, pos));
    printf("Nb dimensions tab: %d\n", tt_tabNbDimensions(tt, pos));
    printf("Borne inf dimension 1 tab: %d\n", tt_tabDimBornInf(tt, pos, 0));
    printf("Borne sup dimension 2 tab: %d\n", tt_tabDimBornSup(tt, pos, 1));

    /* Fonctions */
    pos = tt_ajoutFonction(tt, &l, 1, 2, 2345, 2, 234, 1);
    afficherTabTypes(tt, l);
    printf("Type retour fonc: %d\n", tt_foncTypeRetour(tt, pos));
    printf("Nb param fonc: %d\n", tt_foncNbParam(tt, pos));
    printf("Num lex param 1 fonc: %d\n", tt_foncNumLexParam(tt, pos, 0));
    printf("Type param 2 fonc: %d\n", tt_foncTypeParam(tt, pos, 1));

    /* Procédures */
    pos = tt_ajoutProcedure(tt, &l, 2, 867, 3, 238, 0);
    afficherTabTypes(tt, l);
    printf("Nb param proc: %d\n", tt_procNbParam(tt, pos));
    printf("Num lex param 1 proc: %d\n", tt_procNumLexParam(tt, pos, 0));
    printf("Type param 2 proc: %d\n", tt_procTypeParam(tt, pos, 1));

    afficherTabTypes(tt, l+10);

    tt_detruire(tt);

    exit(EXIT_SUCCESS);
}