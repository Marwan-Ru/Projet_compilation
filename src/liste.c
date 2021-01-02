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


void afficher_liste (liste l)
{
 
  if (l == NULL) printf("vide \n");

  printf("liste : ");
  while (l != liste_vide())
    {
      l = l->suivant;
    }
  printf("\n");
}