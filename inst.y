%{
#include <stdio.h>
int yylex();
void yyerror (char const *s) {
	fprintf (stderr, "%s\n", s);
}
%}

%token PROG DEBUT FIN
%token POINT_VIRGULE
%token OPAFF
%token IDF
%token INT
%token PLUS MOINS
%token MULT DIV
%token PO PF
%token PV

%%
programme : PROG corps
	  ;

corps : liste_instructions
      ;

liste_instructions : DEBUT suite_liste_inst FIN
 		   ; 

suite_liste_inst : instruction POINT_VIRGULE
		 | suite_liste_inst instruction
		 ;

instruction : affectation
	    ;

affectation : variable OPAFF expression PV
	    ;

variable : IDF
	 ;

expression : expr_pm
	   ;

expr_pm : expr_pm PLUS expr_md
	| expr_pm MOINS expr_md
	| expr_md
	;

expr_md : expr_md MULT expr_base
	| expr_md DIV expr_base
	| expr_base
	;

expr_base : INT
	  | IDF
	  | PO expr_pm PF
	  ;


%%
