#ifndef TABLEREG
#define TABLEREG

#include <stdlib.h>
#include <stdio.h>
#include "allocation.h"
#include "arbreAbstrait.h"

/*Struct region :
   - taille_zone : La taille de la zone de données associée dans la pile à l'exécution
   - niv_imbric : Le niveau d'imbrication statique de la région
   - arbre : Le pointeur vers l'arbre abstrait des instructions de cette région*/
typedef struct {
  int taille_zone; 
  int niv_imbric;
  arbre tree;
} region;

#define NB_REGIONS 500

/*Initialisation d'une table des regions (tableau de type region de taille NB_REGIONS
  les champs sont initialisés à -1, sauf tree à NULL*/
void tr_init();

/*Ajout d'une region à partir de son numéro de région (nreg)*/
void tr_ajout_reg (int nreg, int taillez, int niv, arbre a);

/*Ajout de la taille à la région de numéro num*/
void tr_ajout_taille (int num, int taille);

/*Ajout du NIS à la région de numéro num*/
void tr_ajout_nis (int num, int nis);

/*Ajout d'un arbre a, à la region de numéro num*/
void tr_ajout_arbre (int num, arbre a);

/*Retourne le nombre de régions dans la table*/
int tr_taille();

/*Renvoie la région de numéro num_reg*/
region tr_get_reg (int num_reg);

/*Renvoie 1 si la région de numéro num_reg existe et 0 sinon*/
int tr_reg_existe (int num_reg);

/*Affiche la table des régions*/
void tr_affiche ();

/*Affichage des arbres dans le main*/
void tr_afficherArbres ();

/* Ecrit la table vers le fichier ouvert f */
void tr_ecrireFichier (FILE *f);

#endif
