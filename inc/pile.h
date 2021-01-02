#ifndef _PILE_H_
#define _PILE_H_

#include "liste_pa.h"

typedef liste pile;

pile pile_vide();

int est_pile_vide(pile p);

pile empiler(pile p,element e);

element sommet_pile(pile p);

pile depiler(pile p);

int taille_pile(pile p);

#endif