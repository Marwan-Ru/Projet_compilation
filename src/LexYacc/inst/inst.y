%{
#include <stdio.h>
#include <string.h>

int yylex();
extern int yylineno;

void yyerror (char const *str) {
    fprintf(stderr,"Error | Line: %d\n%s\n",yylineno,str);
}
%}

%union {
	int intVal;
    float floatVal;
    char *stringVal;
	char charVal;
	int boolVal;
}

%define parse.error verbose
%locations

%token PROG DEBUT FIN
%token OPAFF
%token IDF
%token INT FLOAT BOOL
%token STRING CHAR
%token PLUS MOINS
%token MULT DIV MOD
%token EXP
%token PO PF CO CF
%token PV
%token INF SUP INFE SUPE EGAL DIF 
%token OR AND NOT
%token POINT VIRG
%token SI ALORS SINON
%token TANTQUE FAIRE
%token POUR
%token RETOURNE
%token AFFICHER
%token GUILLEMET PARENTHESE
%token UNEXPECTED

%%
programme : PROG IDF corps
		  | PROG corps
		  ;

corps : liste_instructions
      ;

liste_instructions : DEBUT suite_liste_inst FIN
				   ; 

suite_liste_inst : instruction PV
		 		 | suite_liste_inst instruction PV
		 		 ;

instruction : affectation
            | variable POINT fonction
			| fonction
			| condition
			| tantque
			| pour
			| RETOURNE resultat_retourne
			| afficher
	    	;

affectation : variable OPAFF expression
	    	;

variable : IDF
		 | variable POINT IDF
		 | variable POINT fonction
		 | variable CO liste_indices CF
	 	 ;

liste_indices : expr_pm
              | liste_indices VIRG expr_pm
              ;

expression : expr_pm
		   | expr_bool_or
		   | constante
		   ;




constante : STRING
		  | CHAR
		  ;




expr_pm : expr_pm PLUS expr_md
		| expr_pm MOINS expr_md
		| expr_md
		;

expr_md : expr_md MULT expr_exp
		| expr_md DIV expr_exp
		| expr_md MOD expr_exp
		| expr_exp
		;

expr_exp : expr_exp EXP expr_base
		 | expr_base
         | MOINS expr_base
		 ;

expr_base : constante_maths
		  | variable
	  	  | PO expr_pm PF
		  | fonction
	  	  ;

constante_maths : INT
		        | FLOAT
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
			   | BOOL
			   ;




fonction : IDF PO suite_args PF
		 ;

suite_args : 
		   | expression
		   | suite_args VIRG expression
		   ;



condition : SI expr_cond ALORS liste_instructions
		  | SI expr_cond ALORS liste_instructions SINON liste_instructions
		  ;

expr_cond : expr_bool_or
		  | variable
		  ;


tantque : TANTQUE expr_cond FAIRE liste_instructions
		| FAIRE liste_instructions TANTQUE expr_cond
		;


pour : POUR expression PV expr_cond PV instruction FAIRE liste_instructions
	 ;

resultat_retourne : 
				  | expression
				  ;

afficher : AFFICHER PO expression PF
		 ;
%%

int main(int argc, char *argv[]) {
	if (argc > 1 && (strcmp(argv[1], "-debug") == 0 ||
					 strcmp(argv[1], "-d") == 0))
		yydebug = 1;
	yyparse();
	return(0);
}