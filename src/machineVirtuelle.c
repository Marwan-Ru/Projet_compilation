#include "machineVirtuelle.h"

types_pile pile[TAILLEPILE];
int NIS_utilisation = 0;
int BC = 0;

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
        case A_IF_THEN_ELSE: /*rajouté par PA donc pas sur*/
            if ((evaluer(aa_fils(a))).booleen == 't') execute(aa_frere(aa_fils(a)));
            else execute(aa_frere(aa_frere(aa_fils(a))));
            execute(aa_frere(a));
            break;
        case A_WHILE: /*rajouté par PA donc pas sur*/
            if ((evaluer(aa_fils(a))).booleen == 't') {
                execute(aa_frere(aa_fils(a)));
                execute(a);
            }
            execute(aa_frere(a));
            break;
        case A_DO_WHILE: /*rajouté par PA donc pas sur*/
            execute(aa_fils(a));
            if ((evaluer(aa_frere(aa_fils(a)))).boolen == 't') {
                execute(a);
            }
            execute(aa_frere(a));
            break;
        case A_FOR: /*rajouté par PA donc pas sur*/
            int i = (evaluer(aa_fils(a))).entier;
            int max = (evaluer(aa_frere(aa_fils(a)))).entier;
            int nb_pas = (evaluer(aa_frere(aa_frere(aa_fils(a))))).entier;

            if (i < max) {
                execute(aa_frere(aa_frere(aa_frere(aa_fils(a)))));
                i += nb_pas;
            }
            execute(aa_frere(a));
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
    /*Récupérer num region avec la fonction de gustav*/
    decl champ = tdgetDeclAssocNom(numlex); /*on le récup grace à la fonction de gustav*/
    int region_decl = champ.numregion;
    int NIS_decl = tr_get_reg(region_decl).niv_imbric;
    int cs = NIS_utilisation-NIS_decl;
    int diff = champ.exec;

    return pile[pile[BC+cs]+diff];
}

/* Place la valeur v dans l'emplacement mémoire i de la pile */
void remplir_pile (int i, union types_pile v) {
    if (i >= 0 && i < TAILLEPILE) pile[i] = v;
    else {
        fprintf(stderr, "Tentative d'accès en dehors de la pile (%d)\n", i);
        exit(EXIT_FAILURE);
    }
}