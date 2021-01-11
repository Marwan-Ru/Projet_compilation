#include "machineVirtuelle.h"

types_pile pile[TAILLEPILE];

/* Execute les instructions se trouvant dans l'arbre a */
void execute (arbre a) {
    int i, types_pile v;

    if (a == aa_vide()) return;
    
    switch (a->id) {
        case A_LISTE:
            execute(aa_fils(a));
            execute(aa_frere(aa_fils(a)));
            break;
        case A_OPAFF:
            i = association_nom(aa_fils(a));
            v = evaluer(aa_frere(aa_fils(a)));
            remplir_pile(i, v);
            break;
        case A_APPEL_FONC:
            break;
        case A_IF_THEN_ELSE:
            break;
        case A_WHILE:
            break;
        case A_DO_WHILE:
            break;
        case FOR:
            break;
        case A_RETOURNER:
            break;
        case A_AFFICHER:
            break;
        case A_VIDE:
        default:
            break;
    }
}

/* Evalue l'expression se trouvant dans l'arbre a */
union types_pile evaluer (arbre a) {
    if (a == aa_vide()) return;
    
    switch (a->id) {
        case A_IDF:
            return;
        case A_CSTE_ENT:
            return;
        case A_CSTE_REELE:
            return;
        case A_CSTE_BOOL:
            return;
        case A_CSTE_CAR:
            return;
        case A_CSTE_CHAINE:
            return;
        case A_OP_PLUS:
            return;
        case A_OP_MOINS:
            return;
        case A_OP_MULT:
            return;
        case A_OP_DIV:
            return;
        case A_OP_EXP:
            return;
        case A_OP_MODUL:
            return;
        case A_OP_INF:
            return;
        case A_OP_SUP:
            return;
        case A_OP_INFE:
            return;
        case A_OP_SUPE:
            return;
        case A_OP_EGAL:
            return;
        case A_OP_DIFF:
            return;
        case A_OP_OU:
            return;
        case A_OP_ET:
            return;
        case A_OP_NON:
            return;
        case A_VIDE:
        default:
            fprintf(stderr, "Erreur arbre invalide dans expression\n");
            exit(EXIT_FAILURE);
    }
}

/* Retrouve l'emplacement mémoire dans la pile correspondant 
au numéro lexicographique */
int association_nom (int numlex) {

}

/* Place la valeur v dans l'emplacement mémoire i de la pile */
void remplir_pile (int i, union types_pile v) {
    if (i >= 0 && i < TAILLEPILE) pile[i] = v;
    else {
        fprintf(stderr, "Tentative d'accès en dehors de la pile (%d)\n", i);
        exit(EXIT_FAILURE);
    }
}