#include <stdio.h>
#include "pile.h"

pile pile_vide()
{
  return liste_vide();
}

int est_pile_vide(pile p)
{
  return est_liste_vide(p);
}

pile empiler(pile p,element e)
{
  return inserer_element_liste(p,e);
}

element sommet_pile(pile p)
{
  return renvoie_premier_liste(p);
}

pile depiler(pile p)
{
  return supprimer_premier_liste(p);
}

int taille_pile(pile p)
{
  int nb=0;
  liste lcourant=p;
  while(lcourant)
    {
      nb++;
      lcourant=lcourant->suivant;
    }
  return nb;
}

void liberer_pile (pile l) {
  while (!est_pile_vide(l))
    l = supprimer_premier_liste(l);
}
