#include "arbreAbstrait.h"

int indent;

arbre aa_vide () {
	return NULL;
}

arbre aa_creerNoeud (Identifiant id, int valeur, int num_decl) {
	arbre a = allocation_mem(1, sizeof(struct struct_arbre));
	a->id = id;
	a->valeur = valeur;
	a->num_decl = num_decl;
    a->fils = aa_vide();
    a->frere = aa_vide();
    return a;
}

/* Renvoie pere */
arbre aa_concatPereFrere (arbre pere, arbre frere) {
	pere->frere = frere;
	return pere;
} 

/* Renvoie pere */
arbre aa_concatPereFils (arbre pere, arbre fils) {
	pere->fils = fils;
	return pere;
} 

/* Fonction locale utilitaire pour aa_afficher */
char *id_to_string (Identifiant id) {
	switch (id) {
		case A_VIDE: return "A_VIDE";
		case A_LISTE: return "A_LISTE";
		case A_IDF: return "A_IDF";
		case A_CSTE_ENT: return "A_CSTE_ENT";
		case A_CSTE_REELE: return "A_CSTE_REELE";
		case A_CSTE_BOOL: return "A_CSTE_BOOL";
		case A_CSTE_CAR: return "A_CSTE_CAR";
		case A_CSTE_CHAINE: return "A_CSTE_CHAINE";
		case A_APPEL_FONC: return "A_APPEL_FONC";
		case A_LISTEPARAMS: return "A_LISTEPARAMS";
		case A_OPAFF: return "A_OPAFF";
		case A_IF_THEN_ELSE: return "A_IF_THEN_ELSE";
		case A_WHILE: return "A_WHILE";
		case A_DO_WHILE: return "A_DO_WHILE";
		case A_FOR: return "A_FOR";
		case A_OP_PLUS: return "A_OP_PLUS";
		case A_OP_MOINS: return "A_OP_MOINS";
		case A_OP_MULT: return "A_OP_MULT";
		case A_OP_DIV: return "A_OP_DIV";
		case A_OP_EXP: return "A_OP_EXP";
		case A_OP_MODUL: return "A_OP_MODUL";
		case A_OP_INF: return "A_OP_INF";
		case A_OP_SUP: return "A_OP_SUP";
		case A_OP_INFE: return "A_OP_INFE";
		case A_OP_SUPE: return "A_OP_SUPE";
		case A_OP_EGAL: return "A_OP_EGAL";
		case A_OP_DIFF: return "A_OP_DIFF";
		case A_OP_OU: return "A_OP_OU";
		case A_OP_ET: return "A_OP_ET";
		case A_OP_NON: return "A_OP_NON";
		case A_LISTE_INDICES: return "A_LISTE_INDICES";
		case A_CHAMP: return "A_CHAMP";
		case A_AFFICHER: return "A_AFFICHER";
		case A_RETOURNER: return "A_RETOURNER";
		case A_LIRE: return "A_LIRE";
		default: return "la fonction id_to_string n'est pas à jour!";
	}
}

/* Fonction locale utilitaire pour aa_afficher */
char *strdup(const char *src) {
	/* Prévoit l'espace nécessaire après */
    char *dst = malloc(strlen (src) + 15); 
    if (dst == NULL) return NULL;        
    strcpy(dst, src);             
    return dst;                           
}

/* Fonction locale utilitaire pour aa_afficher */
void afficher_rec (arbre a, char *indent) {
	char *newIndent;
	int i, l = strlen(indent);

	printf("%s%s (%d", indent, id_to_string(aa_id(a)), aa_valeur(a));
	if (aa_id(a) == A_CSTE_CAR) printf(": '%c'", aa_valeur(a));
	printf(", %d)\n", aa_num_decl(a));

	/* └ = \342\224\224 
	   ├ = \342\224\234 
	   │ = \342\224\202 */
	if (l >= 14) {
		if (indent[l-12] == '\234') indent[l-12] = '\202';
		else for (i = l-14; i < l-11; i++) indent[i] = ' ';
		indent[l-11] = '\0';
	}
	
	newIndent = strdup(indent);
	if (a->fils != aa_vide() && a->frere != aa_vide()) {
		strcat(newIndent, "├─fils─ ");
		afficher_rec (a->fils, newIndent);
		free(newIndent);

		newIndent = strdup(indent);
		strcat(newIndent, "└frère─ ");
		afficher_rec (a->frere, newIndent);
	} else if (a->frere != aa_vide()) {
		strcat(newIndent, "└frère─ ");
		afficher_rec(a->frere, newIndent);
	} else if (a->fils != aa_vide()) {
		strcat(newIndent, "└─fils─ ");
		afficher_rec(a->fils, newIndent);
	}
	free(newIndent);
}

void aa_afficher (arbre a) {
	if (a != aa_vide()) afficher_rec(a, "");
	else printf("A_VIDE\n");
}

arbre aa_frere (arbre a) {
	if (a != aa_vide()) return a->frere;
	else return NULL;
}

arbre aa_fils (arbre a) {
	if (a != aa_vide()) return a->fils;
	else return NULL;
}

int aa_valeur (arbre a) {
	if (a != aa_vide()) return a->valeur;
	else return -1;
}

int aa_num_decl (arbre a) {
	if (a != aa_vide()) return a->num_decl;
	else return -1;
}

Identifiant aa_id (arbre a) {
	if (a != aa_vide()) return a->id;
	else return A_VIDE;
}

void ecrireFichier_rec (FILE *f, arbre a) {
	int localIndent = indent;

	fprintf(f, "{%d,%d,%d}", aa_id(a), aa_valeur(a), aa_num_decl(a));

	if (aa_fils(a) != aa_vide()) {
		fprintf(f, "|%d", localIndent);
		indent++;
		ecrireFichier_rec(f, aa_fils(a));
	} 
	if (aa_frere(a) != aa_vide()) {
		fprintf(f, "_%d", localIndent);
		indent++;
		ecrireFichier_rec(f, aa_frere(a));
	}
}

/* Ecrit l'arbre vers le fichier ouver f */
void aa_ecrireFichier (FILE *f, arbre a) {
	if (a == aa_vide())
		fprintf(f, "{0,-1}");
	else {
		indent = 0;
		ecrireFichier_rec(f, a);
	}
	fprintf(f, "\n");
}

/* Détruit seulement la racine de l'arbre a */
void aa_detruire (arbre a) {
    libere_mem(&a);
}

/* Détruit récursivement tous les noeuds de l'arbre a */
void aa_detruire_rec (arbre a) {
	if (a == aa_vide()) return;
	if(a->fils != aa_vide())
		aa_detruire_rec(a->fils);
	if(a->frere != aa_vide())
		aa_detruire_rec(a->frere);
    aa_detruire(a);
}
