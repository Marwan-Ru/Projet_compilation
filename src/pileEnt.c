/*       Auteur: Paul-Antoine Bernard
 *  Description: Module gérant les piles. 
 *       Résumé: Gérer des piles à partir de listes chaînées
 */

#include <stdio.h>
#include "pileEnt.h"

pileEnt pile_vide()
{
  return liste_vide();
}

int est_pile_vide(pileEnt p)
{
  return est_liste_vide(p);
}

pileEnt empiler(pileEnt p,element e)
{
  return inserer_element_liste(p,e);
}

element sommet_pile(pileEnt p)
{
  return renvoie_premier_liste(p);
}

pileEnt depiler(pileEnt p)
{
  return supprimer_premier_liste(p);
}

int taille_pile(pileEnt p)
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

int dans_pile (int x, pileEnt p) {
  return dans_liste(x, p);
}

void liberer_pile (pileEnt l) {
  while (!est_pile_vide(l))
    l = supprimer_premier_liste(l);
}

void afficher_pile (pileEnt p) {
  afficher_liste (p);
}