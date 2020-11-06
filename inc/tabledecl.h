#ifndef TABLEDECL
#define TABLEDECL

#include "allocation.h"

#define T_TABLEDECL 5000
#define T_TABLEPRINC 500 //dois être de la meme taille que la table des lexicaux

enum nature{TYPE_S, TYPE_S, VAR, PARAM, PROC, FUNCT};

typedef struct s_decl{
    int NATURE;     //Ce champs peut prendre les valeurs de l'enumeration nature (ou -1 si vide)
    int suivant;    //Chainage vers la prochaine decl de meme nom (dans le debordement)
    int numregion;  
    int index;
    int exec;
}decl;

/*Initialise la table des declarations*/
void td_init();

/*Ajoute une declaration a partir de son type et son nom (utilisation de la table lexico), retourne 0 si tout s'est passé correctement*/
int td_add(int type, char * nom);

/*Renvoie la*/
decl td_get(char * nom);

#endif