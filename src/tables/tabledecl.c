/*       Auteur: Ait Addi Marwan
 *  Description: Module gérant la table des declaration. 
 *  Utilisation: td_init() permet l'initialisation de la table
 *       Résumé: Contient les fonctions d'ajout de declaration et d'acces a la table
 */

#include "tabledecl.h"

/*Fonction interne utilisée pour renvoyer une variable de type decl qui correspond a une erreur
auteur : Marwan Ait Addi*/
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

/*Initialise la table des declarations
auteur : Marwan Ait Addi*/
int td_init(){
    int i;

    /*ON allout la place pour la tableprincipale et également la table de debordement*/
    tabledecl = allocation_mem(T_TABLEDEBORD + T_TABLELEX, sizeof(decl));
    
    for(i=0; i<T_TABLEDEBORD + T_TABLELEX; i++){ 
        tabledecl[i] = declerr();
    }
    /*On remplis le champs exec des types de base*/
    for (i=0;i<4;i++) {
        tabledecl[i].exec = 1;
        tabledecl[i].numregion = 0;
        tabledecl[i].NATURE = TYPE_B;
    }

    return 0;
}
/*
 *Ajoute une declaration de type nature
 *a partir de son numéro lexicographique, 
 *sa nature (struct ou table) et la valeur adéquate du champs index
 *(recuperation du retour de la fonction d'ajout dans la table des types).
 * Renvoie un message descriptif lors d'une erreur, NULL sinon
 * auteur : Marwan Ait Addi*/
char * td_ajout(int numLex, int nature, int numregion, int index, int exec){
    int pos = numLex, newPos, i, decal = exec;

    /* On remonte dans les délarations ayant le même num lex */
    /* On vérifie également qu'il n'y ai pas deux déclations de même types et noms dans cette région */
    while (tabledecl[pos].suivant != -1) {
        if (tabledecl[pos].NATURE == nature && tabledecl[pos].numregion == numregion)
            return "Une déclaration de ce type existe déjà!";
        pos = tabledecl[pos].suivant;
    }

    /*Si on a déja une entrée sur cette déclaration on va chercher une place de libre dans la table de debordement*/
    if (tabledecl[pos].NATURE != -1) {
        newPos = T_TABLELEX + 1;
        while(tabledecl[newPos].NATURE != -1 && pos < T_TABLELEX + T_TABLEDEBORD) newPos++;
        tabledecl[pos].suivant = newPos;
        pos = newPos;
    }

    if (pos >= T_TABLELEX + T_TABLEDEBORD) {
        return "La table des déclarations est remplie!";
    }

    tabledecl[pos].NATURE = nature;
    tabledecl[pos].numregion = numregion;
    tabledecl[pos].suivant = -1;
    tabledecl[pos].index = index;
    /* On regarde le numero de region pour le decalage si c'est un PARAM ou VARI*/
    if(nature == PARAM || nature == VARI){
        /*Chainage dynamique = 1 sauf pour la region 0*/
        if(numregion != 0) decal++;
        
        for(i=0;i<T_TABLEDEBORD + T_TABLELEX - 1;i++){
            if(tabledecl[i].NATURE == nature && tabledecl[i].numregion == numregion && i != pos) 
                decal += td_getdecl(tabledecl[i].index).exec;
        }
        tabledecl[pos].exec = decal;
    }else tabledecl[pos].exec = exec;
    return NULL;
}

/* Permet de définir tous les champs de la ligne i 
auteur : Marwan Ait Addi*/
void td_set (int i, int nature, int numregion, int suivant, int index, int exec) {
    tabledecl[i].NATURE = nature;
    tabledecl[i].numregion = numregion;
    tabledecl[i].suivant = suivant;
    tabledecl[i].index = index;
    tabledecl[i].exec = exec;
}

/*Renvoie la declaration stockée a la position num de la table des declarations
auteur : Marwan Ait Addi*/
decl td_getdecl(int num){
    if(num > T_TABLEDEBORD + T_TABLELEX){
        return declerr();
    }
    return tabledecl[num];
}

/*Donne la derniere declaration ayant ce numéro (ou declerr si elle n'existe pas)
auteur : Marwan Ait Addi*/
decl td_getlastdecl(int numLex){
    while (tabledecl[numLex].suivant != -1) numLex = tabledecl[numLex].suivant;
    return tabledecl[numLex];
}

/* Renvoie le numéro de déclaration de l'objet de nature n et de numéro lexicographique numLex
   ayant été déclaré dans la plus profonde région du contexte des régions englobante donné.
   Renvoie -1 si rien a été trouvé.
   Auteur: Gustav Hubert */
int td_assocNom (int numLex, enum nature n, pileEnt contexte) {
    int regMax = 0, regionUtilisation = sommet_pile(contexte);
    int declMax = -1;

    do {   
        if (tabledecl[numLex].numregion <= regionUtilisation && tabledecl[numLex].numregion >= regMax &&
            (tabledecl[numLex].NATURE == n || tabledecl[numLex].NATURE == n+1) && dans_pile(tabledecl[numLex].numregion, contexte)) {
            declMax = numLex;
            regMax = tabledecl[numLex].numregion;
        }
        numLex = tabledecl[numLex].suivant;
    } while (numLex != -1);

    return declMax;
}

/*auteur : Gustab Hubert*/
char *natureVersTexte (int nature) {
    switch (nature) {
        case TYPE_S: return "TYPE_S";
        case TYPE_T: return "TYPE_T";
        case VARI: return "VAR";
        case PARAM: return "PARAM";
        case PROC: return "PROC";
        case FUNCT: return "FONC";
        case TYPE_B: return "TYPE_B"; 
        default: return "-1";
    }
}

/*Affiche une partie de la table dans la console
auteur : Marwan Ait Addi*/
void td_afficher(){
  int i;
  printf("Table des déclarations :\n");
  printf("   num │ nature │ suivant │ region │ desc | exec |\n");
  
  for (i = 0; i < 32; i++) {
    printf("   %3d │  %6s│  %7d│  %6d│  %4d|  %4d|\n", i, natureVersTexte(tabledecl[i].NATURE), tabledecl[i].suivant, tabledecl[i].numregion, tabledecl[i].index, tabledecl[i].exec);
  }
  printf("Table de débordement\n");

  for (i = 501; i < 521; i++) {
    printf("   %3d │  %6s│  %7d│  %6d│  %4d|  %4d|\n", i, natureVersTexte(tabledecl[i].NATURE), tabledecl[i].suivant, tabledecl[i].numregion, tabledecl[i].index, tabledecl[i].exec);
  }
  printf("\n");
}

/* Ecrit la table vers le fichier ouvert f 
auteur : Marwan Ait Addi*/
void td_ecrireFichier (FILE *f) {
    int i;
    for (i = 0; i < T_TABLEDEBORD + T_TABLELEX ; i++) {
        if (tabledecl[i].NATURE != -1)
            fprintf(f, "%d;%d;%d;%d;%d;%d\n", i, tabledecl[i].NATURE, tabledecl[i].numregion, tabledecl[i].suivant, tabledecl[i].index, tabledecl[i].exec);
    }

    /* Séparateur */
    fprintf(f, "---\n");
}

/* Renvoie le numéro lexicographique d'une déclaration 
auteur : Marwan Ait Addi*/
int td_getNumLex (int numDecl) {
    int i = 0;

    while (numDecl > 0 && numDecl < T_TABLELEX + T_TABLEDEBORD-1 && numDecl > T_TABLELEX) {
        for (i = 0; i < T_TABLELEX + T_TABLEDEBORD; i++) {
            if (tabledecl[i].suivant == numDecl) {
                numDecl = i;
                break;
            }
        }
    }

    return numDecl;
}

/*Supprime proprement la table des declarations renvoie 0 si tout est ok
auteur : Marwan Ait Addi*/
int td_detruire(){
    free(tabledecl);
    return 0;
}