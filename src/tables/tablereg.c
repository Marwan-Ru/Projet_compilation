/*       Auteur: Paul-Antoine Bernard
 *  Description: Module gérant la table des régions. 
 *  Utilisation: tr_init() permet l'initialisation de la table
 *       Résumé: Contient les fonctions d'ajout de régions,
 *               d'affichage, de récupération de régions.
 */

#include "tablereg.h"

region tablereg[NB_REGIONS];

/*Initialisation d'une table des regions (tableau de type region de taille NB_REGIONS
  les champs sont initialisés à -1, sauf tree à NULL*/
void tr_init() {
  int i;
  for (i = 0; i < NB_REGIONS; i++) {
    tablereg[i].taille_zone = -1;
    tablereg[i].niv_imbric = -1;
    tablereg[i].tree = NULL;
  }
}

/*Ajout d'une region à partir de son numéro de région (nreg)*/
void tr_ajout_reg (int nreg, int taillez, int niv, arbre a) {
  if (nreg > NB_REGIONS ){
    printf("erreur table region (tr_ajout_reg) : dépassement borne table \n");
    exit(-1);
  }

  tablereg[nreg].taille_zone = taillez;
  tablereg[nreg].niv_imbric = niv;
  tablereg[nreg].tree = a;
}

/*Ajout de la taille à la région de numéro num*/
void tr_ajout_taille (int num, int taille) {
  if (num > NB_REGIONS ){
    printf("erreur table region (tr_ajout_reg) : dépassement borne table \n");
    exit(-1);
  }

  tablereg[num].taille_zone = taille;
}

/*Ajout du NIS à la région de numéro num*/
void tr_ajout_nis (int num, int nis) {
  if (num > NB_REGIONS ){
    printf("erreur table region (tr_ajout_reg) : dépassement borne table \n");
    exit(-1);
  }

  tablereg[num].niv_imbric = nis;
}

/*Ajout d'un arbre a, à la region de numéro num*/
void tr_ajout_arbre (int num, arbre a) {
  if (num > NB_REGIONS ){
    printf("erreur table region (tr_ajout_reg) : dépassement borne table \n");
    exit(-1);
  }

  tablereg[num].tree = a;
}

/*Retourne le nombre de régions dans la table*/
int tr_taille () {
  int i = 0;
  while (tablereg[i].taille_zone != -1) {
    i++;
  }

  return i;
}

/*Renvoie la région de numéro num_reg*/
region tr_get_reg (int num_reg) {
  if (num_reg > NB_REGIONS){
    printf("erreur table region (tr_get_reg) : dépassement borne table \n");
    exit(-1);
  }

  return tablereg[num_reg];
}

/*Renvoie 1 si la région de numéro num_reg existe et 0 sinon*/
int tr_reg_existe (int num_reg) { /*Si c'est implémenté ou pas encore dans la table*/
  if (num_reg > NB_REGIONS){
    return 0;
  }
  else if (tablereg[num_reg].taille_zone != -1) return 1;
  else return 0;
}

/*Affiche la table des régions*/
void tr_affiche () {
  int i;
  printf("Table des régions :\n");
  printf("   │ num │ taille │  NIS │ arbre\n");
  
  for (i = 0; i < NB_REGIONS-480; i++) {
    /*printf("region[%d] : taille_zone : %d -- niv_imbric : %d -- pointeur arbre : %p \n", i, tablereg[i].taille_zone, tablereg[i].niv_imbric, (void *) tablereg[i].arbre);*/
    printf("   │  %3d│  %5d │  %3d │%p\n", i, tablereg[i].taille_zone, tablereg[i].niv_imbric, (void *) tablereg[i].tree);
  }
  printf("\n");
}

/*Affichage des arbres dans le main*/
void tr_afficherArbres () {
  int i, tot = tr_taille();
  for (i = 0; i < tot; i++) {
    printf("Région %d:\n", i);
    aa_afficher(tablereg[i].tree);
  }
}

/* Ecrit la table vers le fichier ouvert f */
void tr_ecrireFichier (FILE *f) {
  int i, tot = tr_taille();

  for (i = 0; i < tot; i++) {
    fprintf(f, "%d;%d;%d;", i, tablereg[i].taille_zone, tablereg[i].niv_imbric);

    /* arbre */
    aa_ecrireFichier(f, tablereg[i].tree);
  }

  /* Séparateur */
    fputs("---\n", f);
}
