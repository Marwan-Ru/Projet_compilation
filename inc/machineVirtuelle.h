#ifndef VM
#define VM

#include <stdlib.h>
#include <stdio.h>
#include "tabledecl.h"
#include "tableLex.h"
#include "tablereg.h"
#include "tableTypes.h"
#include "arbreAbstrait.h"

/* pile */
typedef union {
    int entier;
    float reel;
    char booleen;
    char caractere;
} types_pile;

#define TAILLEPILE 5000

/* Execute les instructions se trouvant dans l'arbre a */
void execute (arbre a);

/* Evalue l'expression se trouvant dans l'arbre a */
types_pile evaluer (arbre a);

/* Retrouve l'emplacement mémoire dans la pile correspondant 
au numéro lexicographique */
int get_pile (int numlex);

/* Place la valeur v dans l'emplacement mémoire i de la pile */
void remplir_pile (int i, types_pile v);

#endif