%{
#include "main.tab.h"
#include <string.h>
int NIS = 0;
int cmp_reg = 0;
int taille = 0;
%}

%option yylineno
%option nounput
%option noinput
%option noyywrap

%%
    /* Structure du programme */
"program"	        	        { return(PROG); }
"begin"  	        	        { return(DEBUT); }
"end"		                    { return(FIN); }

    /* Déclarations */
"type"                          { return(TYPE); }
"variable"                      { return(VAR); }
"struct"                        { return(STRUCT); }
"end"[[:blank:]]?"struct"       { return(FSTRUCT); }
"proc"                          { return(PROCEDURE); }
"funct"                         { return(FONCTION); }	
"tab"                           { return(TABLEAU); }
"of"                            { return(DE); }

    /* Noms de types de données */
"int"                           { return(T_INT); }
"char"                          { return(T_CHAR); }
"bool"                          { return(T_BOOL); }
"float"                         { return(T_FLOAT); }
"string"                        { return(T_STRING); }

    /* Types de données */
([0]|[1-9][0-9]*)		        { yylval.t_int = atoi(yytext); return(INT); }
([0]|[1-9][0-9]*)\.[0-9]+	    { yylval.t_int = tl_ajout(yytext); return(FLOAT); }
('[^']')|'\\''                  { yylval.t_int = yytext[1]; return(CHAR); }
\"((\\\")|[^(\")])*\"           { yylval.t_int = tl_ajout(yytext); return(STRING); }
"true"|"false"                  { yylval.t_int = (yytext[0] == 't'); return(BOOL); }

    /* Opérateurs arithmétique */
\+			                    { return(PLUS); }
\-			                    { return(MOINS); }
\*			                    { return(MULT); }
\/		            	        { return(DIV); }
\%                              { return(MOD); }
\^                              { return(EXP); }

    /* Opérateurs relationnel */
\<                              { return(INF); }
"<="                            { return(INFE); }
\>                              { return(SUP); }
">="                            { return(SUPE); }
\=                              { return(EGAL); }
"!="                            { return(DIF); }

    /* Opérateurs logique */
\!                              { return(NOT); }
\&                              { return(AND); }
\|                              { return(OR); }

    /* Opérateurs d'affectation */
"<-"		        	        { return(OPAFF); }

    /* Ponctuations */
\(		            	        { return(PO); }
\)		            	        { return(PF); }
;		            	        { return(PV); }
".."                            { return(POINTPOINT); }
\.                              { return(POINT); }
\[                              { return(CO); }
\]                              { return(CF); }
\,                              { return(VIRG); }
\:                              { return(DEUX_POINTS); }

    /* Structures conditionnelles */
"if"                            { return(SI); }
"then"                          { return(ALORS); }
"else"                          { return(SINON); }
"while"                         { return(TANTQUE); }
"do"                            { return(FAIRE); }
"for"                           { return(POUR); }

    /* Entrées & sorties */
"return"                        { return(RETOURNE); }
"print"                         { return(AFFICHER); }
"read"                          { return(LIRE); }

    /* Commentaires */
\/\/.*

    /* Identifiants */
[a-zA-Z][a-zA-Z0-9]* 	        { yylval.t_int = tl_ajout(yytext); return(IDF); }

    /* Misc */
[[:blank:]\r\n]
\"                              { return(GUILLEMET); }
'                               { return(APOSTROPHE); }
.                               { return(INNATENDU); }
%%
