%{
#include "txtInt.tab.h"
#include <string.h>
%}

%option yylineno
%option nounput
%option noinput
%option noyywrap

%%
\;                                 { printf("%s\n", yytext);return (PV); }
\{                                 { printf("%s\n", yytext);return (PO); }
\}                                 { printf("%s\n", yytext);return (PF); }
\,                                 { printf("%s\n", yytext);return (VIRG); }
\|                                 { printf("%s\n", yytext);return (BARREVERT); }
\_                                 { printf("%s\n", yytext);return (BARREHORI); }
([0]|-?[1-9][0-9]*)                { printf("%s\n", yytext);yylval.t_entier = atoi(yytext); return (ENTIER); }
([0]|[1-9][0-9]*)\.[0-9]+	       { printf("%s\n", yytext);yylval.t_chaine = strdup(yytext); return (TEXTE); } /* réels */
\"((\\\")|[^(\")])*\"              { printf("%s\n", yytext);yylval.t_chaine = strdup(yytext); return (TEXTE); } /* Chaînes de caractère */
[a-zA-Z][a-zA-Z0-9]* 	           { printf("%s\n", yytext);yylval.t_chaine = strdup(yytext); return (TEXTE); } /* Identifiants */
"---"                              { printf("%s\n", yytext);return (SEPARATEUR); }
[[:blank:]\r\n]                     { printf("%s\n", yytext);}
.                                  { printf("%s\n", yytext);}
%%