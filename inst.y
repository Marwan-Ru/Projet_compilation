%{
#include <stdio.h>

int yylex();

void yyerror (char const *s) {
	fprintf (stderr, "%s\n", s);
}
%}

%token PROG DEBUT FIN
%token OPAFF
%token IDF
%token INT
%token PLUS MOINS
%token MULT DIV
%token PO PF
%token PV
%token INF SUP INFE SUPE EGAL DIF 
%token OR AND NOT

%%
programme : PROG corps
		  ;

corps : liste_instructions
      ;

liste_instructions : DEBUT suite_liste_inst FIN
				   ; 

suite_liste_inst : instruction PV
		 		 | suite_liste_inst instruction PV
		 		 ;

instruction : affectation
	    	;

affectation : variable OPAFF expression
	    	;

variable : IDF
	 	 ;

expression : expr_pm
		   | expr_bool_or
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
		  | MOINS INT
		  | IDF
		  | MOINS IDF
	  	  | PO expr_pm PF
	  	  | MOINS PO expr_pm PF
	  	  ;

expr_comp : expr_pm INF expr_pm
		  | expr_pm SUP expr_pm
		  | expr_pm INFE expr_pm
		  | expr_pm SUPE expr_pm
		  | expr_pm EGAL expr_pm
		  | expr_pm DIF expr_pm
		  ;

expr_bool_or : expr_bool_or OR expr_bool_and
		     | expr_bool_and
		     ;

expr_bool_and : expr_bool_and AND expr_bool_not
			  | expr_bool_not
			  ;

expr_bool_not : NOT expr_bool_base
			  | expr_bool_base
			  ;

expr_bool_base : PO expr_bool_or PF
			   | expr_comp
			   ;

%%

int main(void) {
  yyparse();
}