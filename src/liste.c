/*       Auteur: Paul-Antoine Bernard
 *  Description: Module gérant les listes. 
 *       Résumé: Gérer des listes chaînées
 */

#include "liste.h"

liste liste_vide()
{
  return NULL;
}

int est_liste_vide(liste l)
{
  if(l==liste_vide())
    return 1;
  return 0;
}

liste inserer_element_liste(liste l,element elem)
{
  liste lnew=(liste)allocation_mem(1,sizeof(struct_cellule));
  lnew->objet=elem;
  lnew->suivant=l;
  return lnew;
}

element renvoie_premier_liste(liste l)
{
  if(est_liste_vide(l))
    printf("Erreur la liste est vide dans la fonction renvoie_premier\n");
  return l->objet;
}


liste supprimer_premier_liste(liste l)
{
  liste lsuivant=l->suivant;
  libere_mem(&l);
  return lsuivant;
}

int dans_liste (int x, liste l) {
  liste tmp = l;

  while (!est_liste_vide(tmp)) {
    if (x == renvoie_premier_liste(tmp)) return 1;
    tmp = tmp->suivant;    
  }
  return 0;
}


void afficher_liste (liste l) {
  liste tmp = l;

  if (tmp == NULL) printf("vide \n");

  while (tmp != liste_vide()) {
    printf("%d, ", tmp->objet);
    tmp = tmp->suivant;
  }

  printf("\n");
}