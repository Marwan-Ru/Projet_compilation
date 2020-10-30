/* Date : 2020/02/25
 * Auteur : Gustav HUBERT
 * Description : Copie des fonctions
 * du cours implémentant les listes
 * + quelques additions
 */

#ifndef LISTE
#define LISTE

#include <stdio.h>
#include <stdlib.h>
#include "allocation.h"

typedef void * element;

typedef struct cellule{
  element objet;
  struct cellule * suivant;
} struct_cellule;

typedef struct_cellule * liste;

/* renvoie la liste vide */
liste liste_vide();

/* teste si une liste est vide */
int est_liste_vide(liste l);

/* inserer un element (au début de la liste) */
void inserer_element_liste(liste *l, element elem);

/* renvoie le premier element de la liste l */
element renvoie_premier_liste(liste l);

/* supprimer une cellule (au début de la liste).
   Ne libère pas la mémoire potentiellement allouée
   à la valeur stockée */
void supprimer_premier_liste(liste *l);

/* Renvoie un pointeur vers la prochaine cellule */
liste prochain_liste (liste l);

/* Renvoie la taille de la liste */
int taille_liste (liste l);

/* Renvoie l'élément à l'indice i */
element elem_i_liste (liste l, int i);

/* Supprime le restant des éléments de l.
   Utilise la fonction de destruction dstr sur les valeurs
   s'il ne s'agit pas de NULL */
void detruire_liste (liste l, void (*dstr)(void *));

/* Renvoie l'indice de l'élément s'il existe déjà, sinon -1.
   foncComp est necessaire pour comparer deux éléments et doit 
   renvoyer 1 si les deux éléments sont égaux ! */
int indice_elem (liste l, element x, int (*foncComp)(void *, void *));

/* Renvoie 1 si x existe dans l, 0 sinon */
int existe_elem (liste l, element x, int (*foncComp)(void *, void *));

/* Renvoi un tableau contenant les éléments de l dans le même ordre */
element *liste_vers_tableau (liste l);

/* Renvoie une liste contenant les n premiers éléments de t dans le 
   même ordre */
liste tableau_vers_liste (element *t, int n);

/* Trie l à l'aide de l'algorithme quick sort et de la fonction de 
   comparaison foncComp */
void trier_liste (liste *l, int (*foncComp) (const void *, const void *));

/* Insère correctement l'élément elem dans une liste triée l dans l'ordre croissant */
void inserer_element_trie (liste *l, element elem, int (*foncComp) (const void *, const void *));

#endif
