#include "tablereg.h"

int main () {
  int num = 0;
  int r1 = 25;
  int t1 = 50;
  int p1 = 58;
  champ c1;
  tr_init();

  tr_ajout_reg (0, r1, t1, &p1);
  tr_ajout_reg (9, 4, 2, &p1);
  /*c1 = get_reg(10);*/
  //printf("petit test : %d | %d \n", r1, t1);

  if (tr_reg_existe(9)) printf("la région existe 9 \n");
  else printf("la région 9 n'existe pas \n");
  printf("\n\n");
  tr_affiche ();

  /*reg_detruire ();*/
  exit(0);
}
