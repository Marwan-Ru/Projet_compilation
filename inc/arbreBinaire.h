/*
 *      Auteur: Gustav HUBERT
 *        Date: 2020/04/04
 * Modifié le: 2020/11/31
 * Description: Fichier header du module implémentant
 *              les arbres binaires
 */ 

#ifndef ARBREBIN
#define ARBREBIN

#include <stdlib.h>
#include "allocation.h"

typedef struct struct_arbre {
    void *val;
    struct struct_arbre *fGauche;
    struct struct_arbre *fDroit;
} *arbre;

/* Renvoie un arbre nulle */
arbre ab_creerVide ();

/* Vérifie si l'arbre est vide */
int ab_estVide (arbre a);

/* Renvoie un arbre sans fils et ayant comme ab_getRacine val */
arbre ab_creerFeuille (void *val);

/* Renvoie un arbre ayant val pour ab_getRacine ainsi que
   filsgauche et filsdroit comme sous-arbre gauche 
   et sous-arbre droit respectivement */
arbre ab_creerNoeud (void *val, arbre filsgauche, arbre filsdroit);

/* Remplace le sous-arbre gauche de l'arbre a par filsgauche
   de façon "in-place".
   Renvoie le même arbre a */
arbre ab_setFilsGauche (arbre a, arbre filsgauche);

/* Remplace le sous-arbre droit de l'arbre a par filsdroit
   de façon "in-place".
   Renvoie le même arbre a */
arbre ab_setFilsDroit (arbre a, arbre filsdroit);

/* Renvoie la ab_getRacine de l'arbre a */
void *ab_getRacine (arbre a);

/* Renvoie le fils gauche de l'arbre a */
arbre ab_getFilsGauche (arbre a);

/* Renvoie le fils droit de l'arbre a */
arbre ab_getFilsDroit (arbre a);

/* Libère récursivement la mémoire allouée à l'arbre a
   et ses descendants */
arbre ab_detruire (arbre a);

/* Renvoie la hauteur de l'arbre a.
   La ab_getRacine compte pour 1 */
int ab_hauteur (arbre a);

/* Renvoie le nombre total de fils
   utilisé dans l'arbre a */
int ab_nombreFils (arbre a);

#endif