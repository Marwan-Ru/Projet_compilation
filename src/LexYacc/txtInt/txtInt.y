%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "tableLex.h"
	#include "tableTypes.h"
	#include "tableReg.h"
	#include "arbreAbstrait.h"
	#include "allocation.h"

	int yylex();
	extern int yylineno;
	void yyerror (char const *str) {
		fprintf(stderr,"Erreur de syntaxe en ligne %d\n%s\n", yylineno, str);
	}

	int nbVal, **tabVal, i;

	void allocTabVal (int n) {
		nbVal = n;
		tabVal = allocation_mem(n, sizeof(int *));
		for (i = 0; i < n; i++) {
			tabVal[i] = allocation_mem(2, sizeof(int));
		}
		i = 0;
	}
%}

%union {
	int t_entier;
	char *t_chaine;
}

%define parse.error verbose
%locations

%token PV PO PF VIRG SEPARATEUR
%token <t_entier> ENTIER 
%token <t_chaine> TEXTE 
%token <t_chaine> CHAINE 

%%
corps: valTabLex SEPARATEUR valTabReg SEPARATEUR valTabType SEPARATEUR
	 ;

valTabLex: TEXTE { tl_ajout($1); free($1); } valTabLex 
		 | TEXTE { tl_ajout($1); free($1); }
		 ;

valTabType: ENTIER { tt_ajout($1); } valTabType 
		  | ENTIER { tt_ajout($1); }
		  ;

valTabReg: ENTIER PV ENTIER PV ENTIER PV ENTIER { allocTabVal($7); } 
		   tabArbre { arbre a = aa_tableauVersArbre(tabVal, i-1); tr_ajout_reg($1, $3, $5, a); }
		 | ENTIER PV ENTIER PV ENTIER PV ENTIER { allocTabVal($7); } 
		   tabArbre { arbre a = aa_tableauVersArbre(tabVal, i-1); tr_ajout_reg($1, $3, $5, a); }
		 ;

tabArbre: PO ENTIER VIRG ENTIER PF PV { tabVal[i][0] = $2; tabVal[i++][1] = $4; } tabArbre
		| PO ENTIER VIRG ENTIER PF { tabVal[i][0] = $2; tabVal[i++][1] = $4; }
%%

int main(int argc, char *argv[]) {
	if (argc > 1 && (strcmp(argv[1], "-debug") == 0 ||
					 strcmp(argv[1], "-d") == 0))
		yydebug = 1;

	tl_init();
	tt_init();
	tr_init();

	yyparse();

	tl_afficher();
	tt_afficher();
	tr_affiche();

	tr_detruire();
	tl_detruire();

	exit(EXIT_SUCCESS);
}