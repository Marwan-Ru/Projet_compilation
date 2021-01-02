/*       Auteur: Gustav Hubert
 * Description: - Module implémentant une table de représentation
 *              des  types et des entêtes de sous-programmes.
 *              Cette table contient la description des types,
 *              des procédures et fonctions déclaré(e)s dans 
 *              le programme.
 *              - Pour utiliser le module il suffit de le charger 
 *              puis d'appeler tt_init().
 */


#include "tableTypes.h"
#include <stdio.h>
#include <stdlib.h>

int main () {
    int pos;
    FILE *f;

    tt_init();

    /* Structures */
    pos = tt_ajoutStruct(2, 1, 2, 3, 4, 5, 6);
    tt_afficher();
    /* Utilisation normale */
    printf("nb champs struct1: %d\n", tt_structNbChamps(pos));
    pos = tt_ajoutStruct(1, 7, 8, 9, 10, 11, 12);
    tt_afficher();
    /* Ignore 10, 11, 12 */
    printf("index champ 1 struct2: %d\n", tt_structIndexChamp(pos, 0));
    pos = tt_ajoutStruct(1, 13, 14);
    tt_afficher();
    /* Comportement imprévu */
    printf("NumLex champ 1 struct3: %d\n", tt_structNumLexChamp(pos, 0));
    printf("Deplacement champ 2 struct1: %d\n", tt_structDeplacementChamp(0, 1));
    

    /* Tableaux */
    pos = tt_ajoutTab(234, 2, 0, 5, 10, 15);
    tt_afficher();
    printf("Type elements tab: %d\n", tt_tabTypeElem(pos));
    printf("Nb dimensions tab: %d\n", tt_tabNbDimensions(pos));
    printf("Borne inf dimension 1 tab: %d\n", tt_tabDimBornInf(pos, 0));
    printf("Borne sup dimension 2 tab: %d\n", tt_tabDimBornSup(pos, 1));

    /* Fonctions */
    pos = tt_ajoutFonction(1, 2, 2345, 2, 234, 1);
    tt_afficher();
    printf("Type retour fonc: %d\n", tt_foncTypeRetour(pos));
    printf("Nb param fonc: %d\n", tt_foncNbParam(pos));
    printf("Num lex param 1 fonc: %d\n", tt_foncNumLexParam(pos, 0));
    printf("Type param 2 fonc: %d\n", tt_foncTypeParam(pos, 1));

    /* Procédures */
    pos = tt_ajoutProcedure(2, 867, 3, 238, 0);
    tt_afficher();
    printf("Nb param proc: %d\n", tt_procNbParam(pos));
    printf("Num lex param 1 proc: %d\n", tt_procNumLexParam(pos, 0));
    printf("Type param 2 proc: %d\n", tt_procTypeParam(pos, 1));

    tt_afficher();

    f = fopen("obj/tabTypesInter.txt", "a+");
    tt_ecrireFichier(f);
    fclose(f);

    exit(EXIT_SUCCESS);
}