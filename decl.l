%{
#include "y.tab.h"
%}

%%
"program"                 {return (PROG);}
,                         {return (VIRGULE);}
\.                        {return (POINT);}
;                         {return (PV);}
:                         {return (DEUX_POINTS);}

%%
