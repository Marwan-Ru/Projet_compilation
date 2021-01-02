/*       Auteur: Gustav Hubert
 * Description: - Module implémentant une table de représentation
 *              des  types et des entêtes de sous-programmes.
 *              Cette table contient la description des types,
 *              des procédures et fonctions déclaré(e)s dans 
 *              le programme.
 *              - Pour utiliser le module il suffit de le charger 
 *              puis d'appeler tt_init().
 */


#ifndef TABLETYPES
#define TABLETYPES

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "allocation.h"

#define T_TABLETYPES 70

void tt_init ();


/* Ajoute les informations concernant une structure à la table de représentation des types.
   Les derniers paramètres de la fonction correspondent à nbChamps fois trois entiers indiquants,
   pour chaque champs :
    - l'index dans la table des déclarations de l'enregistrement associé au type du champs
    - le numéro lexicographique du nom du champ
    - le déplacement à l'intérieur de la structure
   La fonction renvoit l'emplacement des données dans la table */
int tt_ajoutStruct(int nbChamps, ...);

/* Ajoute les informations concernant un tableau (type des éléments: typeElem, nombre de dimensions: 
   nbDimensions) à la table de représentation des types.
   Les derniers paramètres de la fonction correspondent à nbDimensions fois deux entiers indiquants,
   pour chaque dimension la borne inférieure et la borne supérieure.
   La fonction renvoit l'emplacement des données dans la table */
int tt_ajoutTab(int typeElem, int nbDimensions, ...);

/* Ajoute les informations concernant une fonction (type du résultat: typeRes, nombre de paramètres:
   nbParams) à la table de représentation des types.
   Les derniers paramètres de la fonction correspondent à nbParams fois deux entiers indiquants,
   pour chaque paramètre :
    - Son numéro lexicographique
    - Son type 
   La fonction renvoit l'emplacement des données dans la table */
int tt_ajoutFonction(int typeRes, int nbParams, ...);

/* Ajoute les informations concernant une procédure (nombre de paramètres: nbParams) à la table de 
   représentation des types. Les derniers paramètres de la procédure correspondent à nbParams fois 
   deux entiers indiquants, pour chaque paramètre :
    - Son numéro lexicographique
    - Son type 
   La fonction renvoit l'emplacement des données dans la table */
int tt_ajoutProcedure(int nbParams, ...);



/* Renvoie le nombre de champs de la structure se trouvant à posStruct */
int tt_structNbChamps (int posStruct);

/* Renvoie l'index du champs i (indexé à 0) de la structure se trouvant à posStruct */
int tt_structIndexChamp (int posStruct, int i);

/* Renvoie le numéro lexicographique du nom du champs i (indexé à 0) de la structure 
   se trouvant à posStruct */
int tt_structNumLexChamp (int posStruct, int i);

/* Renvoie le déplacement du champs i (indexé à 0) à l'intérieur de la structure se 
   trouvant à posStruct */
int tt_structDeplacementChamp (int posStruct, int i);



/* Renvoie le type des éléments du tableau se trouvant à posTab */
int tt_tabTypeElem (int posTab);

/* Renvoie le nombre de dimensions du tableau se trouvant à posTab */
int tt_tabNbDimensions (int posTab);

/* Renvoie la borne inférieure de la dimension i (indexé à 0) du tableau se trouvant à posTab */
int tt_tabDimBornInf (int posTab, int i);

/* Renvoie la borne supérieure de la dimension i (indexé à 0) du tableau se trouvant à posTab */
int tt_tabDimBornSup (int posTab, int i);



/* Renvoie le type de retour de la fonction se trouvant à posFonc */
int tt_foncTypeRetour (int posFonc);

/* Renvoie le nombre de paramètres de la fonction se trouvant à posFonc */
int tt_foncNbParam (int posFonc);

/* Renvoie le numéro lexicographique du paramètre i (indexé à 0) de la fonction se 
   trouvant à posFonc */
int tt_foncNumLexParam (int posFonc, int i);

/* Renvoie le type du paramètre i (indexé à 0) de la fonction se trouvant à posFonc */
int tt_foncTypeParam (int posFonc, int i);



/* Renvoie le nombre de paramètres de la procédure se trouvant à posProc */
int tt_procNbParam (int posProc);

/* Renvoie le numéro lexicographique du paramètre i (indexé à 0) de la procédure se 
   trouvant à posProc */
int tt_procNumLexParam (int posProc, int i);

/* Renvoie le type du paramètre i (indexé à 0) de la procédure se trouvant à posProc */
int tt_procTypeParam (int posProc, int i);


/* Affiche le tableau des types dans le terminal */
void tt_afficher();

/* Ecrit la table vers le fichier ouvert f */
void tt_ecrireFichier (FILE *f);
#endif