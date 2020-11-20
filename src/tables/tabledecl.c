#include <stdlib.h>
#include "tabledecl.h"
#include "tableLex.h"

decl* tabledecl;

/*Initialise la table des declarations*/
decl* td_init(){
    tabledecl = allocation_mem(T_TABLEDECL + T_TABLEPRINC, sizeof(decl));
    int i = 0;
    for(i=0; i<T_TABLEDECL + T_TABLEPRINC; i++){
        tabledecl[i].NATURE = -1;
        tabledecl[i].suivant = -1;
        tabledecl[i].index = -1;
        tabledecl[i].numregion = -1;
        tabledecl[i].exec = -1;
    }
}

/*
 *Ajoute une declaration a partir de son type 
 *et son nom (utilisation de la table lexico), 
 *retourne 0 si tout s'est passé correctement
 */
int td_add(decl* table, int nature, char * nom, int numregion){
    if(!lexemeExiste(nom)){
        fprintf(stderr, "Tentative de declaration avec un lexeme qui n'est pas dans la table des lexicaux\n");
        return -1;
    }
}

/*Renvoie la declaration stockée a la position num de la table des declarations*/
decl td_getobj(int num);

/*Pour avoir la position a partir du nom il suffit d'utiliser la table lexicographique*/

/*Donne la derniere declaration de ce nom (ou -1 si elle n'existe pas)*/
decl td_getlastdecl(char* nom);