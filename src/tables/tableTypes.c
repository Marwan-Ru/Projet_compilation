/* Auteur: Gustav Hubert
 * Description: - Module implémentant une table de représentation
 *                des  types et des entêtes de sous-programmes.
 *                Cette table contient la description des types,
 *                des procédures et fonctions déclaré(e)s dans 
 *                le programme.
 *                - Pour utiliser le module il suffit de le charger 
 *                puis d'appeler tt_init().
 */

#include "tableTypes.h"

int tt[T_TABLETYPES];
int longTabType = 0;

void tt_init () {
    int i;
    for(i = 0; i < T_TABLETYPES; i++) tt[i] = -1;
}

/* Fonction locale permettant de vérifier si t valeurs rentre dans une table des types.
   Affiche une erreur et quitte si ce n'est pas le cas */
void verifTaille (int t) {
    if (t > T_TABLETYPES) {
        fprintf(stderr, "Erreur! Dépassement de la limite de champs autorisées!\n");
        exit(EXIT_FAILURE);
    }
}

/* Ajoute valeur à la suite de la table. Assez de place supposé */
void tt_ajout (int valeur) {
    tt[longTabType++] = valeur;
}

/* Fonction locale permettant l'ajout de nb valeurs à la table des types.
   Renvoie la position des données ajoutées */
int ajoutsValTab (int nb, int *valeurs) {
    int i, start = longTabType;

    verifTaille(longTabType + nb);

    for (i = 0; i < nb; i++) {
        tt_ajout(valeurs[i]);
    }

    return start;
}


/* Ajoute les informations concernant une structure à la table de représentation des types.
   Le tableau de valeurs correspond à nbChamps fois trois entiers indiquants,
   pour chaque champs :
    - l'index dans la table des déclarations de l'enregistrement associé au type du champs
    - le numéro lexicographique du nom du champ
    - le déplacement à l'intérieur de la structure
   La fonction renvoit l'emplacement des données dans la table */
int tt_ajoutStruct(int nbChamps, int *valeurs) {
    verifTaille(longTabType+1);
    tt[longTabType++] = nbChamps;

    return ajoutsValTab(nbChamps * 3, valeurs)-1;
}

/* Ajoute les informations concernant un tableau (type des éléments: typeElem, nombre de dimensions: 
   nbDimensions) à la table de représentation des types.
   Le tableau de valeurs correspond à nbDimensions fois deux entiers indiquants,
   pour chaque dimension la borne inférieure et la borne supérieure.
   La fonction renvoit l'emplacement des données dans la table */
int tt_ajoutTab(int typeElem, int nbDimensions, int *valeurs) {
    verifTaille(longTabType + 2);

    tt[longTabType++] = typeElem;
    tt[longTabType++] = nbDimensions;

    return ajoutsValTab(nbDimensions*2, valeurs)-2;
}

/* Ajoute les informations concernant une fonction (type du résultat: typeRes, nombre de paramètres:
   nbParams) à la table de représentation des types.
   Le tableau de valeurs correspond à nbParams fois deux entiers indiquants,
   pour chaque paramètre :
    - Son numéro lexicographique
    - Son type 
   La fonction renvoit l'emplacement des données dans la table */
int tt_ajoutFonction(int typeRes, int nbParams, int *valeurs) {
    verifTaille(longTabType + 2);

    tt[longTabType++] = typeRes;
    tt[longTabType++] = nbParams;

    return ajoutsValTab(nbParams*2, valeurs)-2;
}

/* Ajoute les informations concernant une procédure (nombre de paramètres: nbParams) à la table de 
   représentation des types. Le tableau de valeurs correspond à nbParams fois 
   deux entiers indiquants, pour chaque paramètre :
    - Son numéro lexicographique
    - Son type 
   La fonction renvoit l'emplacement des données dans la table */
int tt_ajoutProcedure(int nbParams, int *valeurs) {
    verifTaille(longTabType + 1);

    tt[longTabType++] = nbParams;

    return ajoutsValTab(nbParams*2, valeurs)-1;
}


/* Fonction locale vérifiant l'indice pos du tableau des types. 
   Si ce dernier se trouve dans le tableau la valeur associé est renvoyé */
int getVal (int pos) {
    verifTaille(pos);
    return tt[pos];
}

/* Renvoie le nombre de champs de la structure se trouvant à posStruct */
int tt_structNbChamps (int posStruct) { return getVal(posStruct); }

/* Renvoie l'index du champs i (indexé à 0) de la structure se trouvant à posStruct */
int tt_structIndexChamp (int posStruct, int i) { return getVal(posStruct+1+i*3); }

/* Renvoie le numéro lexicographique du nom du champs i (indexé à 0) de la structure 
   se trouvant à posStruct */
int tt_structNumLexChamp (int posStruct, int i) { return getVal(posStruct+2+i*3); }

/* Renvoie le déplacement du champs i (indexé à 0) à l'intérieur de la structure se 
   trouvant à posStruct */
int tt_structDeplacementChamp (int posStruct, int i) { return getVal(posStruct+3+i*3); }



/* Renvoie le type des éléments du tableau se trouvant à posTab */
int tt_tabTypeElem (int posTab) { return getVal(posTab); }

/* Renvoie le nombre de dimensions du tableau se trouvant à posTab */
int tt_tabNbDimensions (int posTab) { return getVal(posTab+1); }

/* Renvoie la borne inférieure de la dimension i (indexé à 0) du tableau se trouvant à posTab */
int tt_tabDimBornInf (int posTab, int i) { return getVal(posTab+2+i*2); }

/* Renvoie la borne supérieure de la dimension i (indexé à 0) du tableau se trouvant à posTab */
int tt_tabDimBornSup (int posTab, int i) { return getVal(posTab+3+i*2); }



/* Renvoie le type de retour de la fonction se trouvant à posFonc */
int tt_foncTypeRetour (int posFonc) { return getVal(posFonc); }

/* Renvoie le nombre de paramètres de la fonction se trouvant à posFonc */
int tt_foncNbParam (int posFonc) { return getVal(posFonc+1); }

/* Renvoie le numéro lexicographique du paramètre i (indexé à 0) de la fonction se 
   trouvant à posFonc */
int tt_foncNumLexParam (int posFonc, int i) { return getVal(posFonc+2+i*2); }

/* Renvoie le type du paramètre i (indexé à 0) de la fonction se trouvant à posFonc */
int tt_foncTypeParam (int posFonc, int i) { return getVal(posFonc+3+i*2); }



/* Renvoie le nombre de paramètres de la procédure se trouvant à posProc */
int tt_procNbParam (int posProc) { return getVal(posProc); }

/* Renvoie le numéro lexicographique du paramètre i (indexé à 0) de la procédure se 
   trouvant à posProc */
int tt_procNumLexParam (int posProc, int i) { return getVal(posProc+1+i*2); }

/* Renvoie le type du paramètre i (indexé à 0) de la procédure se trouvant à posProc */
int tt_procTypeParam (int posProc, int i) { return getVal(posProc+2+i*2); }


/* Affiche le tableau des types dans le terminal */
void tt_afficher() {
    int i;

    printf("Table de représentation des types et des entêtes de sous-programmes (%d valeurs):\n", longTabType);
    printf("[");
    for (i = 0; i < longTabType+2 && i < T_TABLETYPES-1; i++) {
        printf("%d, ", tt[i]);
    }
    if (i < T_TABLETYPES-1) {
        printf("..., -1]\n");
    } else printf("%d]\n", tt[i]);
}

/* Ecrit la table vers le fichier ouvert f */
void tt_ecrireFichier (FILE *f) {
    int i;

    /* Valeurs */
    for (i = 0; i < longTabType; i++) {
        fprintf(f, "%d\n", tt[i]);
    }
    /* Séparateur */
    fputs("---\n", f);
}