#include <stdlib.h>
#include <stdio.h>
#include "liste.h"

int comp_int (void *a, void *b) {
  int *ia = (int *) a;
  int *ib = (int *) b;

  return (*ia > *ib) - (*ia < *ib);
}

void afficher_liste_int (liste l) {
    liste ptr = l;

    if (est_liste_vide(ptr)) printf("[]\n");
    else {
        printf("[");
        while(!est_liste_vide(prochain_liste(ptr))) {
            printf("%d, ", renvoie_premier_liste(ptr));
            ptr = prochain_liste(ptr);
        }
        printf("%d]\n", renvoie_premier_liste(ptr));
    }
}

int main() {
    liste l = liste_vide();

    inserer_element_trie(&l, 3, comp_int);
    inserer_element_trie(&l, 2, comp_int);
    inserer_element_trie(&l, 1, comp_int);
    inserer_element_trie(&l, 4, comp_int);
    inserer_element_trie(&l, 5, comp_int);


    afficher_liste_int(l);

    exit(EXIT_SUCCESS);
}