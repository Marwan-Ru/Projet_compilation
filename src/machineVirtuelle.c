#include "machineVirtuelle.h"

types_pile pile[TAILLEPILE];
types_pile buffer[TAILLEPILE];
int NIS = 0, BC = 0, current = 0;
region reg;

/* Execute les instructions se trouvant dans l'arbre a */
void execute (arbre a) {
    int i, newBC, newNIS, nbParam, escape;
    region newReg;
    decl declaration;
    types_pile v, w, x, tmp;
    arbre tmpArbre;
    char *tmpStr;

    if (a == aa_vide()) return;
    
    switch (a->id) {
        case A_LISTE:
            execute(aa_fils(a));
            execute(aa_frere(aa_fils(a)));
            break;
        case A_OPAFF:
            w = evaluer(aa_fils(a), 0);
            if(w.type != 'e'){
                fprintf(stderr, "Erreur affectation dans arbre\n");
                exit(EXIT_FAILURE);
            }
            i = get_pile(w.entier);
            v = evaluer(aa_frere(aa_fils(a)), 1);
            set_pile(i, v);
            break;
        case A_APPEL_FONC:
            declaration = td_getdecl(aa_num_decl(a));
            newReg = tr_get_reg(declaration.exec);
            newBC = BC + reg.taille_zone;
            newNIS = newReg.niv_imbric;

            /* Vérification */
            if (newNIS < 0 || newNIS > NIS+1) {
                printf("La région '%s' est innacessible\n", tl_getLex(aa_valeur(a)));
                exit(EXIT_FAILURE);
            }

            /* Chaînage dynamique */
            tmp.entier = BC;
            tmp.type = T_INT;
            set_pile(newBC, tmp);

            /* Chaînage statique */
            if (newNIS == NIS+1) {
                /* On ajoute la BC puis on copie le chainage statique de la région d'avant */
                set_pile(newBC+1, tmp);
                for (i = 0; i < NIS; i++) {
                    tmp.entier = BC+1+i;
                    set_pile(newBC+2+i, tmp);
                }
            } else {
                /* On copie le chainage statique de la dernière région ayant le même NIS */
                for (i = NIS - newNIS; i < NIS; i++){
                    tmp.entier = BC+1+i;
                    set_pile(newBC+1+i-(NIS-newNIS), tmp);
                } 
            }

            BC = newBC;
            NIS = newNIS;
            reg = newReg;

            /* Arguments */
            tmpArbre = aa_fils(a);
            if (declaration.NATURE == FUNCT) {
                for (i = 0; i < tt_foncNbParam(declaration.index); i++) {
                    if (aa_fils(tmpArbre) != aa_vide()) {
                        tmpArbre = aa_fils(tmpArbre);
                        tmp = evaluer(tmpArbre, 1);
                        if (tmp.type != tt_foncTypeParam(declaration.index, i)) {
                            printf("L'argument %d d'un appel à la fonction '%s' à un type invalide!\n", i, tl_getLex(aa_valeur(a)));
                            exit(EXIT_FAILURE);
                        }
                        set_pile(BC+NIS+i, tmp);
                        tmpArbre = aa_frere(tmpArbre);
                    } else {
                        printf("Il manque des arguments dans un appel à la fonction '%s'!\n", tl_getLex(aa_valeur(a)));
                        exit(EXIT_FAILURE);
                    }
                }
            } else { /* Procédure */
                for (i = 0; i < tt_procNbParam(declaration.index); i++) {
                    if (aa_fils(tmpArbre) != aa_vide()) {
                        tmpArbre = aa_fils(tmpArbre);
                        tmp = evaluer(tmpArbre, 1);
                        if (tmp.type != tt_procTypeParam(declaration.index, i)) {
                            printf("L'argument %d d'un appel à la procédure '%s' à un type invalide!\n", i, tl_getLex(aa_valeur(a)));
                            exit(EXIT_FAILURE);
                        }
                        set_pile(BC+NIS+i, tmp);
                        tmpArbre = aa_frere(tmpArbre);
                    } else {
                        printf("Il manque des arguments dans un appel à la procédure '%s'!\n", tl_getLex(aa_valeur(a)));
                        exit(EXIT_FAILURE);
                    }
                }
            }

            /* Execution du corps */
            execute(reg.tree);
        case A_IF_THEN_ELSE: 
            x = evaluer(aa_fils(a), 1);
            if(x.type != T_BOOL){
                fprintf(stderr, "Erreur affectation dans arbre\n");
                exit(EXIT_FAILURE);
            }
            if ((aa_frere(aa_fils(a)) == aa_vide()) || (aa_frere(aa_frere(aa_fils(a))))) {
                fprintf(stderr, "Erreur noeud absent de l'arbre\n");
                exit(EXIT_FAILURE);
            }

            if (evaluer(aa_fils(a), 1).booleen == TRUE) execute(aa_frere(aa_fils(a)));
            else execute(aa_frere(aa_frere(aa_fils(a))));
            break;
        case A_WHILE: 
            x = evaluer(aa_fils(a), 1);
            if(x.type != T_BOOL){
                fprintf(stderr, "Erreur affectation dans arbre\n");
                exit(EXIT_FAILURE);
            }
            if (aa_frere(aa_fils(a)) == aa_vide()) {
                fprintf(stderr, "Erreur noeud absent de l'arbre\n");
                exit(EXIT_FAILURE);
            }

            if (evaluer(aa_fils(a), 1).booleen == TRUE) {
                execute(aa_frere(aa_fils(a)));
                execute(a);
            }
            break;
        case A_DO_WHILE:
            x = evaluer(aa_frere(aa_fils(a)), 1);
            if(x.type != T_BOOL){
                fprintf(stderr, "Erreur affectation dans arbre\n");
                exit(EXIT_FAILURE);
            }
            if (aa_fils(a) == aa_vide()) {
                fprintf(stderr, "Erreur noeud absent de l'arbre\n");
                exit(EXIT_FAILURE);
            }

            execute(aa_fils(a));
            if (evaluer(aa_frere(aa_fils(a)), 1).booleen == TRUE) {
                execute(a);
            }
            break;
        case A_FOR:
            x = evaluer(aa_frere(aa_fils(a)), 1);
            if(x.type != T_BOOL){
                fprintf(stderr, "Erreur affectation dans arbre\n");
                exit(EXIT_FAILURE);
            }

            if ((aa_fils(a) == aa_vide()) || (aa_frere(aa_frere(aa_fils(a)))) || (aa_frere(aa_frere(aa_frere(aa_fils(a)))) == aa_vide())) {
                fprintf(stderr, "Erreur noeud absent de l'arbre\n");
                exit(EXIT_FAILURE);
            }

            execute(aa_fils(a));
            if (evaluer(aa_frere(aa_fils(a)), 1).booleen == TRUE) {
                execute(aa_frere(aa_frere(aa_frere(aa_fils(a)))));
                execute(aa_frere(aa_frere(aa_fils(a))));
                execute(a);
            }
            break;
        case A_RETOURNER:
            x = evaluer(aa_fils(a), 1);
            if(x.type != T_BOOL){
                fprintf(stderr, "Erreur affectation dans arbre\n");
                exit(EXIT_FAILURE);
            }
            buffer[current] = evaluer(aa_fils(a), 1);
            current++;
            break;
        case A_AFFICHER:
            tmpStr = tl_getLex(aa_valeur(a));
            tmpArbre = aa_fils(a);

            /* On traverse la chaîne */
            i = 1;
            escape = 0;
            while (tmpStr[i] != '"' || (escape && tmpStr[i] == '"')) {
                if (tmpStr[i] == '\\') escape = 1;
                else if (escape && tmpStr[i] == '\\') printf("\\");
                else if (escape && tmpStr[i] == '"') printf("\"");
                else if (escape && tmpStr[i] == '%') printf("%");
                else if (tmpStr[i] == '%') {
                    /* On récupère le prochain argument */
                    if (aa_fils(tmpArbre) == aa_vide()) {
                        printf("Il manque un ou des arguments pour l'affichage de %s\n", tmpStr);
                        exit(EXIT_FAILURE);
                    }

                    i++;

                    if (tmpStr[i] == 's') {
                        if (aa_id(aa_fils(tmpArbre)) != A_CSTE_CHAINE) {
                            printf("L'argument pour l'affichage d'une chaîne de caractères dans %s est incorrect\n", tmpStr);
                            exit(EXIT_FAILURE);
                        } 
                        printf("%s", tl_getLex(aa_valeur(a)));
                        continue;
                    }
                    
                    tmp = evaluer(aa_fils(tmpArbre), 1);
                    tmpArbre = aa_frere(aa_fils(tmpArbre));
                    switch (tmpStr[i]) {
                        case 'c':
                            if (tmp.type != T_CHAR) {
                                printf("L'argument pour l'affichage d'un caractère dans %s est incorrect\n", tmpStr);
                                exit(EXIT_FAILURE);
                            }
                            printf("%c", tmp.caractere);
                            break;
                        case 'd':
                            if (tmp.type != T_INT) {
                                printf("L'argument pour l'affichage d'un entier dans %s est incorrect\n", tmpStr);
                                exit(EXIT_FAILURE);
                            }
                            printf("%d", tmp.entier);
                            break;
                        case 'f':
                            if (tmp.type != T_FLOAT) {
                                printf("L'argument pour l'affichage d'un réel dans %s est incorrect\n", tmpStr);
                                exit(EXIT_FAILURE);
                            }
                            printf("%f", tmp.reel);
                            break;
                        case 'b':
                            if (tmp.type != T_BOOL) {
                                printf("L'argument pour l'affichage d'un booléen dans %s est incorrect\n", tmpStr);
                                exit(EXIT_FAILURE);
                            }
                            if (tmp.booleen == TRUE) printf("true");
                            else printf("false");
                            break;
                        default:
                            printf("'\%%c' n'est pas un spécificateur de format correct");
                            exit(EXIT_FAILURE);
                    }
                }
                i++;
                escape = 0;
            }
            break;
        case A_LIRE:
            tmpArbre = aa_fils(a);

            while (aa_fils(tmpArbre) != aa_vide()) {
                /* On récupère le type et l'emplacement de l'argument */
                tmp = evaluer(aa_fils(tmpArbre), 0);
                switch (tmp.type) {
                    case T_INT:
                        scanf("%d", pile[tmp.entier]);
                        break;
                    case T_FLOAT:
                        scanf("%d", pile[tmp.entier]);
                        break;
                    case T_BOOLEAN:
                        scanf("%d", pile[tmp.entier]);
                        break;
                    case T_CHAR:
                        scanf("%d", pile[tmp.entier]);
                        break;
                    default:
                        printf("Erreur dans un argument lors d'une lecture\n");
                        exit(EXIT_FAILURE);
                }
                tmpArbre = aa_frere(aa_fils(tmpArbre));
            }
            break;
        case A_VIDE:
        default:
            break;
    }
}

/*
 *Evalue l'expression se trouvant dans l'arbre a 
 *prend en paramètre l'arbre a evaluer et un int, 
 *si valeur == 1 on retourne la valeur des idf et champs, 
 *sinon on retourne le décalage a l'execution
 *Auteur : Marwan Ait Addi
 */
types_pile evaluer(arbre a, int valeur) {
    if (a == aa_vide()) return;
    
    types_pile ret, tpa, tpb; /*tpa et tpb pour les opérations booléenes*/
    /*initialisation de la structure retournée*/
    ret.type = T_ERR; /*erreur*/

    switch (a->id) {
        case A_IDF:
            if(valeur == 1){
                ret = pile[getpile(aa_valeur(a))];
            }else{
                ret.entier = getpile(aa_valeur(a));
                ret.type = T_INT;
            }
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
            tpa = evaluer(aa_fils(a), 1);
            tpb = evaluer(aa_frere(aa_fils(a)), 1);
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
            tpa = evaluer(aa_fils(a), 1);
            tpb = evaluer(aa_frere(aa_fils(a)), 1);
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
            tpa = evaluer(aa_fils(a), 1);
            tpb = evaluer(aa_frere(aa_fils(a)), 1);
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
            tpa = evaluer(aa_fils(a), 1);
            tpb = evaluer(aa_frere(aa_fils(a)), 1);
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
            tpa = evaluer(aa_fils(a), 1);
            tpb = evaluer(aa_frere(aa_fils(a)), 1);
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
            tpa = evaluer(aa_fils(a), 1);
            tpb = evaluer(aa_frere(aa_fils(a)), 1);
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
            tpa = evaluer(aa_fils(a), 1);
            tpb = evaluer(aa_frere(aa_fils(a)), 1);
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
            tpa = evaluer(aa_fils(a), 1);
            tpb = evaluer(aa_frere(aa_fils(a)), 1);
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
            tpa = evaluer(aa_fils(a), 1);
            tpb = evaluer(aa_frere(aa_fils(a)), 1);
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
            tpa = evaluer(aa_fils(a), 1);
            tpb = evaluer(aa_frere(aa_fils(a)), 1);
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
            tpa = evaluer(aa_fils(a), 1);
            tpb = evaluer(aa_frere(aa_fils(a)), 1);
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
            tpa = evaluer(aa_fils(a), 1);
            tpb = evaluer(aa_frere(aa_fils(a)), 1);
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
            tpa = evaluer(aa_fils(a), 1);
            tpb = evaluer(aa_frere(aa_fils(a)), 1);
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
            tpa = evaluer(aa_fils(a), 1);
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
        case A_CHAMP:
            /*On dois déterminer a quel champs de la structure on souhaite acceder*/
            /*Le premier idf c'est la structure d'ou on part*/
            ret = evaluer(aa_fils(a), 0);
            arbre tmp = aa_fils(a);
            while(aa_frere(tmp) != aa_vide() && aa_frere(tmp)->id == A_CHAMP){
                ret.entier++;
                tmp = aa_fils(aa_frere(tmp));
            }
            /*Si c'est la valeur qu'on cherche on renvoie ce qui se trouve dans la pile a cet index la*/
            if(valeur = 1) ret = pile[ret.entier];
            break;
        case A_APPEL_FONC:
            current--;
            ret = buffer[current];
            ret.type = buffer[current].type;          
            break;
        case A_VIDE:
        default:
            fprintf(stderr, "Erreur arbre invalide dans expression\n");
            exit(EXIT_FAILURE);
    }
    return ret;
}

/* Retrouve l'emplacement mémoire dans la pile correspondant 
au numéro de déclaration donné */
types_pile get_pile (int numdecl) {
    decl champ = td_getdecl(numdecl);
    int NIS_decl = tr_get_reg(champ.numregion).niv_imbric, 
        cs = NIS-NIS_decl, 
        deplacement = champ.exec;

    return pile[pile[BC+cs].entier+deplacement];
}

/* Place la valeur v dans l'emplacement mémoire i de la pile */
void set_pile (int i, types_pile v) {
    if (i >= 0 && i < TAILLEPILE) pile[i] = v;
    else {
        fprintf(stderr, "Tentative d'accès en dehors de la pile (%d)\n", i);
        exit(EXIT_FAILURE);
    }
}