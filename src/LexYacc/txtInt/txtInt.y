%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "tableLex.h"
	#include "tableTypes.h"

	int yylex();
	extern int yylineno;
	void yyerror (char const *str) {
		fprintf(stderr,"Erreur de syntaxe en ligne %d\n%s\n", yylineno, str);
	}
%}

%union {
	int t_entier;
	char *t_chaine;
}

%define parse.error verbose
%locations

%token VIRGULE SEPARATEUR
%token <t_entier> ENTIER 
%token <t_chaine> TEXTE 
%token <t_chaine> CHAINE 


%%
corps: valTabLex SEPARATEUR valTabType SEPARATEUR
	 ;

valTabLex: TEXTE { tl_ajout($1); } valTabLex 
		 | TEXTE { tl_ajout($1); }
		 ;

valTabType: ENTIER { tt_ajout($1); } valTabType 
		  | ENTIER { tt_ajout($1); }
		  ;
%%

int main(int argc, char *argv[]) {
	if (argc > 1 && (strcmp(argv[1], "-debug") == 0 ||
					 strcmp(argv[1], "-d") == 0))
		yydebug = 1;

	tl_init();
	tt_init();

	yyparse();

	tl_afficher();
	tt_afficher();

	tl_detruire();

	exit(EXIT_SUCCESS);
}