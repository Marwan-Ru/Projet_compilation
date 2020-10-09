%{
#include "decl.tab.h"
%}

%%
"program"                 {return (PROG);}
,                         {return (VIRGULE);}
\.                        {return (POINT);}
;                         {return (PV);}
:                         {return (DEUX_POINTS);}
\[                        {return (CO);}
\]                        {return (CF);}
\(                        {return (PO);}
\)                        {return (PF);}

"type"                    {return(TYPE);}
[a-zA-Z][a-zA-Z0-9\_]* 	  {return(IDF);}

[1-9][0-9]*		  {return(INT);}
%%
