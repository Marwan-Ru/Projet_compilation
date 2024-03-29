%{
#include "decl.tab.h"
#include <string.h>
int numligne=1 ;
%}

%option nounput
%option noinput
%option noyywrap

%%
program                   {return (PROG);}
variable                  {return(VAR) ;}
type                      {return(TYPE);}
struct                    {return(STRUCT);}
fin[ ]*struct             {return(FSTRUCT);}	   
tab                       {return(TABLEAU);}
of                        {return(DE);}
proc                      {return(PROCEDURE);}
funct                     {return(FONCTION);}
return                    {return(RETOURNE);}

int                       {return(INT);}
char                      {return(CHAR);}
bool                      {return(BOOL);}
float                     {return(REEL);}
string                    {return(CHAINE);}
cst                       {return(CSTE_ENTIERE);}

,                         {return (VIRGULE);}
\.                        {return (POINT);}
;                         {return (PV);}
:                         {return (DEUX_POINTS);}
\[                        {return (CO);}
\]                        {return (CF);}
\(                        {return (PO);}
\)                        {return (PF);}

[a-zA-Z][a-zA-Z0-9]* 	  {yylval.nomVar = strdup(yytext); return(IDF);}


\n                        {numligne++ ;} 
[ \t]                       ;
%%
