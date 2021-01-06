#ifndef TABLEREG
#define TABLEREG

#include <stdlib.h>
#include <stdio.h>
#include "allocation.h"
#include "arbreAbstrait.h"

/*Struct champ :
   - taille_zone : La taille de la zone de données associée dans la pile à l'exécution
   - niv_imbric : Le niveau d'imbrication statique de la région
   - arbre : Le pointeur vers l'arbre abstrait des instructions de cette région*/
typedef struct {
  int taille_zone; 
  int niv_imbric;
  arbre tree;
} champ;

#define NB_REGIONS 500


void tr_init();

void tr_ajout_reg (int nreg, int taillez, int niv, arbre a);

void tr_ajout_taille (int num, int taille);

void tr_ajout_nis (int num, int nis);

void tr_ajout_arbre (int num, arbre a);

int tr_taille();

void tr_ajout_taille_prog_princ (int nis, int taille);

champ tr_get_reg (int num_reg);

int tr_reg_existe (int num_reg);

void tr_affiche ();

void tr_afficherArbres ();

/* Ecrit la table vers le fichier ouvert f */
void tr_ecrireFichier (FILE *f);

#endif
