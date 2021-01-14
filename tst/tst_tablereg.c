#include "tablereg.h"

int main () {
  int r1 = 25;
  int t1 = 50;
  int p1 = 58;

  /* pile p = pile_vide();
  p = empiler(p, 1);
  p = empiler(p, 2);
  p = depiler(p);
  printf("sommet pile : %d \n", sommet_pile(p)); */

  tr_init();

  /*c1 = get_reg(10);*/
  /* printf("petit test : %d | %d \n", r1, t1); */

  if (tr_reg_existe(9)) printf("la région existe 9 \n");
  else printf("la région 9 n'existe pas \n");
  printf("\n\n");
  tr_affiche ();

  tr_ajout_taille(9, 3);
  tr_affiche ();

  tr_ajout_nis(9, 3);

  tr_ajout_taille(1, 3);
  tr_ajout_taille(2, 3);
  tr_ajout_taille(3, 1);
  tr_affiche ();

  /*reg_detruire ();*/
  exit(0);
}
