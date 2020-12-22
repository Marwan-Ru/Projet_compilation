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
int td_ajout(decl* table, int nature, char * nom, int numregion){
    if(!lexemeExiste(nom)){
        fprintf(stderr, "Tentative de declaration avec un lexeme qui n'est pas dans la table des lexicaux\n");
        return -1;
    }
    decl d = td_getdecl(tl_getLexNum(nom));
    if(d.suivant == -1){    /*On a pas de suivant*/
        if(d.NATURE == -1){ /*Le lexeme n'as pas encore été déclaré*/
            d.NATURE = nature;
            d.numregion = numregion;
            if(nature == TYPE_S || nature == TYPE_T){
                d.index = 0;
                /*A faire plut tard recupere l'index dans la table des types*/
            }else if(nature = VAR || nature == PARAM){
                d.index = 0;
                /*index, dans la table des déclarations, de l'enregistrement associé à la déclaration du type de la variable ou du paramètre 
                dont on mémorise la déclaration*/
            }else if(nature == PROC || nature == FUNCT){
                /*index dans la table contenant la description de l'entête de la procédure ou de la fonction (table de représentation des types 
                et des entêtes de sous-programmes)*/
                d.index = 0;
            }
        }
    }
}
/*Renvoie la declaration stockée a la position num de la table des declarations*/
decl td_getdecl(int num){
    if(num > T_TABLEDECL + T_TABLEPRINC) return NULL;
    return tabledecl[num];
}

/*Pour avoir la position a partir du nom il suffit d'utiliser la table lexicographique*/

/*Donne la derniere declaration de ce nom (ou -1 si elle n'existe pas)*/
decl td_getlastdecl(char* nom){
    int pos = tl_getLexNum(nom);
    decl rep = td_getdecl(pos);
    decl suivant;
    if(rep.suivant == 0)
        return rep;
    else{
        suivant = td_getdecl(rep.suivant);
        while(suivant.suivant != 0){
            suivant = td_getdecl(suivant.suivant);
        }
        return suivant;
    }
}

/*Supprime proprement la table des declarations renvoie 0 si tout est ok*/
int td_detruire(){
    free(tabledecl);
    return 0;
}