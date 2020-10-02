%{
  int yylex();
  int yyerror();
  %}

%token PROG

%token VIRGULE
%token POINT
%token PV
%token DEUX_POINTS
/* %token CO */
/* %token CF */
/* %token PO */
/* %token PF */

/* %token TYPE */
/* %token ENTIER */
/* %token REEL */
/* %token BOOLEEN */
/* %token CARACTERE */
/* %token IDF */
/* %token CHAINE */
/* %token CSTE_ENTIERE */
/* %token VARIABLE */

/* %token STRUCT */
/* %token FSTRUCT */
/* %token PROCEDURE */
/* %token FONCTION */

%%
programme : PROG corps
          ;

corps : liste_declarations
      ;

liste_declarations : declaration PV
                   | liste_declarations declaration PV
                   ;

declaration : declaration_type
            | declaration_variable
            | declaration_procedure
            | declaration_fonction
            ;

declaration_type : TYPE IDF DEUX_POINTS suite_declaration_type
                 ;

suite_declaration_type : STRUCT liste_champs FSTRUCT
                       | TABLEAU dimension DE nom_type
                       ;

dimension : CO liste_dimensions CF
%%
