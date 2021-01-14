%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>

	int yylex();
	extern int yylineno;
	void yyerror (char const *str) {
		fprintf(stderr,"Erreur de syntaxe en ligne %d\n%s\n", yylineno, str);
	}
%}

%code requires { 
	#include "tableLex.h"
	#include "tablereg.h"
	#include "tabledecl.h"
	#include "tableTypes.h"
	#include "arbreAbstrait.h"
	#include "machineVirtuelle.h"
}

%code {
	arbre tab[NB_REGIONS];
	int longTab = 0;
}

%union {
	int t_entier;
	char *t_chaine;
	arbre t_arbre;
}

%define parse.error verbose
%locations

%token PV PO PF VIRG SEPARATEUR BARREVERT BARREHORI
%token <t_entier> ENTIER 
%token <t_chaine> TEXTE 
%token <t_chaine> CHAINE 
%type <t_arbre> arbre

%%
corps: valTabLex SEPARATEUR valTabReg SEPARATEUR valTabType SEPARATEUR valTabDecl SEPARATEUR
	 ;

valTabLex: TEXTE { tl_ajout($1); free($1); } valTabLex 
		 |
		 ;

valTabType: ENTIER { tt_ajout($1); } valTabType 
		  |
		  ;

valTabReg: ENTIER PV ENTIER PV ENTIER { longTab = 0; } arbre valTabReg
			{ tr_ajout_reg ($1, $3, $5, $7); }
		 |
		 ;

arbre: PO ENTIER VIRG ENTIER VIRG ENTIER PF { $<t_arbre>$ = (tab[longTab++] = aa_creerNoeud($2, $4, $6)); } suite_arbre 
		{ $$ = $<t_arbre>6; }
	 ;

suite_arbre: BARREVERT ENTIER arbre { aa_concatPereFils(tab[$2], $3); }
		   | BARREHORI ENTIER arbre { aa_concatPereFrere(tab[$2], $3); }
		   |
		   ;

valTabDecl : ENTIER PV ENTIER PV ENTIER PV ENTIER PV ENTIER PV ENTIER valTabDecl { td_set($1, $3, $5, $7, $9, $11); }
		   |
		   ;
%%

int main(int argc, char *argv[]) {
	tl_init();
	tt_init();
	tr_init();
	td_init();

	yyparse();

	if (argc > 1 && (strcmp(argv[1], "-debug") == 0 || strcmp(argv[1], "-d") == 0)) {
		tl_afficher();
		tt_afficher();
		tr_affiche();
		tr_afficherArbres();
		td_afficher();
	}

	execute (tr_get_reg(0).tree);

	tl_detruire();
	td_detruire();

	exit(EXIT_SUCCESS);
}