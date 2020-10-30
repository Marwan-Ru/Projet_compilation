#include <stdlib.h>
#include <stdio.h>
#include "liste.h"

void afficher_liste_int (liste l) {
    liste ptr = l;

    if (est_liste_vide(ptr)) printf("[]\n");
    else {
        printf("[");
        while(!est_liste_vide(prochain_liste(ptr))) {
            printf("%d, ", *(int *) renvoie_premier_liste(ptr));
            ptr = prochain_liste(ptr);
        }
        printf("%d]\n", *(int *) renvoie_premier_liste(ptr));
    }
}

int comp_int (const void *a, const void *b) {
  int *ia = (int *) a;
  int *ib = (int *) b;

  return (*ia > *ib) - (*ia < *ib);
}

int main() {
    liste l = liste_vide();
    int *elem = allocation_mem(1, sizeof(int));

    *elem = 3;
    inserer_element_trie(&l, elem, comp_int);
    elem = allocation_mem(1, sizeof(int));
    *elem = 6;
    inserer_element_trie(&l, elem, comp_int);
    elem = allocation_mem(1, sizeof(int));
    *elem = 2;
    inserer_element_trie(&l, elem, comp_int);
    elem = allocation_mem(1, sizeof(int));
    *elem = 9;
    inserer_element_trie(&l, elem, comp_int);
    elem = allocation_mem(1, sizeof(int));
    *elem = 7;
    inserer_element_trie(&l, elem, comp_int);
    elem = allocation_mem(1, sizeof(int));


    afficher_liste_int(l);
    detruire_liste(l, libere_mem);

    exit(EXIT_SUCCESS);
} 