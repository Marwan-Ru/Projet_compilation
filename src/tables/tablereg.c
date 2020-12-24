#include "tablereg.h"

champ tablereg[NB_REGIONS];

void tr_init() {
  int i;
  for (i = 0; i < NB_REGIONS; i++) {
    tablereg[i].taille_zone = -1;
    tablereg[i].niv_imbric = -1;
    /* tablereg[i].arbre = allocation_mem(1, sizeof(int*)); */ /*TO DO : changer en bon type*/
  }
}

void tr_ajout_reg (int nreg, int taillez, int niv, int *pointeur) { /*TO DO : changer en bon type*/
  if (nreg > NB_REGIONS ){
    printf("erreur table region (tr_ajout_reg) : dépassement borne table \n");
    exit(-1);
  }

  tablereg[nreg].taille_zone = taillez;
  tablereg[nreg].niv_imbric = niv;
  tablereg[nreg].arbre = pointeur;

  nreg++;
}

champ tr_get_reg (int num_reg) {
  if (num_reg > NB_REGIONS){
    printf("erreur table region (tr_get_reg) : dépassement borne table \n");
    exit(-1);
  }

  return tablereg[num_reg];
}

int tr_reg_existe (int num_reg) { /*Si c'est implémenté ou pas encore dans la table*/
  if (num_reg > NB_REGIONS){
    return 0;
  }
  else if (tablereg[num_reg].taille_zone != -1) return 1;
  else return 0;
}

void tr_affiche () {
  int i;
  for (i = 0; i < NB_REGIONS-480; i++) {
    /*printf("region[%d] : taille_zone : %d -- niv_imbric : %d -- pointeur arbre : %p \n", i, tablereg[i].taille_zone, tablereg[i].niv_imbric, (void *) tablereg[i].arbre);*/
    printf("%3d│%5d│%3d│%p│\n", i, tablereg[i].taille_zone, tablereg[i].niv_imbric, (void *) tablereg[i].arbre);
  }
}

void tr_detruire () {
  int i;
  for (i = 0; i < NB_REGIONS; i++) {
    libere_mem(tablereg[i].arbre);
  }
}
