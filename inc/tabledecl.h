#ifndef TABLEDECL
#define TABLEDECL

#include "allocation.h"

#define T_TABLEDECL 5000
#define T_TABLEPRINC 500 //dois être de la meme taille que la table des lexicaux

enum nature{TYPE_S, TYPE_S, VAR, PARAM, PROC, FUNCT};

typedef struct s_decl{
    int NATURE;     //Ce champs peut prendre les valeurs de l'enumeration nature (ou -1 si vide)
    int suivant;    //Chainage vers la prochaine decl de meme nom (dans le debordement)
    int numregion;  //Numero de region contenant la declaration     
    /*
    *si NATURE=1 ou NATURE=2 (déclaration d'un type structure ou tableau) : 
    *   index dans la table contenant la description du type (table de représentation des types et des entêtes de sous-programmes).
    *si NATURE=3 ou NATURE=4 (déclaration d'une variable ou d'un paramètre) : 
    *   index, dans la table des déclarations, de l'enregistrement associé à la déclaration du type de la variable ou du paramètre 
    *   dont on mémorise la déclaration. Si cette valeur vaut 0, 1, 2, ou 3, il s'agit d'un type de base (entier, réel, booléen ou caractère).
    *si NATURE=5 ou NATURE=6 (déclaration d'une procédure ou d'une fonction) : 
    *   index dans la table contenant la description de l'entête de la procédure ou de la fonction (table de représentation des types 
    *   et des entêtes de sous-programmes).
    */
    int index; 
    /*
    *si NATURE=1 ou NATURE=2 : taille à l'exécution d'une valeur de ce type (en tenant compte qu'il s'agit d'une machine C, cf ci-dessous).
    *si NATURE=3 ou NATURE=4 : déplacement à l'exécution, de l'emplacement associé à la variable ou du paramètre dans la zone de données correspondante.
    *si NATURE=5 ou NATURE=6 : numéro de la région associée à la procédure ou à la fonction.
    */
    int exec;
}decl;

/*Initialise la table des declarations*/
decl* td_init();

/*
 *Ajoute une declaration a partir de son type 
 *et son nom (utilisation de la table lexico), 
 *retourne 0 si tout s'est passé correctement
 */
int td_add(decl* table, int nature, char * nom, int numregion);

/*Renvoie la declaration stockée a la position num de la table des declarations*/
decl td_getobj(int num);

/*Pour avoir la position a partir du nom il suffit d'utiliser la table lexicographique
 *Donne la derniere declaration de ce nom (ou -1 si elle n'existe pas)*/
decl td_getlastdecl(char* nom);


#endif