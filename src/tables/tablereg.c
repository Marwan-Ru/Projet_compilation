#include "tablereg.h"

champ tablereg[NB_REGIONS];

void init() {
  int i;
  for (i = 0; i < NB_REGIONS; i++) {
    tablereg[i].taille_zone = -1;
    tablereg[i].niv_imbric = -1;
    /* tablereg[i].arbre = allocation_mem(1, sizeof(int*)); */ /*TO DO : changer en bon type*/
  }
}

void ajout_reg (int num_reg, int taillez, int niv, int *pointeur) { /*TO DO : changer en bon type*/
  if (num_reg > NB_REGIONS || num_reg < 1){
    printf("erreur cette région n'existe pas\n");
    exit(-1);
  }

  tablereg[num_reg-1].taille_zone = taillez;
  tablereg[num_reg-1].niv_imbric = niv;
  tablereg[num_reg-1].arbre = pointeur;
}

champ get_reg (int num_reg) {
  if (num_reg > NB_REGIONS || num_reg < 1){
    printf("erreur cette région n'existe pas\n");
    exit(-1);
  }

  return tablereg[num_reg-1];
}

int reg_existe (int num_reg) { /*Si c'est implémenté ou pas encore dans la table*/
  if (num_reg > NB_REGIONS || num_reg < 1){
    return 0;
  }
  else if (tablereg[num_reg-1].taille_zone != -1) return 1;
  else return 0;
}

void affiche () {
  int i;
  for (i = 0; i < NB_REGIONS; i++) {
    printf("region[%d] : taille_zone : %d -- niv_imbric : %d -- pointeur arbre : %d \n", i+1, tablereg[i].taille_zone, tablereg[i].niv_imbric, tablereg[i].arbre);
  }
}

void reg_detruire () {
  int i;
  for (i = 0; i < NB_REGIONS; i++) {
    libere_mem(tablereg[i].arbre);
  }
}
