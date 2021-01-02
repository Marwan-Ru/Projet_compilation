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
  int *arbre; /*TO DO : changer en bon type*/
} champ;

#define NB_REGIONS 500


void tr_init();

void tr_ajout_reg (int nreg, int taillez, int niv, int *pointeur); /*TO DO : changer en bon type*/

void tr_ajout_taille (int num, int taille);

void tr_ajout_nis (int num, int nis);

void tr_ajout_arbre (int num, int *tree);

champ tr_get_reg (int num_reg);

int tr_reg_existe (int num_reg);

void tr_affiche ();

/* Ecrit la table vers le fichier ouvert f */
void tr_ecrireFichier (FILE *f);

void tr_detruire ();

#endif
