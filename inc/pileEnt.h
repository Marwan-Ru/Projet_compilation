#ifndef _PILE_H_
#define _PILE_H_

#include "liste.h"

typedef liste pileEnt;

pileEnt pile_vide();

int est_pile_vide(pileEnt p);

pileEnt empiler(pileEnt p, element e);

element sommet_pile(pileEnt p);

pileEnt depiler(pileEnt p);

int taille_pile(pileEnt p);

void liberer_pile (pileEnt l);

int dans_pile (int x, pileEnt p);

void afficher_pile (pileEnt p);

#endif