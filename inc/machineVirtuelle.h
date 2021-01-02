#ifndef "VM"
#define "VM"

#include <stdlib.h>
#include <stdio.h>
#include "tabledecl.h"
#include "tableLex.h"
#include "tablereg.h"
#include "tableTypes.h"
#include "arbreAbstrait.h"

/* pile */
union {
    int entier;
    float reel;
    char booleen;
    char caractere;
} types_pile;

#endif