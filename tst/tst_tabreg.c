#include "tablereg.h"

int main () {
  int r1 = 25;
  int t1 = 50;
  int p1 = 58;
  champ c1;
  init();

  ajout_reg (10, r1, t1, &p1);
  c1 = get_reg(10);
  printf("petit test : %d | %d \n", r1, t1);

  if (reg_existe(9)) printf("la région existe 9 \n");
  else printf("la région 9 n'existe pas \n");
  printf("\n\n");
  affiche ();

  /*reg_detruire ();*/
  exit(0);
}
