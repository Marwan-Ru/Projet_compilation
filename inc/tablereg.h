#ifndef TABLEREG
#define TABLEREG

#include <stdlib.h>
#include <stdio.h>
#include "allocation.h"

/*Struct champ :
   - taille_zone : La taille de la zone de données associée dans la pile à l'exécution
   - niv_imbric : Le niveau d'imbrication statique de la région
   - arbre : Le pointeur vers l'arbre abstrait des instructions de cette région*/
typedef struct {
  int taille_zone; 
  int niv_imbric;
  void *arbre; /*à verif*/
} champ;

#define NB_REGIONS 10

void init();

void ajout_reg (int num_reg, int taillez, int niv, void *pointeur);

champ get_reg (int num_reg);

int reg_existe (int num_reg);

void affiche ();

void reg_detruire ();

#endif
