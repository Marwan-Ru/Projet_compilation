#include "tableTypes.h"

tableType tt_init () {
    int i;
    tableType tt = allocation_mem(T_TABLETYPES, sizeof(int));
    for(i = 0; i < T_TABLETYPES; i++) tt[i] = -1;
    return tt;
}

/* Fonction locale permettant de vérifier si t valeurs rentre dans une table des types.
   Affiche une erreur et quitte si ce n'est pas le cas */
void verifTaille (int t) {
    if (t > T_TABLETYPES) {
        fprintf(stderr, "Erreur! Dépassement de la limite de champs autorisées!\n");
        exit(EXIT_FAILURE);
    }
}

/* Fonction locale permettant l'ajout de nb valeurs à tt de longueur longTabType.
   Renvoie la position des données ajoutées */
int ajoutsValTab (tableType tt, int *longTabType, int nb, va_list vl) {
    int i, start = *longTabType;

    verifTaille(*longTabType + nb);

    for (i = 0; i < nb; i++) {
        tt[(*longTabType)++] = va_arg(vl, int);
    }

    va_end(vl);

    return start;
}


/* Ajoute les informations concernant une structure à la table de représentation des types.
   Les derniers paramètres de la fonction correspondent à nbChamps fois trois entiers indiquants,
   pour chaque champs :
    - l'index dans la table des déclarations de l'enregistrement associé au type du champs
    - le numéro lexicographique du nom du champ
    - le déplacement à l'intérieur de la structure
   La fonction renvoit l'emplacement des données dans la table */
int tt_ajoutStruct(tableType tt, int *longTabType, int nbChamps, ...) {
    va_list vl;

    verifTaille(*longTabType+1);
    tt[(*longTabType)++] = nbChamps;

    va_start(vl, nbChamps);
    return ajoutsValTab(tt, longTabType, nbChamps * 3, vl)-1;
}

/* Ajoute les informations concernant un tableau (type des éléments: typeElem, nombre de dimensions: 
   nbDimensions) à la table de représentation des types.
   Les derniers paramètres de la fonction correspondent à nbDimensions fois deux entiers indiquants,
   pour chaque dimension la borne inférieure et la borne supérieure.
   La fonction renvoit l'emplacement des données dans la table */
int tt_ajoutTab(tableType tt, int *longTabType, int typeElem, int nbDimensions, ...) {
    va_list vl;

    verifTaille(*longTabType + 2);

    tt[(*longTabType)++] = typeElem;
    tt[(*longTabType)++] = nbDimensions;

    va_start(vl, nbDimensions);
    return ajoutsValTab(tt, longTabType, nbDimensions*2, vl)-2;
}

/* Ajoute les informations concernant une fonction (type du résultat: typeRes, nombre de paramètres:
   nbParams) à la table de représentation des types.
   Les derniers paramètres de la fonction correspondent à nbParams fois deux entiers indiquants,
   pour chaque paramètre :
    - Son numéro lexicographique
    - Son type 
   La fonction renvoit l'emplacement des données dans la table */
int tt_ajoutFonction(tableType tt, int *longTabType, int typeRes, int nbParams, ...) {
    va_list vl;

    verifTaille(*longTabType + 2);

    tt[(*longTabType)++] = typeRes;
    tt[(*longTabType)++] = nbParams;

    va_start(vl, nbParams);
    return ajoutsValTab(tt, longTabType, nbParams*2, vl)-2;
}

/* Ajoute les informations concernant une procédure (nombre de paramètres: nbParams) à la table de 
   représentation des types. Les derniers paramètres de la procédure correspondent à nbParams fois 
   deux entiers indiquants, pour chaque paramètre :
    - Son numéro lexicographique
    - Son type 
   La fonction renvoit l'emplacement des données dans la table */
int tt_ajoutProcedure(tableType tt, int *longTabType, int nbParams, ...) {
    va_list vl;

    verifTaille(*longTabType + 1);

    tt[(*longTabType)++] = nbParams;

    va_start(vl, nbParams);
    return ajoutsValTab(tt, longTabType, nbParams*2, vl)-1;
}



/* Renvoie le nombre de champs de la structure se trouvant à posStruct */
int tt_structNbChamps (tableType tt, int posStruct) { return tt[posStruct]; }

/* Renvoie l'index du champs i (indexé à 0) de la structure se trouvant à posStruct */
int tt_structIndexChamp (tableType tt, int posStruct, int i) { return tt[posStruct+1+i*3]; }

/* Renvoie le numéro lexicographique du nom du champs i (indexé à 0) de la structure 
   se trouvant à posStruct */
int tt_structNumLexChamp (tableType tt, int posStruct, int i) { return tt[posStruct+2+i*3]; }

/* Renvoie le déplacement du champs i (indexé à 0) à l'intérieur de la structure se 
   trouvant à posStruct */
int tt_structDeplacementChamp (tableType tt, int posStruct, int i) { return tt[posStruct+3+i*3]; }



/* Renvoie le type des éléments du tableau se trouvant à posTab */
int tt_tabTypeElem (tableType tt, int posTab) { return tt[posTab]; }

/* Renvoie le nombre de dimensions du tableau se trouvant à posTab */
int tt_tabNbDimensions (tableType tt, int posTab) { return tt[posTab+1]; }

/* Renvoie la borne inférieure de la dimension i (indexé à 0) du tableau se trouvant à posTab */
int tt_tabDimBornInf (tableType tt, int posTab, int i) { return tt[posTab+2+i*2]; }

/* Renvoie la borne supérieure de la dimension i (indexé à 0) du tableau se trouvant à posTab */
int tt_tabDimBornSup (tableType tt, int posTab, int i) { return tt[posTab+3+i*2]; }



/* Renvoie le type de retour de la fonction se trouvant à posFonc */
int tt_foncTypeRetour (tableType tt, int posFonc) { return tt[posFonc]; }

/* Renvoie le nombre de paramètres de la fonction se trouvant à posFonc */
int tt_foncNbParam (tableType tt, int posFonc) { return tt[posFonc+1]; }

/* Renvoie le numéro lexicographique du paramètre i (indexé à 0) de la fonction se 
   trouvant à posFonc */
int tt_foncNumLexParam (tableType tt, int posFonc, int i) { return tt[posFonc+2+i*2]; }

/* Renvoie le type du paramètre i (indexé à 0) de la fonction se trouvant à posFonc */
int tt_foncTypeParam (tableType tt, int posFonc, int i) { return tt[posFonc+3+i*2]; }



/* Renvoie le nombre de paramètres de la procédure se trouvant à posProc */
int tt_procNbParam (tableType tt, int posProc) { return tt[posProc]; }

/* Renvoie le numéro lexicographique du paramètre i (indexé à 0) de la procédure se 
   trouvant à posProc */
int tt_procNumLexParam (tableType tt, int posProc, int i) { return tt[posProc+1+i*2]; }

/* Renvoie le type du paramètre i (indexé à 0) de la procédure se trouvant à posProc */
int tt_procTypeParam (tableType tt, int posProc, int i) { return tt[posProc+2+i*2]; }



/* Libère la mémoire associé à la table des types  */
void tt_detruire (tableType tt) {
    if (tt != NULL) libere_mem(&tt);
}