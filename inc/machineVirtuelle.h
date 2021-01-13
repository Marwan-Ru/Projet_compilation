#ifndef VM
#define VM

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "tabledecl.h"
#include "tableLex.h"
#include "tablereg.h"
#include "tableTypes.h"
#include "arbreAbstrait.h"

#define TRUE 't'
#define FALSE 'f'

typedef enum { T_INT, T_FLOAT, T_BOOL, T_CHAR, T_ERR } Type;

/* pile */
typedef struct{
    Type type; /*e si c'est un entier, r pour un reel, b pour un booleen, c pour un caractere, x pour une erreur*/
    union {
        int entier;
        float reel;
        char booleen;
        char caractere;
    };
}types_pile;

#define TAILLEPILE 5000

/* Execute les instructions se trouvant dans l'arbre a */
void execute (arbre a);

/* Evalue l'expression se trouvant dans l'arbre a */
types_pile evaluer (arbre a, int i);

/* Retrouve l'emplacement mémoire dans la pile correspondant 
au numéro de déclaration donné */
int get_pile (int numdecl);

/* Place la valeur v dans l'emplacement mémoire i de la pile */
void set_pile (int i, types_pile v);

#endif