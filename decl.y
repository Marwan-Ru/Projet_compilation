%{
  int yylex();
  int yyerror();
  extern numligne ;
%}

%token PROG

%token VIRGULE
%token POINT
%token PV
%token DEUX_POINTS
%token CO
%token CF
%token PO
%token PF

%token TYPE
%token INT
/* %token REEL */
/* %token BOOLEEN */
/* %token CARACTERE */
%token IDF
/* %token CHAINE */
/* %token CSTE_ENTIERE */
%token VAR

%token DE
%token TABLEAU
%token STRUCT
%token FSTRUCT
/* %token PROCEDURE */
/* %token FONCTION */

%%
programme : PROG corps
          ;

corps : liste_declarations
      ;

liste_declarations :
                   | liste_declarations declaration PV
                   ;

declaration : declaration_type
            | declaration_variable
            /* | declaration_procedure */
            /* | declaration_fonction */
            ;

declaration_type : TYPE IDF DEUX_POINTS suite_declaration_type
                 ; 

suite_declaration_type : STRUCT liste_champs FSTRUCT
                       | TABLEAU dimension DE nom_type
                       ;

dimension : CO liste_dimensions CF
          ;

liste_dimensions : une_dimension
                 | liste_dimensions VIRGULE une_dimension
                 ;

une_dimension : expression POINT POINT expression
              ;

expression : IDF
           ;

liste_champs : un_champ PV
             | liste_champs un_champ PV
             ;

un_champ : IDF DEUX_POINTS nom_type
         ;

nom_type : type_simple
         | IDF
         ;

type_simple : INT
            ;

declaration_variable : VAR IDF DEUX_POINTS nom_type
                     ;















/* dimension : CO liste_dimensions CF */

/* liste_dimensions : une_dimension */
/*                  | liste_dimensions VIRGULE dimension */
/*                  ; */

/* une_dimension : expression POINT POINT expression */
/*               ; */

/* liste_champs : un_champ */
/*              | liste_champs POINT_VIRGULE un_champ */
/*              ; */

%%
int yyerror()
{
  printf("Erreur de syntaxe en ligne %d\n",numligne) ;
  return numligne;
}

/* decl < tdecl1.cpy */
