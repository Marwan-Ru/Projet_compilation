%{
#include "txtInt.tab.h"
#include <string.h>
%}

%option yylineno
%option nounput
%option noinput
%option noyywrap

%%
\;                                 { return (PV); }
\{                                 { return (PO); }
\}                                 { return (PF); }
\,                                 { return (VIRG); }
\|                                 { return (BARREVERT); }
\_                                 { return (BARREHORI); }
([0]|-?[1-9][0-9]*)                { yylval.t_entier = atoi(yytext); return (ENTIER); }
"---"                              { return (SEPARATEUR); }
[^\-[:blank:]\n].*                 { yylval.t_chaine = strdup(yytext); return (TEXTE); }
[[:blank:]\r\n]
%%
