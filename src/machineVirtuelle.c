#include "machineVirtuelle.h"

types_pile pile[TAILLEPILE];
int NIS_utilisation = 0;
int BC = 0;

/* Execute les instructions se trouvant dans l'arbre a */
void execute (arbre a) {
    int i;
    types_pile v;

    if (a == aa_vide()) return;
    
    switch (a->id) {
        case A_LISTE:
            execute(aa_fils(a));
            execute(aa_frere(aa_fils(a)));
            break;
        case A_OPAFF:
            i = get_pile(aa_fils(a));
            v = evaluer(aa_frere(aa_fils(a)));
            remplir_pile(i, v);
            break;
        case A_APPEL_FONC:
            execute(aa_fils(a)); /*pb : A_LISTEPARAMS pas dans execute*/
            execute(aa_frere(a));
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
            else execute(aa_frere(a)); /*necessaire de mettre le else ? (cause du rappel)*/
            break;
        case A_DO_WHILE: /*rajouté par PA donc pas sur*/
            execute(aa_fils(a));
            if ((evaluer(aa_frere(aa_fils(a)))).boolen == 't') {
                execute(a);
            }
            else execute(aa_frere(a)); /*necessaire de mettre le else (cause du rappel)?*/
            break;
        case A_FOR: /*rajouté par PA donc pas sur*/
            int i = (evaluer(aa_fils(a))).entier;
            int max = (evaluer(aa_frere(aa_fils(a)))).entier;
            int nb_pas = (evaluer(aa_frere(aa_frere(aa_fils(a))))).entier;

            if (i < max) {
                execute(aa_frere(aa_frere(aa_frere(aa_fils(a)))));
                evaluer(aa_fils(a)).entier += nb_pas; /*peut être que ça fonctionne (cause du rappel)*/
                execute(a);
            }

            else execute(aa_frere(a));
            break;
        case A_RETOURNER:
            return execute(aa_fils(a)); /*???*/
            break;
        case A_AFFICHER:
            aa_afficher(aa_fils(a));
            execute(aa_frere(a));
            break;
        case A_VIDE:
        default:
            break;
    }
}

/* Evalue l'expression se trouvant dans l'arbre a */
types_pile evaluer (arbre a) {
    if (a == aa_vide()) return;
    /*initialisation de la structure retournée*/
    types_pile ret;
    ret.entier = -1;
    ret.reel = -1;
    ret.booleen = -1;
    ret.caractere = -1;

    switch (a->id) {
        case A_IDF:
            break;
        case A_CSTE_ENT:
            ret.entier = aa_valeur(a);
            break;
        case A_CSTE_REELE:
            ret.reel = association_nom(tl_getLex(aa_valeur(a)));
            break;
        case A_CSTE_BOOL:
            ret.booleen = aa_valeur(a);
            break;
        case A_CSTE_CAR:
            ret.caractere = aa_valeur(a);
            break;
        case A_CSTE_CHAINE:
            break;
        case A_OP_PLUS:
            ret.entier = evaluer(aa_fils(a)).entier + evaluer(aa_frere(aa_fils(a))).entier;
            break;
        case A_OP_MOINS:
            ret.entier = evaluer(aa_fils(a)).entier - evaluer(aa_frere(aa_fils(a))).entier;
            break;
        case A_OP_MULT:
            ret.entier = evaluer(aa_fils(a)).entier * evaluer(aa_frere(aa_fils(a))).entier;
            break;
        case A_OP_DIV:
            ret.entier = evaluer(aa_fils(a)).entier / evaluer(aa_frere(aa_fils(a))).entier;
            break;
        case A_OP_EXP:
            ret.entier = pow(evaluer(aa_fils(a)).entier, evaluer(aa_frere(aa_fils(a))).entier);
            break;
        case A_OP_MODUL:
            ret.entier = evaluer(aa_fils(a)).entier % evaluer(aa_frere(aa_fils(a))).entier;
            break;
        case A_OP_INF:
            if(evaluer(aa_fils(a)) < evaluer(aa_frere(aa_fils(a)))){
                ret.booleen = 't';
            }else ret.boolee = 'f';
            break;
        case A_OP_SUP:
            if(evaluer(aa_fils(a)) > evaluer(aa_frere(aa_fils(a)))){
                ret.booleen = 't';
            }else ret.boolee = 'f';
            break;
        case A_OP_INFE:
            if(evaluer(aa_fils(a)) <= evaluer(aa_frere(aa_fils(a)))){
                ret.booleen = 't';
            }else ret.boolee = 'f';
            break;
        case A_OP_SUPE:
            if(evaluer(aa_fils(a)) >= evaluer(aa_frere(aa_fils(a)))){
                ret.booleen = 't';
            }else ret.boolee = 'f';
            break;
        case A_OP_EGAL:
            if(evaluer(aa_fils(a)) == evaluer(aa_frere(aa_fils(a)))){
                ret.booleen = 't';
            }else ret.boolee = 'f';
            break;
        case A_OP_DIFF:
            if(evaluer(aa_fils(a)) != evaluer(aa_frere(aa_fils(a)))){
                ret.booleen = 't';
            }else ret.boolee = 'f';
            break;
        case A_OP_OU:
            break;
        case A_OP_ET:
            break;
        case A_OP_NON:
            break;
        case A_VIDE:
        default:
            fprintf(stderr, "Erreur arbre invalide dans expression\n");
            exit(EXIT_FAILURE);
    }
    return ret;
}

/* Retrouve l'emplacement mémoire dans la pile correspondant 
au numéro lexicographique */
int get_pile (int numlex) {
    /*Récupérer num region avec la fonction de gustav*/
    decl champ = td_getDeclAssocNom(numlex); /*on le récup grace à la fonction de gustav*/
    int region_decl = champ.numregion;
    int NIS_decl = tr_get_reg(region_decl).niv_imbric;
    int cs = NIS_utilisation-NIS_decl;
    int diff = champ.exec;

    return pile[pile[BC+cs]+diff];
}

/* Place la valeur v dans l'emplacement mémoire i de la pile */
void remplir_pile (int i, types_pile v) {
    if (i >= 0 && i < TAILLEPILE) pile[i] = v;
    else {
        fprintf(stderr, "Tentative d'accès en dehors de la pile (%d)\n", i);
        exit(EXIT_FAILURE);
    }
}