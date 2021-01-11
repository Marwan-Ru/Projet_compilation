#include "tabledecl.h"

/*Fonction interne utilisée pour renvoyer une variable de type decl qui correspond a une erreur*/
decl declerr(){
    decl d;
    d.exec = -1;
    d.index = -1;
    d.NATURE = -1;
    d.numregion = -1;
    d.suivant = -1;
    return d;
}

decl* tabledecl;

/*Initialise la table des declarations*/
int td_init(){
    int i;

    /*ON allout la place pour la tableprincipale et également la table de debordement*/
    tabledecl = allocation_mem(T_TABLEDEBORD + T_TABLELEX, sizeof(decl));
    
    for(i=0; i<T_TABLEDEBORD + T_TABLELEX; i++){ 
        tabledecl[i] = declerr();
    }
    /*On remplis le champs exec des types de base*/
    tabledecl[0].exec = sizeof(int);
    tabledecl[1].exec = sizeof(float);
    tabledecl[2].exec = sizeof(int); /*Un booleen est simplement un int*/
    tabledecl[3].exec = sizeof(char);

    return 0;
}
/*
 *Ajoute une declaration de type nature
 *a partir de son nom (utilisation de la table lexico), 
 *sa nature (struct ou table) et la valeur adéquate du champs index
 *(recuperation du retour de la fonction d'ajout dans la table des types).
 *retourne 0 si tout s'est passé correctement
 */
int td_ajout(int nature, char * nom, int numregion, int index, int exec){
    int pos = td_getlastdeclnum(nom);
    
    if(!tl_existe(nom)){
        fprintf(stderr, "Tentative de declaration avec un lexeme qui n'est pas dans la table des lexicaux\n");
        return -1;
    }
    
    if(tabledecl[pos].NATURE != -1){ /*Si on a déja une entrée sur cette déclaration on va chercher une place de libre dans la table de debordement*/
        pos = T_TABLELEX + 1;
        while(tabledecl[pos].NATURE != -1 && pos < T_TABLELEX + T_TABLEDEBORD) pos++;
    }
    tabledecl[td_getlastdeclnum(nom)].suivant = pos;

    tabledecl[pos].NATURE = nature;
    tabledecl[pos].numregion = numregion;
    tabledecl[pos].suivant = -1;
    tabledecl[pos].index = index;
    tabledecl[pos].exec = exec;

    return 0;
}

/* Permet de définir tous les champs de la ligne i */
void td_set (int i, int nature, int numregion, int suivant, int index, int exec) {
    tabledecl[i].NATURE = nature;
    tabledecl[i].numregion = numregion;
    tabledecl[i].suivant = suivant;
    tabledecl[i].index = index;
    tabledecl[i].exec = exec;
}

/*Renvoie la declaration stockée a la position num de la table des declarations*/
decl td_getdecl(int num){
    if(num > T_TABLEDEBORD + T_TABLELEX){
        return declerr();
    }
    return tabledecl[num];
}

/*Pour avoir la position a partir du nom il suffit d'utiliser la table lexicographique*/

/*Donne la derniere declaration de ce nom (ou declerr si elle n'existe pas)*/
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

/*Renvoie la position dans la table de la derniere declaration qui porte ce nom*/
int td_getlastdeclnum(char * nom){
    int pos = tl_getLexNum(nom);
    decl rep = td_getdecl(pos);
    decl suivant;
    if(rep.suivant != -1){
        suivant = td_getdecl(rep.suivant);
        pos = rep.suivant;
        while(suivant.suivant != -1){
            pos = suivant.suivant;
            suivant = td_getdecl(suivant.suivant);
        }
    }
    return pos;
}

void td_afficher(){
  int i;
  printf("Table des déclarations :\n");
  printf("   num │ nature │ suivant │ region │ desc | exec |\n");
  
  for (i = 0; i < 32; i++) {
    printf("   %3d │  %6d│  %7d│  %9d│  %4d|  %4d|\n", i, tabledecl[i].NATURE, tabledecl[i].suivant, tabledecl[i].numregion, tabledecl[i].index, tabledecl[i].exec);
  }
  printf("Table de débordement\n");

  for (i = 501; i < 521; i++) {
    printf("   %3d │  %6d│  %7d│  %9d│  %4d|  %4d|\n", i, tabledecl[i].NATURE, tabledecl[i].suivant, tabledecl[i].numregion, tabledecl[i].index, tabledecl[i].exec);
  }
  printf("\n");
}

/* Ecrit la table vers le fichier ouvert f */
void td_ecrireFichier (FILE *f) {
    int i;
    for (i = 0; i < T_TABLEDEBORD + T_TABLELEX ; i++) {
        if (tabledecl[i].NATURE != -1)
            fprintf(f, "%d;%d;%d;%d;%d;%d\n", i, tabledecl[i].NATURE, tabledecl[i].numregion, tabledecl[i].suivant, tabledecl[i].index, tabledecl[i].exec);
    }

    /* Séparateur */
    fprintf(f, "---\n");
}

/*Supprime proprement la table des declarations renvoie 0 si tout est ok*/
int td_detruire(){
    free(tabledecl);
    return 0;
}