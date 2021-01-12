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
            if ((evaluer(aa_frere(aa_fils(a)))).booleen == 't') {
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
    
    types_pile ret, tpa, tpb; /*tpa et tpb pour les opérations booléenes*/
    /*initialisation de la structure retournée*/
    ret.type = 'x'; erreur;

    switch (a->id) {
        case A_IDF:
            break;
        case A_CSTE_ENT:
            ret.entier = aa_valeur(a);
            ret.type = 'e'; /*Permet de savoir qu'on a initialisée un entier et pas une autre variable*/
            break;
        case A_CSTE_REELE:
            ret = pile[getpile(aa_valeur(a))];
            ret.type = 'r'; /*idem*/
            break;
        case A_CSTE_BOOL:
            ret.booleen = aa_valeur(a);
            ret.type = 'b';
            break;
        case A_CSTE_CAR:
            ret.caractere = aa_valeur(a);
            ret.type = 'c';
            break;
        case A_CSTE_CHAINE:
            break;
        case A_OP_PLUS:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == 'e' && tpb.type == 'e'){
                ret.entier = tpa.entier + tpb.entier;
                ret.type = 'e';
            }else if(tpa.type == 'r' && tpb.type == 'r'){
                ret.reel = tpa.reel + tpb.reel;
                ret.type = 'r';
            }else if(tpa.type == 'c' && tpb.type == 'c'){
                ret.caractere = tpa.caractere + tpb.caractere;
                ret.type = 'c';
            }else if(tpa.type == 'c' && tpb.type == 'e'){
                ret.entier = tpa.caractere + tpb.entier;
                ret.type = 'e';
            }else if(tpa.type == 'e' && tpb.type == 'c'){
                ret.entier = tpa.entier + tpb.caractere;
                ret.type = 'e';
            }else{/*On a fait une addition entre deux types incompatibles*/
                fprintf(stderr, "Erreur addition entre deux types incompatibles\n");
                exit(EXIT_FAILURE);
            }
            break;
        case A_OP_MOINS:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == 'e' && tpb.type == 'e'){
                ret.entier = tpa.entier - tpb.entier;
                ret.type = 'e';
            }else if(tpa.type == 'r' && tpb.type == 'r'){
                ret.reel = tpa.reel - tpb.reel;
                ret.type = 'r';
            }else if(tpa.type == 'c' && tpb.type == 'c'){
                ret.caractere = tpa.caractere - tpb.caractere;
                ret.type = 'c';
            }else if(tpa.type == 'c' && tpb.type == 'e'){
                ret.entier = tpa.caractere - tpb.entier;
                ret.type = 'e';
            }else if(tpa.type == 'e' && tpb.type == 'c'){
                ret.entier = tpa.entier - tpb.caractere;
                ret.type = 'e';
            }else{/*On a fait une soustraction entre deux types incompatibles*/
                fprintf(stderr, "Erreur soustraction entre deux types incompatibles\n");
                exit(EXIT_FAILURE);
            }
            break;
        case A_OP_MULT:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == 'e' && tpb.type == 'e'){
                ret.entier = tpa.entier * tpb.entier;
                ret.type = 'e';
            }else if(tpa.type == 'r' && tpb.type == 'r'){
                ret.reel = tpa.reel * tpb.reel;
                ret.type = 'r';
            }else if(tpa.type == 'c' && tpb.type == 'c'){
                ret.caractere = tpa.caractere * tpb.caractere;
                ret.type = 'c';
            }else if(tpa.type == 'c' && tpb.type == 'e'){
                ret.entier = tpa.caractere * tpb.entier;
                ret.type = 'e';
            }else if(tpa.type == 'e' && tpb.type == 'c'){
                ret.entier = tpa.entier * tpb.caractere;
                ret.type = 'e';
            }else{/*On a fait une multiplication entre deux types incompatibles*/
                fprintf(stderr, "Erreur multiplication entre deux types incompatibles\n");
                exit(EXIT_FAILURE);
            }
            break;
        case A_OP_DIV:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == 'e' && tpb.type == 'e'){
                ret.entier = tpa.entier / tpb.entier;
                ret.type = 'e';
            }else if(tpa.type == 'r' && tpb.type == 'r'){
                ret.reel = tpa.reel / tpb.reel;
                ret.type = 'r';
            }else if(tpa.type == 'c' && tpb.type == 'c'){
                ret.caractere = tpa.caractere / tpb.caractere;
                ret.type = 'c';
            }else if(tpa.type == 'c' && tpb.type == 'e'){
                ret.entier = tpa.caractere / tpb.entier;
                ret.type = 'e';
            }else if(tpa.type == 'e' && tpb.type == 'c'){
                ret.entier = tpa.entier / tpb.caractere;
                ret.type = 'e';
            }else{/*On a fait une division entre deux types incompatibles*/
                fprintf(stderr, "Erreur division entre deux types incompatibles\n");
                exit(EXIT_FAILURE);
            }
            break;
        case A_OP_EXP:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == 'r' && tpb.type == 'r'){
                ret.reel = pow(tpa.reel, tpb.reel);
                ret.type = 'r';
            }else{/*On a fait une division entre deux types incompatibles*/
                fprintf(stderr, "Erreur tentative d'exponentielle avec un autre type que reel\n");
                exit(EXIT_FAILURE);
            }
            break;
        case A_OP_MODUL:
            if(tpa.type == 'e' && tpb.type == 'e'){
                ret.entier = tpa.entier % tpb.entier;
                ret.type = 'e';
            }else if(tpa.type == 'c' && tpb.type == 'c'){
                ret.caractere = tpa.caractere % tpb.caractere;
                ret.type = 'c';
            }else if(tpa.type == 'c' && tpb.type == 'e'){
                ret.entier = tpa.caractere % tpb.entier;
                ret.type = 'e';
            }else if(tpa.type == 'e' && tpb.type == 'c'){
                ret.entier = tpa.entier % tpb.caractere;
                ret.type = 'e';
            }else{/*On a fait une modulo entre deux types incompatibles*/
                fprintf(stderr, "Erreur modulo entre deux types incompatibles\n");
                exit(EXIT_FAILURE);
            }
        case A_OP_INF: 
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == 'e' && tpb.type == 'e'){
                if(tpa.entier < tpb.entier){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'r' && tpb.type == 'r'){
                if(tpa.reel < tpb.reel){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'c' && tpb.type == 'c'){
                if(tpa.caractere < tpb.caractere){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'c' && tpb.type == 'e'){
                if(tpa.caractere < tpb.entier){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'e' && tpb.type == 'c'){
                if(tpa.entier < tpb.entier){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else{/*On a fait une comparaison entre deux types incomparables*/
                fprintf(stderr, "Erreur comparaison entre deux types incompatibles\n");
                exit(EXIT_FAILURE);
            }
            ret.type = 'b';
            break;
        case A_OP_SUP:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == 'e' && tpb.type == 'e'){
                if(tpa.entier > tpb.entier){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'r' && tpb.type == 'r'){
                if(tpa.reel > tpb.reel){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'c' && tpb.type == 'c'){
                if(tpa.caractere > tpb.caractere){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'c' && tpb.type == 'e'){
                if(tpa.caractere > tpb.entier){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'e' && tpb.type == 'c'){
                if(tpa.entier > tpb.entier){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else{/*On a fait une comparaison entre deux types incomparables*/
                fprintf(stderr, "Erreur comparaison entre deux types incompatibles\n");
                exit(EXIT_FAILURE);
            }
            ret.type = 'b';
            break;
        case A_OP_INFE:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == 'e' && tpb.type == 'e'){
                if(tpa.entier <= tpb.entier){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'r' && tpb.type == 'r'){
                if(tpa.reel <= tpb.reel){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'c' && tpb.type == 'c'){
                if(tpa.caractere <= tpb.caractere){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'c' && tpb.type == 'e'){
                if(tpa.caractere <= tpb.entier){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'e' && tpb.type == 'c'){
                if(tpa.entier <= tpb.caractere){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else{/*On a fait une comparaison entre deux types incomparables*/
                fprintf(stderr, "Erreur comparaison entre deux types incompatibles\n");
                exit(EXIT_FAILURE);
            }
            ret.type = 'b';
            break;
        case A_OP_SUPE:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == 'e' && tpb.type == 'e'){
                if(tpa.entier >= tpb.entier){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'r' && tpb.type == 'r'){
                if(tpa.reel >= tpb.reel){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'c' && tpb.type == 'c'){
                if(tpa.caractere >= tpb.caractere){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'c' && tpb.type == 'e'){
                if(tpa.caractere >= tpb.entier){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'e' && tpb.type == 'c'){
                if(tpa.entier >= tpb.caractere){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else{/*On a fait une comparaison entre deux types incomparables*/
                fprintf(stderr, "Erreur comparaison entre deux types incompatibles\n");
                exit(EXIT_FAILURE);
            }
            ret.type = 'b';
            break;
        case A_OP_EGAL:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == 'e' && tpb.type == 'e'){
                if(tpa.entier == tpb.entier){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'r' && tpb.type == 'r'){
                if(tpa.reel == tpb.reel){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'c' && tpb.type == 'c'){
                if(tpa.caractere == tpb.caractere){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'c' && tpb.type == 'e'){
                if(tpa.caractere == tpb.entier){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'e' && tpb.type == 'c'){
                if(tpa.entier == tpb.caractere){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else{/*On a fait une comparaison entre deux types incomparables*/
                fprintf(stderr, "Erreur comparaison entre deux types incompatibles\n");
                exit(EXIT_FAILURE);
            }
            ret.type = 'b';
            break;
        case A_OP_DIFF:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == 'e' && tpb.type == 'e'){
                if(tpa.entier != tpb.entier){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'r' && tpb.type == 'r'){
                if(tpa.reel != tpb.reel){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'c' && tpb.type == 'c'){
                if(tpa.caractere != tpb.caractere){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'c' && tpb.type == 'e'){
                if(tpa.caractere != tpb.entier){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else if(tpa.type == 'e' && tpb.type == 'c'){
                if(tpa.entier != tpb.caractere){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
            }else{/*On a fait une comparaison entre deux types incomparables*/
                fprintf(stderr, "Erreur comparaison entre deux types incompatibles\n");
                exit(EXIT_FAILURE);
            }
            ret.type = 'b';
            break;
        case A_OP_OU:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == 'b' && tpb.type == 'b'){
                if(tpa.booleen == 't' || tpa.booleen == 't'){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
                
            }else{/*On a fait une division entre deux types incompatibles*/
                fprintf(stderr, "Erreur tentative d'operation booleene avec un autre type que booleen\n");
                exit(EXIT_FAILURE);
            }
            ret.type = 'b';
            break;
        case A_OP_ET:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == 'b' && tpb.type == 'b'){
                if(tpa.booleen == 't' && tpa.booleen == 't'){
                    ret.booleen = 't';
                }else ret.booleen = 'f';
                
            }else{/*On a fait une division entre deux types incompatibles*/
                fprintf(stderr, "Erreur tentative d'operation booleene avec un autre type que booleen\n");
                exit(EXIT_FAILURE);
            }
            ret.type = 'b';
            break;
        case A_OP_NON:
            tpa = evaluer(aa_fils(a));
            if(tpa.type == 'b'){
                if(tpa.booleen == 't'){
                    ret.booleen = 'f';
                }else ret.booleen = 't';
            }else{/*On a fait une division entre deux types incompatibles*/
                fprintf(stderr, "Erreur tentative d'operation booleene avec un autre type que booleen\n");
                exit(EXIT_FAILURE);
            }
            ret.type = 'b';
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