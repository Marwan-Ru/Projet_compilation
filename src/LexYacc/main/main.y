%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <math.h>
	#include "tableLex.h"

	int yylex();
	extern int yylineno;

	void yyerror (char const *str) {
		fprintf(stderr,"Erreur de syntaxe en ligne %d\n%s\n", yylineno, str);
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

/** Symboles terminaux **/
    /* Structure du programme */
%token PROG "'program'"
%token DEBUT "'begin'"
%token FIN "'fin'"
    /* Déclarations */
%token TYPE "'type'"
%token VAR "'variable'"
%token STRUCT "'struct'"
%token FSTRUCT "'finstruct'"
%token PROCEDURE "'proc'"
%token FONCTION "'funct'"
%token TABLEAU "'tab'"
%token DE "of"
    /* Noms de types de données */
%token T_INT "'int'"
%token T_FLOAT "'float'"
%token T_BOOL "'bool'"
%token T_CHAR "'char'"
%token T_STRING "'string'"
    /* Types de données */
%token INT "entier"
%token FLOAT "réel"
%token BOOL "booléen"
%token STRING "chaîne de caractères"
%token CHAR "caractère"
    /* Opérateurs arithmétique */
%token PLUS "'+'"
%token MOINS "'-'"
%token MULT "'*'"
%token DIV "'/'"
%token MOD "'%'"
%token EXP "'^'"
    /* Opérateurs relationnel */
%token INF "'<'"
%token SUP "'>'"
%token INFE "'<='"
%token SUPE "'>='"
%token EGAL "'='"
%token DIF "'!=''"
    /* Opérateurs logique */
%token OR "'|'"
%token AND "'&'"
%token NOT "'!'"
    /* Opérateurs d'affectation */
%token OPAFF "'<-'"
    /* Ponctuations */
%token PO "'('"
%token PF "')'"
%token CO "'['"
%token CF "']'"
%token POINT "'.'"
%token VIRG "','"
%token PV "';'"
%token POINTPOINT "'..'"
%token GUILLEMET "'\"'"
%token APOSTROPHE "'''" 
%token DEUX_POINTS "':'"
    /* Structures conditionnelles */
%token SI "'if'"
%token ALORS "'then'"
%token SINON "'else'"
%token TANTQUE "'while'"
%token FAIRE "'do'"
%token POUR "'for'"
    /* Entrées & sorties */
%token RETOURNE "'return'"
%token AFFICHER "'print'"
    /* Identifiants */
%token IDF "identifiant"
	/* Misc */
%token INNATENDU "expression"

/** Typage des non-terminaux **/
%nterm <type> nonterm...

%%
programme : PROG IDF corps
		  | PROG corps
		  ;

corps : liste_declarations liste_instructions
      ;



/*** DÉCLARATIONS ***/



liste_declarations :
                   | liste_declarations declaration PV
                   ;

declaration : declaration_type
            | declaration_variable
            | declaration_procedure 
            | declaration_fonction 
            ;


	/** Déclaration de types **/


declaration_type : TYPE IDF DEUX_POINTS suite_declaration_type
                 ; 

suite_declaration_type : STRUCT liste_champs FSTRUCT
                       | TABLEAU dimension DE nom_type
                       ;

		/* Déclaration de tableaux */

dimension : CO liste_dimensions CF
          ;

liste_dimensions : une_dimension
                 | liste_dimensions VIRG une_dimension
                 ;

une_dimension : expression POINTPOINT expression
              ;

		/* Declaration de structures */
		
liste_champs : un_champ PV
             | liste_champs un_champ PV
             ;

un_champ : IDF DEUX_POINTS nom_type
         ;


	/** Déclaration de variables **/


declaration_variable : VAR IDF DEUX_POINTS nom_type
                     ;


	/** Déclaration de procédures **/


declaration_procedure : PROCEDURE IDF liste_parametres corps
                      ;

liste_parametres : 
                 | PO liste_param PF
                 ;

liste_param : un_param
            | liste_param PV un_param
            ;

un_param : IDF DEUX_POINTS type_simple
         ;


	/** Déclaration de fonctions **/


declaration_fonction : FONCTION IDF liste_parametres RETOURNE type_simple corps
                     ;


	/** Déclarations de noms et types de variables **/


nom_type : type_simple
         | IDF
         ;

type_simple : T_INT
            | T_CHAR
            | T_BOOL
            | T_FLOAT
            | T_STRING CO INT CF
            ;



/*** INSTRUCTIONS ***/



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


	/** Affectations **/


affectation : variable OPAFF expression
	    	;

variable : IDF
		 | variable POINT IDF
		 | variable POINT fonction
		 | variable CO expression CF
	 	 ;


	/** Expressions **/


expression : expr_pm
		   | expr_bool_or
		   | constante
		   ;

constante : STRING
		  | CHAR
		  ;

		/* Expressions arithmétiques */

expr_pm : expr_pm PLUS expr_md { $$ = $1 + $3; }
		| expr_pm MOINS expr_md { $$ = $1 - $3; }
		| expr_md
		;

expr_md : expr_md MULT expr_exp { $$ = $1 * $3; } 
		| expr_md DIV expr_exp { $3 == 0 ? yyerror("Division par zéro!") : $$ = $1 / $3; } 
		| expr_md MOD expr_exp { $$ = $1 % $3; } 
		| expr_exp
		;

expr_exp : expr_exp EXP expr_base { $$ = pow($1, $3); } 
		 | MOINS expr_base { $$ = -$1; }
		 | expr_base
		 ;

expr_base : constante_maths
		  | variable
	  	  | PO expr_pm PF
		  | fonction
	  	  ;

constante_maths : INT
		        | FLOAT
			    ;

		/* Expressions relationnels */

expr_comp : expr_pm INF expr_pm
		  | expr_pm SUP expr_pm
		  | expr_pm INFE expr_pm
		  | expr_pm SUPE expr_pm
		  | expr_pm EGAL expr_pm
		  | expr_pm DIF expr_pm
		  ;

		/* Expressions logiques */

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


	/** Appels de fonctions **/


fonction : IDF PO suite_args PF
		 ;

suite_args : 
		   | expression
		   | suite_args VIRG expression
		   ;


	/** Structures conditionnelles **/


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


	/** Entrées & sorties **/


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
	exit(EXIT_SUCCESS);
}