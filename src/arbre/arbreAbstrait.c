/*
 * Auteur: Gustav Hubert
 * Desciption: - Module implémentant un arbre abstrait à l'aide 
 *            du TAD arbreBinaire. L'arbre abstrait permet la
 *            représentation d'une liste d'instructions.
 *             - Pour l'utiliser, il suffit de charger ce module
 *             puis de lancer aa_init().
 *             - Ne pas oublier de libérer la mémoire avec
 *             aa_detruire() après utilisation.
 */

#include "arbreAbstrait.h"

/* GESTION DES CELLULES DE L'ARBRE */

/* Renvoie une nouvelle cellule composée d'id et de val */
celluleAA aa_creerCellule (enum Identifiant id, void *val) {
    celluleAA cel = allocation_mem(1, sizeof(struct_celluleAA));
    cel->id = id;
    cel->donnees = val;
    return cel;
}

/* Libère la mémoire associée à la cellule cel */
void aa_detruireCellule (celluleAA cel) {
    libere_mem(cel);
}

/* GESTION DE L'ARBRE */

/* Renvoie un abrbre abstrait vide */
arbre aa_creerVide () {
    return ab_creerVide();
}

/* Vérifie si l'arbre abstrait a est vide */
int aa_estVide (arbre a) {
    return ab_estVide(a);
}

/* Renvoie un arbre abstrait identifié par id et 
   n'ayant ni fils, ni frère. val correspond à la
   donnée potentiellement associé à id */
arbre aa_creerFeuille (enum Identifiant id, void *val) {
    celluleAA cel = aa_creerCellule(id, val);

    return ab_creerFeuille(cel);
}

/* Crée et renvoie un arbre abstrait identifié par id.
   Les abres fils et frère peuvent également être indiqués. 
   val correspond à la donnée potentiellement associé à id */
arbre aa_creerNoeud (enum Identifiant id, void *val, arbre fils, arbre frere) {
    celluleAA cel = aa_creerCellule(id, val);

    /* Le fils gauche de l'arbre binaire correspond toujours au fils et
        le fils droit au frère de l'arbre en question */
    return ab_creerNoeud(cel, fils, frere);
}

/* Remplace le fils de l'arbre abstrait a par 
   l'arbre fils donné en argument (de façon "in-place").
   Renvoie le même arbre abstrait a */
arbre aa_setFils (arbre a, arbre fils) {
    return ab_setFilsGauche (a, fils);
}

/* Remplace le frère de l'arbre abstrait a par 
   l'arbre frère donné en argument (de façon "in-place").
   Renvoie le même arbre abstrait a */
arbre aa_setFrere (arbre a, arbre frere) {
    return ab_setFilsDroit (a, frere);
}

/* Renvoie la cellule de la racine de l'arbre abstrait a */
celluleAA aa_getRacine (arbre a) {
    return ab_getRacine(a);
}

/* Renvoie le fils de l'arbre abstrait a */
arbre aa_getFils (arbre a) {
    return ab_getFilsGauche(a);
}

/* Renvoie le frère de l'arbre abstrait a */
arbre aa_getFrere (arbre a) {
    return ab_getFilsDroit(a);
}

/* Libère récursivement la mémoire allouée à l'arbre 
   abstrait a et ses descendants. Si detruireValeur
   vaut 1 les cellules de l'arbre sont également détruites */
arbre aa_detruire (arbre a, int detruireValeur) {
    if (detruireValeur)
        return ab_detruire(a, aa_detruireCellule);
    else
        return ab_detruire(a, NULL);
}
