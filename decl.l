%{
#include "decl.tab.h"
int numligne=1 ;
%}

%%
program                   {return (PROG);}
variable                  {return(VAR) ;}
type                      {return(TYPE);}
struct                    {return(STRUCT);}
fin[ ]*struct             {return(FSTRUCT);}	   
tab                       {return(TABLEAU);}
of                        {return(DE);}

,                         {return (VIRGULE);}
\.                        {return (POINT);}
;                         {return (PV);}
:                         {return (DEUX_POINTS);}
\[                        {return (CO);}
\]                        {return (CF);}
\(                        {return (PO);}
\)                        {return (PF);}

[a-zA-Z][a-zA-Z0-9]* 	  {return(IDF);}
0|[1-9][0-9]*		  {return(INT);}

\n                        {numligne++ ;} 
[ \t]                       ;
%%
