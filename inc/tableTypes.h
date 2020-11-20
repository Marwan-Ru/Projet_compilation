#ifndef TABLETYPES
#define TABLETYPES

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "allocation.h"

#define T_TABLETYPES 70

typedef int *tableType;

tableType tt_init ();

/* Ajoute les informations concernant une structure à la table de représentation des types.
   Les derniers paramètres de la fonction correspondent à nbChamps fois trois entiers indiquants,
   pour chaque champs :
    - l'index dans la table des déclarations de l'enregistrement associé au type du champs
    - le numéro lexicographique du nom du champ
    - le déplacement à l'intérieur de la structure
   La fonction renvoit l'emplacement des données dans la table */
int tt_ajoutStruct(tableType tt, int *longTabType, int nbChamps, ...);

/* Ajoute les informations concernant un tableau (type: typeElem, dimensions: nbDimensions)
   à la table de représentation des types.
   Les derniers paramètres de la fonction correspondent à nbDimensions fois deux entiers indiquants,
   pour chaque dimension la borne inférieure et la borne supérieure.
   La fonction renvoit l'emplacement des données dans la table */
int tt_ajoutTab(tableType tt, int *longTabType, int typeElem, int nbDimensions, ...);

/* Ajoute les informations concernant une fonction (type du résultat: typeRes, nombre de paramètres:
   nbParams) à la table de représentation des types.
   Les derniers paramètres de la fonction correspondent à nbParams fois deux entiers indiquants,
   pour chaque paramètre :
    - Son numéro lexicographique
    - Son type 
   La fonction renvoit l'emplacement des données dans la table */
int tt_ajoutFonction(tableType tt, int *longTabType, int typeRes, int nbParams, ...);

/* Ajoute les informations concernant une procédure (nombre de paramètres: nbParams) à la table de 
   représentation des types. Les derniers paramètres de la procédure correspondent à nbParams fois 
   deux entiers indiquants, pour chaque paramètre :
    - Son numéro lexicographique
    - Son type 
   La fonction renvoit l'emplacement des données dans la table */
int tt_ajoutProcedure(tableType tt, int *longTabType, int nbParams, ...);



/* Renvoie le nombre de champs de la structure se trouvant à posStruct */
int tt_structNbChamps (tableType tt, int posStruct);

/* Renvoie l'index du champs i (indexé à 0) de la structure se trouvant à posStruct */
int tt_structIndexChamp (tableType tt, int posStruct, int i);

/* Renvoie le numéro lexicographique du nom du champs i (indexé à 0) de la structure 
   se trouvant à posStruct */
int tt_structNumLexChamp (tableType tt, int posStruct, int i);

/* Renvoie le déplacement du champs i (indexé à 0) à l'intérieur de la structure se 
   trouvant à posStruct */
int tt_structDeplacementChamp (tableType tt, int posStruct, int i);



/* Renvoie le type des éléments du tableau se trouvant à posTab */
int tt_tabTypeElem (tableType tt, int posTab);

/* Renvoie le nombre de dimensions du tableau se trouvant à posTab */
int tt_tabNbDimensions (tableType tt, int posTab);

/* Renvoie la borne inférieure de la dimension i (indexé à 0) du tableau se trouvant à posTab */
int tt_tabDimBornInf (tableType tt, int posTab, int i);

/* Renvoie la borne supérieure de la dimension i (indexé à 0) du tableau se trouvant à posTab */
int tt_tabDimBornSup (tableType tt, int posTab, int i);



/* Renvoie le type de retour de la fonction se trouvant à posFonc */
int tt_foncTypeRetour (tableType tt, int posFonc);

/* Renvoie le nombre de paramètres de la fonction se trouvant à posFonc */
int tt_foncNbParam (tableType tt, int posFonc);

/* Renvoie le numéro lexicographique du paramètre i (indexé à 0) de la fonction se 
   trouvant à posFonc */
int tt_foncNumLexParam (tableType tt, int posFonc, int i);

/* Renvoie le type du paramètre i (indexé à 0) de la fonction se trouvant à posFonc */
int tt_foncTypeParam (tableType tt, int posFonc, int i);



/* Renvoie le nombre de paramètres de la procédure se trouvant à posProc */
int tt_procNbParam (tableType tt, int posProc);

/* Renvoie le numéro lexicographique du paramètre i (indexé à 0) de la procédure se 
   trouvant à posProc */
int tt_procNumLexParam (tableType tt, int posProc, int i);

/* Renvoie le type du paramètre i (indexé à 0) de la procédure se trouvant à posProc */
int tt_procTypeParam (tableType tt, int posProc, int i);



/* Libère la mémoire associé à la table des types  */
void tt_detruire (tableType tt);
#endif