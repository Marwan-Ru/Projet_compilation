#include "machineVirtuelle.h"

types_pile pile[TAILLEPILE];
int NIS = 0, BC = 0;
region reg;

/* Execute les instructions se trouvant dans l'arbre a */
void execute (arbre a) {
    int i, newBC, newNIS;
    types_pile v;
    region newReg;
    types_pile tmp;
    decl declaration;

    if (a == aa_vide()) return;
    
    switch (a->id) {
        case A_LISTE:
            execute(aa_fils(a));
            execute(aa_frere(aa_fils(a)));
            break;
        case A_OPAFF:
            i = get_pile(aa_fils(a));
            v = evaluer(aa_frere(aa_fils(a)));
            set_pile(i, v);
            break;
        case A_APPEL_FONC:
            declaration = td_getdecl(aa_valeur(a));
            newReg = tr_get_reg(declaration.exec);
            newBC = BC + reg.taille_zone;
            newNIS = newReg.niv_imbric;

            /* Vérification */
            if (newNIS < 0 || newNIS > NIS+1) {
                printf("La région '%s' est innacessible\n", td_getNumLex(aa_valeur(a)));
                System.exit(EXIT_FAILURE);
            }

            /* Chaînage dynamique */
            set_pile(newBC, BC);

            /* Chaînage statique */
            if (newNIS == NIS+1) {
                /* On ajoute la BC puis on copie le chainage statique de la région d'avant */
                set_pile(newBC+1, BC);
                for (i = 0; i < NIS; i++) {
                    tmp.entier = BC+1+i;
                    tmp.type = ''
                    set_pile(newBC+2+i, tmp);
                }
            } else {
                /* On copie le chainage statique de la dernière région ayant le même NIS */
                for (i = NIS - newNIS; i < NIS; i++){
                    tmp.entier = BC+1+i;
                    set_pile(newBC+1+i-(NIS-newNIS), tmp);
                } 
            }

            /* Arguments */


            break;
        case A_IF_THEN_ELSE: /*rajouté par PA donc pas sur*/
            if ((evaluer(aa_fils(a))).booleen == TRUE) execute(aa_frere(aa_fils(a)));
            else execute(aa_frere(aa_frere(aa_fils(a))));
            execute(aa_frere(a));
            break;
        case A_WHILE: /*rajouté par PA donc pas sur*/
            if ((evaluer(aa_fils(a))).booleen == TRUE) {
                execute(aa_frere(aa_fils(a)));
                execute(a);
            } else execute(aa_frere(a));
            break;
        case A_DO_WHILE: /*rajouté par PA donc pas sur*/
            execute(aa_fils(a));
            if ((evaluer(aa_frere(aa_fils(a)))).booleen == TRUE) {
                execute(a);
            }
            else execute(aa_frere(a)); /*necessaire de mettre le else (cause du rappel)?*/
            break;
        case A_FOR: /*rajouté par PA donc pas sur*/
            int i = (evaluer(aa_fils(a))).entier;
            //int max = (evaluer(aa_frere(aa_fils(a)))).entier;
            int indice = 0;
            int nb_pas = (evaluer(aa_frere(aa_frere(aa_fils(a))))).entier;

            if ((evaluer(aa_frere(aa_fils(a)))).booleen == TRUE) {
                execute(aa_frere(aa_frere(aa_frere(aa_fils(a)))));
                indice = get_pile (evaluer(aa_fils(a)).entier); /*dans l'idée : il faudrait recupérer le numlex*/
                pile[indice] += nb_pas;
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
        case A_LIRE:
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
    ret.type = T_ERR; erreur;

    switch (a->id) {
        case A_IDF:
            break;
        case A_CSTE_ENT:
            ret.entier = aa_valeur(a);
            ret.type = T_INT; /*Permet de savoir qu'on a initialisée un entier et pas une autre variable*/
            break;
        case A_CSTE_REELE:
            ret = pile[getpile(aa_valeur(a))];
            ret.type = T_FLOAT; /*idem*/
            break;
        case A_CSTE_BOOL:
            ret.booleen = aa_valeur(a);
            ret.type = T_BOOL;
            break;
        case A_CSTE_CAR:
            ret.caractere = aa_valeur(a);
            ret.type = T_CHAR;
            break;
        case A_CSTE_CHAINE:
            break;
        case A_OP_PLUS:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == T_INT && tpb.type == T_INT){
                ret.entier = tpa.entier + tpb.entier;
                ret.type = T_INT;
            }else if(tpa.type == T_FLOAT && tpb.type == T_FLOAT){
                ret.reel = tpa.reel + tpb.reel;
                ret.type = T_FLOAT;
            }else if(tpa.type == T_CHAR && tpb.type == T_CHAR){
                ret.caractere = tpa.caractere + tpb.caractere;
                ret.type = T_CHAR;
            }else if(tpa.type == T_CHAR && tpb.type == T_INT){
                ret.entier = tpa.caractere + tpb.entier;
                ret.type = T_INT;
            }else if(tpa.type == T_INT && tpb.type == T_CHAR){
                ret.entier = tpa.entier + tpb.caractere;
                ret.type = T_INT;
            }else{/*On a fait une addition entre deux types incompatibles*/
                fprintf(stderr, "Erreur addition entre deux types incompatibles\n");
                exit(EXIT_FAILURE);
            }
            break;
        case A_OP_MOINS:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == T_INT && tpb.type == T_INT){
                ret.entier = tpa.entier - tpb.entier;
                ret.type = T_INT;
            }else if(tpa.type == T_FLOAT && tpb.type == T_FLOAT){
                ret.reel = tpa.reel - tpb.reel;
                ret.type = T_FLOAT;
            }else if(tpa.type == T_CHAR && tpb.type == T_CHAR){
                ret.caractere = tpa.caractere - tpb.caractere;
                ret.type = T_CHAR;
            }else if(tpa.type == T_CHAR && tpb.type == T_INT){
                ret.entier = tpa.caractere - tpb.entier;
                ret.type = T_INT;
            }else if(tpa.type == T_INT && tpb.type == T_CHAR){
                ret.entier = tpa.entier - tpb.caractere;
                ret.type = T_INT;
            }else{/*On a fait une soustraction entre deux types incompatibles*/
                fprintf(stderr, "Erreur soustraction entre deux types incompatibles\n");
                exit(EXIT_FAILURE);
            }
            break;
        case A_OP_MULT:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == T_INT && tpb.type == T_INT){
                ret.entier = tpa.entier * tpb.entier;
                ret.type = T_INT;
            }else if(tpa.type == T_FLOAT && tpb.type == T_FLOAT){
                ret.reel = tpa.reel * tpb.reel;
                ret.type = T_FLOAT;
            }else if(tpa.type == T_CHAR && tpb.type == T_CHAR){
                ret.caractere = tpa.caractere * tpb.caractere;
                ret.type = T_CHAR;
            }else if(tpa.type == T_CHAR && tpb.type == T_INT){
                ret.entier = tpa.caractere * tpb.entier;
                ret.type = T_INT;
            }else if(tpa.type == T_INT && tpb.type == T_CHAR){
                ret.entier = tpa.entier * tpb.caractere;
                ret.type = T_INT;
            }else{/*On a fait une multiplication entre deux types incompatibles*/
                fprintf(stderr, "Erreur multiplication entre deux types incompatibles\n");
                exit(EXIT_FAILURE);
            }
            break;
        case A_OP_DIV:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == T_INT && tpb.type == T_INT){
                ret.entier = tpa.entier / tpb.entier;
                ret.type = T_INT;
            }else if(tpa.type == T_FLOAT && tpb.type == T_FLOAT){
                ret.reel = tpa.reel / tpb.reel;
                ret.type = T_FLOAT;
            }else if(tpa.type == T_CHAR && tpb.type == T_CHAR){
                ret.caractere = tpa.caractere / tpb.caractere;
                ret.type = T_CHAR;
            }else if(tpa.type == T_CHAR && tpb.type == T_INT){
                ret.entier = tpa.caractere / tpb.entier;
                ret.type = T_INT;
            }else if(tpa.type == T_INT && tpb.type == T_CHAR){
                ret.entier = tpa.entier / tpb.caractere;
                ret.type = T_INT;
            }else{/*On a fait une division entre deux types incompatibles*/
                fprintf(stderr, "Erreur division entre deux types incompatibles\n");
                exit(EXIT_FAILURE);
            }
            break;
        case A_OP_EXP:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == T_FLOAT && tpb.type == T_FLOAT){
                ret.reel = pow(tpa.reel, tpb.reel);
                ret.type = T_FLOAT;
            }else{/*On a fait une division entre deux types incompatibles*/
                fprintf(stderr, "Erreur tentative d'exponentielle avec un autre type que reel\n");
                exit(EXIT_FAILURE);
            }
            break;
        case A_OP_MODUL:
            if(tpa.type == T_INT && tpb.type == T_INT){
                ret.entier = tpa.entier % tpb.entier;
                ret.type = T_INT;
            }else if(tpa.type == T_CHAR && tpb.type == T_CHAR){
                ret.caractere = tpa.caractere % tpb.caractere;
                ret.type = T_CHAR;
            }else if(tpa.type == T_CHAR && tpb.type == T_INT){
                ret.entier = tpa.caractere % tpb.entier;
                ret.type = T_INT;
            }else if(tpa.type == T_INT && tpb.type == T_CHAR){
                ret.entier = tpa.entier % tpb.caractere;
                ret.type = T_INT;
            }else{/*On a fait une modulo entre deux types incompatibles*/
                fprintf(stderr, "Erreur modulo entre deux types incompatibles\n");
                exit(EXIT_FAILURE);
            }
        case A_OP_INF: 
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == T_INT && tpb.type == T_INT){
                if(tpa.entier < tpb.entier){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_FLOAT && tpb.type == T_FLOAT){
                if(tpa.reel < tpb.reel){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_CHAR && tpb.type == T_CHAR){
                if(tpa.caractere < tpb.caractere){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_CHAR && tpb.type == T_INT){
                if(tpa.caractere < tpb.entier){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_INT && tpb.type == T_CHAR){
                if(tpa.entier < tpb.entier){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else{/*On a fait une comparaison entre deux types incomparables*/
                fprintf(stderr, "Erreur comparaison entre deux types incompatibles\n");
                exit(EXIT_FAILURE);
            }
            ret.type = T_BOOL;
            break;
        case A_OP_SUP:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == T_INT && tpb.type == T_INT){
                if(tpa.entier > tpb.entier){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_FLOAT && tpb.type == T_FLOAT){
                if(tpa.reel > tpb.reel){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_CHAR && tpb.type == T_CHAR){
                if(tpa.caractere > tpb.caractere){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_CHAR && tpb.type == T_INT){
                if(tpa.caractere > tpb.entier){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_INT && tpb.type == T_CHAR){
                if(tpa.entier > tpb.entier){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else{/*On a fait une comparaison entre deux types incomparables*/
                fprintf(stderr, "Erreur comparaison entre deux types incompatibles\n");
                exit(EXIT_FAILURE);
            }
            ret.type = T_BOOL;
            break;
        case A_OP_INFE:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == T_INT && tpb.type == T_INT){
                if(tpa.entier <= tpb.entier){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_FLOAT && tpb.type == T_FLOAT){
                if(tpa.reel <= tpb.reel){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_CHAR && tpb.type == T_CHAR){
                if(tpa.caractere <= tpb.caractere){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_CHAR && tpb.type == T_INT){
                if(tpa.caractere <= tpb.entier){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_INT && tpb.type == T_CHAR){
                if(tpa.entier <= tpb.caractere){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else{/*On a fait une comparaison entre deux types incomparables*/
                fprintf(stderr, "Erreur comparaison entre deux types incompatibles\n");
                exit(EXIT_FAILURE);
            }
            ret.type = T_BOOL;
            break;
        case A_OP_SUPE:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == T_INT && tpb.type == T_INT){
                if(tpa.entier >= tpb.entier){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_FLOAT && tpb.type == T_FLOAT){
                if(tpa.reel >= tpb.reel){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_CHAR && tpb.type == T_CHAR){
                if(tpa.caractere >= tpb.caractere){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_CHAR && tpb.type == T_INT){
                if(tpa.caractere >= tpb.entier){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_INT && tpb.type == T_CHAR){
                if(tpa.entier >= tpb.caractere){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else{/*On a fait une comparaison entre deux types incomparables*/
                fprintf(stderr, "Erreur comparaison entre deux types incompatibles\n");
                exit(EXIT_FAILURE);
            }
            ret.type = T_BOOL;
            break;
        case A_OP_EGAL:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == T_INT && tpb.type == T_INT){
                if(tpa.entier == tpb.entier){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_FLOAT && tpb.type == T_FLOAT){
                if(tpa.reel == tpb.reel){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_CHAR && tpb.type == T_CHAR){
                if(tpa.caractere == tpb.caractere){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_CHAR && tpb.type == T_INT){
                if(tpa.caractere == tpb.entier){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_INT && tpb.type == T_CHAR){
                if(tpa.entier == tpb.caractere){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else{/*On a fait une comparaison entre deux types incomparables*/
                fprintf(stderr, "Erreur comparaison entre deux types incompatibles\n");
                exit(EXIT_FAILURE);
            }
            ret.type = T_BOOL;
            break;
        case A_OP_DIFF:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == T_INT && tpb.type == T_INT){
                if(tpa.entier != tpb.entier){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_FLOAT && tpb.type == T_FLOAT){
                if(tpa.reel != tpb.reel){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_CHAR && tpb.type == T_CHAR){
                if(tpa.caractere != tpb.caractere){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_CHAR && tpb.type == T_INT){
                if(tpa.caractere != tpb.entier){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else if(tpa.type == T_INT && tpb.type == T_CHAR){
                if(tpa.entier != tpb.caractere){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
            }else{/*On a fait une comparaison entre deux types incomparables*/
                fprintf(stderr, "Erreur comparaison entre deux types incompatibles\n");
                exit(EXIT_FAILURE);
            }
            ret.type = T_BOOL;
            break;
        case A_OP_OU:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == T_BOOL && tpb.type == T_BOOL){
                if(tpa.booleen == TRUE || tpa.booleen == TRUE){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
                
            }else{/*On a fait une division entre deux types incompatibles*/
                fprintf(stderr, "Erreur tentative d'operation booleene avec un autre type que booleen\n");
                exit(EXIT_FAILURE);
            }
            ret.type = T_BOOL;
            break;
        case A_OP_ET:
            tpa = evaluer(aa_fils(a));
            tpb = evaluer(aa_frere(aa_fils(a)));
            if(tpa.type == T_BOOL && tpb.type == T_BOOL){
                if(tpa.booleen == TRUE && tpa.booleen == TRUE){
                    ret.booleen = TRUE;
                }else ret.booleen = FALSE;
                
            }else{/*On a fait une division entre deux types incompatibles*/
                fprintf(stderr, "Erreur tentative d'operation booleene avec un autre type que booleen\n");
                exit(EXIT_FAILURE);
            }
            ret.type = T_BOOL;
            break;
        case A_OP_NON:
            tpa = evaluer(aa_fils(a));
            if(tpa.type == T_BOOL){
                if(tpa.booleen == TRUE){
                    ret.booleen = FALSE;
                }else ret.booleen = TRUE;
            }else{/*On a fait une division entre deux types incompatibles*/
                fprintf(stderr, "Erreur tentative d'operation booleene avec un autre type que booleen\n");
                exit(EXIT_FAILURE);
            }
            ret.type = T_BOOL;
            break;
        case A_VIDE:
        case A_CHAMP:
            break;
        default:
            fprintf(stderr, "Erreur arbre invalide dans expression\n");
            exit(EXIT_FAILURE);
    }
    return ret;
}

/* Retrouve l'emplacement mémoire dans la pile correspondant 
au numéro de déclaration donné */
int get_pile (int numdecl) {
    decl champ = td_getdecl(numdecl);
    int NIS_decl = tr_get_reg(champ.numregion).niv_imbric, 
        cs = NIS-NIS_decl, 
        deplacement = champ.exec;

    return pile[pile[BC+cs]+deplacement];
}

/* Place la valeur v dans l'emplacement mémoire i de la pile */
void set_pile (int i, types_pile v) {
    if (i >= 0 && i < TAILLEPILE) pile[i] = v;
    else {
        fprintf(stderr, "Tentative d'accès en dehors de la pile (%d)\n", i);
        exit(EXIT_FAILURE);
    }
}