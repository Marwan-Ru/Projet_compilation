/*       Auteur: Ait Addi Marwan
 *  Description: Module gérant la table des declaration. 
 *  Utilisation: td_init() permet l'initialisation de la table
 *       Résumé: Contient les fonctions d'ajout de declaration et d'acces a la table
 */

#ifndef TABLEDECL
#define TABLEDECL

#include <stdlib.h>
#include <stddef.h>
#include "allocation.h"
#include "pileEnt.h"
#include "tableLex.h"

#define T_TABLEDEBORD 5000

enum nature{TYPE_S, TYPE_T, VARI, PARAM, PROC, FUNCT, TYPE_B};

typedef struct s_decl{
    int NATURE;     /*Ce champs peut prendre les valeurs de l'enumeration nature (ou -1 si vide)*/
    int suivant;    /*Chainage vers la prochaine decl de meme nom (dans le debordement)*/
    int numregion;  /*Numero de region contenant la declaration    */ 
    /*
    *si NATURE = TYPE_S ou NATURE = TYPE_T (déclaration d'un type structure ou tableau) : 
    *   index dans la table contenant la description du type (table de représentation des types et des entêtes de sous-programmes).
    *si NATURE = VARI ou NATURE = PARAM (déclaration d'une variable ou d'un paramètre) : 
    *   index, dans la table des déclarations, de l'enregistrement associé à la déclaration du type de la variable ou du paramètre 
    *   dont on mémorise la déclaration. Si cette valeur vaut 0, 1, 2, ou 3, il s'agit d'un type de base (entier, réel, booléen ou caractère).
    *si NATURE = PROC ou NATURE = FUNCT (déclaration d'une procédure ou d'une fonction) : 
    *   index dans la table contenant la description de l'entête de la procédure ou de la fonction (table de représentation des types 
    *   et des entêtes de sous-programmes).
    */
    int index; 
    /*
    *si NATURE = TYPE_S ou NATURE = TYPE_T : taille à l'exécution d'une valeur de ce type (en tenant compte qu'il s'agit d'une machine C, cf ci-dessous).
    *si NATURE = VARI ou NATURE = PARAM : déplacement à l'exécution, de l'emplacement associé à la variable ou du paramètre dans la zone de données correspondante.
    *si NATURE = PROC ou NATURE = FUNCT : numéro de la région associée à la procédure ou à la fonction.
    */
    int exec;
}decl;

/*Initialise la table des declarations
* auteur : Marwan Ait Addi
*/
int td_init();

/*
 *Ajoute une declaration de type nature
 *a partir de son numéro lexicographique, 
 *sa nature (struct ou table) et la valeur adéquate du champs index
 *(recuperation du retour de la fonction d'ajout dans la table des types).
 * Renvoie un message descriptif lors d'une erreur, NULL sinon
 * auteur : Marwan Ait Addi
 */
char *td_ajout(int numLex, int nature, int numregion, int index, int exec);

/* Renvoie le numéro de déclaration de l'objet de nature n et de numéro lexicographique numLex
   ayant été déclaré dans la plus profonde région du contexte des régions englobante donné.
   Renvoie -1 si rien a été trouvé.
   Auteur: Gustav Hubert */
int td_assocNom (int numLex, enum nature n, pileEnt contexte);

/* Permet de définir tous les champs de la ligne i 
 * auteur : Marwan Ait Addi
 */
void td_set (int i, int nature, int numregion, int suivant, int index, int exec);

/*Renvoie la declaration stockée a la position num de la table des declarations
auteur : Marwan Ait Addi*/
decl td_getdecl(int num);

/*Donne la derniere declaration ayant ce numéro (ou declerr si elle n'existe pas)
auteur : Marwan Ait Addi*/
decl td_getlastdecl(int numLex);

/*Affiche une partie de la table dans la console
auteur : Marwan Ait Addi*/
void td_afficher();

/* Ecrit la table vers le fichier ouvert f 
auteur : Marwan Ait Addi*/
void td_ecrireFichier (FILE *f);

/* Renvoie le numéro lexicographique d'une déclaration 
auteur : Marwan Ait Addi*/
int td_getNumLex (int numDecl);

/*Supprime proprement la table des declarations renvoie 0 si tout est ok
auteur : Marwan Ait Addi*/
int td_detruire();


#endif