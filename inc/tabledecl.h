#ifndef TABLEDECL
#define TABLEDECL

#include <stdlib.h>
#include <stddef.h>
#include "allocation.h"
#include "tableLex.h"

#define T_TABLEDEBORD 5000

enum nature{TYPE_S, TYPE_T, VARI, PARAM, PROC, FUNCT};

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

/*Initialise la table des declarations*/
int td_init();

/*
 *Ajoute une declaration de type nature
 *a partir de son nom (utilisation de la table lexico), 
 *sa nature (struct ou table) et la valeur adéquate du champs index
 *retourne 0 si tout s'est passé correctement
 */
int td_ajout(int nature, char * nom, int numregion, int index, int exec);

/*Renvoie la declaration stockée a la position num de la table des declarations*/
decl td_getdecl(int num);

/*Pour avoir la position a partir du nom il suffit d'utiliser la table lexicographique
 *Donne la derniere declaration de ce nom (ou declerr si elle n'existe pas)*/
decl td_getlastdecl(char* nom);

/*Renvoie la position dans la table de la derniere declaration qui porte ce nom*/
int td_getlastdeclnum(char * nom);

/*Affiche une partie de la table dans la console*/
void td_afficher();

/* Ecrit la table vers le fichier ouvert f */
void td_ecrireFichier (FILE *f);

/*Supprime proprement la table des declarations renvoie 0 si tout est ok*/
int td_detruire();


#endif