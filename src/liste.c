/* Date : 2020/02/25
 * Description : Copie des fonctions
 * du cours implémentant les listes
 * + quelques additions par Gustav Hubert
 */

#include "liste.h"

/* Renvoie une liste vide */
liste liste_vide()
{
  return NULL;
}

/* Savoir si une liste est vide */
int est_liste_vide(liste l)
{
  return l==liste_vide();
}

/* inserer un element (au début de la liste) */
void inserer_element_liste(liste *l, element elem)
{
  liste lnew=(liste)allocation_mem(1,sizeof(struct_cellule));
  lnew->objet=elem;
  lnew->suivant=*l;
  *l = lnew;
}

/* extraire le premier élément de la liste */
element renvoie_premier_liste(liste l)
{
  if(est_liste_vide(l))
    printf("Erreur la liste est vide dans la fonction renvoie_premier\n");
  return l->objet;
}

/* supprimer une cellule (au début de la liste).
   Ne libère pas la mémoire potentiellement allouée
   à la valeur stockée */
void supprimer_premier_liste(liste *l)
{
  if (!est_liste_vide(*l)) {
    liste tmp = (**l).suivant;
    libere_mem(l);
    *l = tmp;
  }
}

/* Renvoie un pointeur vers la prochaine cellule */
liste prochain_liste (liste l) 
{
  if (!est_liste_vide(l)) return l->suivant;
  else return liste_vide();
}

/* Renvoie la taille de la liste */
int taille_liste (liste l) 
{
  liste ptr = l;
  int n = 0;

  while (!est_liste_vide(ptr)) {
    n++;
    ptr = prochain_liste(ptr);
  }

  return n;
}

/* Renvoie l'élément à l'indice i */
element elem_i_liste (liste l, int i) 
{
  liste ptr = l;

  while (i > 0 && !est_liste_vide(ptr)) {
    ptr = prochain_liste(ptr);
    i--;
  }
  return renvoie_premier_liste(ptr);
}

/* Supprime le restant des éléments de l.
   Utilise la fonction de destruction dstr sur les valeurs
   s'il ne s'agit pas de NULL */
void detruire_liste (liste l, void (*dstr)(void *)) {
  element val;
  while (!est_liste_vide(l)) {
    if (dstr != NULL) {
      val = renvoie_premier_liste(l);
      (*dstr)(&val);
    }
    supprimer_premier_liste(&l);
  }
}

/* Renvoie l'indice de l'élément s'il existe déjà, sinon -1.
   foncComp est necessaire pour comparer deux éléments et doit 
   renvoyer 1 si les deux éléments sont égaux ! */
int indice_elem (liste l, element x, int (*foncComp)(void *, void *)) {
  int i = 0;

  while (!est_liste_vide (l)) {
    if ((*foncComp) (x, renvoie_premier_liste(l))) return i;
    l = prochain_liste(l);
    i++;
  }

  return -1;
}

/* Renvoie 1 si x existe dans l, 0 sinon */
int existe_elem (liste l, element x, int (*foncComp)(void *, void *)) {
  return indice_elem (l, x, foncComp) != -1;
}

/* Renvoi un tableau contenant les éléments de l dans le même ordre */
element *liste_vers_tableau (liste l) {
  int t = taille_liste(l), i;
  element *tab = allocation_mem (t, sizeof (element));

  for (i = 0; i < t; i++) {
    tab[i] = renvoie_premier_liste (l);
    l = prochain_liste(l);
  }

  return tab;
}

/* Renvoie une liste contenant les n premiers éléments de t dans le 
   même ordre */
liste tableau_vers_liste (element *t, int n) {
  int i;
  liste l = liste_vide();

  for (i = n-1; i >= 0; i--) {
    inserer_element_liste (&l, t[i]);
  }

  return l;
}

/* Trie l à l'aide de l'algorithme quick sort et de la fonction de 
   comparaison foncComp */
void trier_liste (liste *l, int (*foncComp) (const void *, const void *)) {
  liste l2 = liste_vide();
  int n = taille_liste(*l);
  element *t = liste_vers_tableau (*l);

  qsort(t, n, sizeof(element), foncComp);
  l2 = tableau_vers_liste(t, n);
  libere_mem (&t);
  detruire_liste (*l, NULL);
  *l = l2;
} 

/* Insère correctement l'élément elem dans une liste triée l dans l'ordre croissant */
void inserer_element_trie (liste *l, element elem, int (*foncComp) (const void *, const void *)) {
  liste ptr = *l,
        last = NULL;

  while (!est_liste_vide(ptr) && foncComp(elem, renvoie_premier_liste(ptr)) > 0) {
    last = ptr;
    ptr = prochain_liste(ptr);
  }

  inserer_element_liste(&ptr, elem);
  last->suivant = ptr;
}