#ifndef _LISTE_PA_H_
#define _LISTE_PA_H_

#include <stdio.h>
#include "allocation.h"

typedef int element;

typedef struct cellule{
  element objet;
  struct cellule * suivant;
}struct_cellule;

typedef struct_cellule * liste;

/* renvoie la liste vide */
liste liste_vide();

/* teste si une liste est vide */
int est_liste_vide(liste l);

/*ajoute un element elem a la liste l */
liste inserer_element_liste(liste l, element elem);

/* renvoie le premier element de la liste l */
element renvoie_premier_liste(liste l);

/* supprime la premiere cellule de la liste l */
liste supprimer_premier_liste(liste l);

void afficher_liste (liste l);

#endif