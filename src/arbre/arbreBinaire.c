/*
 *      Auteur: Gustav HUBERT
 *        Date: 2020/04/04
 * Modifié le: 2020/11/31
 * Description: Module implémentant les arbres binaire
 */ 

#include "arbreBinaire.h"

/* Renvoie un arbre nulle */
arbre ab_creerVide () {
    return NULL;
}

/* Vérifie si l'arbre est vide */
int ab_estVide (arbre a) {
    return a == ab_creerVide();
}

/* Renvoie un arbre sans fils et ayant comme racine val */
arbre ab_creerFeuille (void *val) {
    arbre a = allocation_mem(1, sizeof(struct struct_arbre));
    a->fDroit = ab_creerVide();
    a->fGauche = ab_creerVide();
    a->val = val;
    return a;
}

/* Renvoie un arbre ayant val pour racine ainsi que
   filsgauche et filsdroit comme sous-arbre gauche 
   et sous-arbre droit respectivement */
arbre ab_creerNoeud (void *val, arbre filsgauche, arbre filsdroit) {
    arbre a = ab_creerFeuille(val);
    ab_setFilsGauche(a, filsgauche);
    ab_setFilsDroit(a, filsdroit);
    return a;
}

/* Remplace le sous-arbre gauche de l'arbre a par filsgauche
   de façon "in-place".
   Renvoie le même arbre a */
arbre ab_setFilsGauche (arbre a, arbre filsgauche) {
    if (ab_estVide(a)) a = ab_creerFeuille(NULL);
    a->fGauche = filsgauche;
    return a;
}

/* Remplace le sous-arbre droit de l'arbre a par filsdroit
   de façon "in-place".
   Renvoie le même arbre a */
arbre ab_setFilsDroit (arbre a, arbre filsdroit) {
    if (ab_estVide(a)) a = ab_creerFeuille(NULL);
    a->fDroit = filsdroit;
    return a;    
}

/* Renvoie la racine de l'arbre a */
void *ab_getRacine (arbre a) {
    if (!ab_estVide(a)) return a->val;
    else return NULL;
}

/* Renvoie le fils gauche de l'arbre a */
arbre ab_getFilsGauche (arbre a) {
    if (!ab_estVide(a)) return a->fGauche;
    else return NULL;
}

/* Renvoie le fils droit de l'arbre a */
arbre ab_getFilsDroit (arbre a) {
    if (!ab_estVide(a)) return a->fDroit;
    else return NULL;
}

/* Libère récursivement la mémoire allouée à l'arbre a
   et ses descendants. Utilise la fonction de destruction 
   dstr sur les valeurs s'il ne s'agit pas de NULL */
arbre ab_detruire (arbre a, void (*dstr)(void *)) {
    if (!ab_estVide (a)) {
        /* Fils */
        a->fGauche = ab_detruire (a->fGauche, dstr);
        a->fDroit = ab_detruire (a->fDroit, dstr);
        /* Valeur */
        if (dstr != NULL) (*dstr)(&(a->val));
        /* Self */
        libere_mem (&a);
    }
    return ab_creerVide();
}

/* Renvoie la hauteur de l'arbre a.
   La racine compte pour 1 */
int ab_hauteur (arbre a) {
    int gMax, dMax;

    if (ab_estVide(a)) return 0;
    else {
        gMax = ab_hauteur (a->fGauche) + 1;
        dMax = ab_hauteur (a->fDroit) + 1;
        return gMax > dMax ? gMax : dMax;
    }   
}

/* Renvoie le nombre total de fils
   utilisé dans l'arbre a */
int ab_nombreFils (arbre a) {
    if (ab_estVide(a)) return 0;
    return 1 + ab_nombreFils(a->fGauche) + ab_nombreFils(a->fDroit);
}