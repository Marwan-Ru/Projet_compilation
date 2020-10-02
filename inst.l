%{
#include "inst.tab.h"
%}

%%
"program"\n		{ return(PROG); }
begin			{ return(DEBUT); }
end			{ return(FIN); }
;			{ return(POINT_VIRGULE); }
"<-"			{ return(OPAFF); }
[a-zA-Z][a-zA-Z0-9\_]* 	{ return(IDF); }
[1-9][0-9]*		{ return(INT); }
\+			{ return(PLUS); }
\-			{ return(MOINS); }
\*			{ return(MULT); }
\/			{ return(DIV); }
\(			{ return(PO); }
\)			{ return(PF); }
\;			{ return(PV); }
%%
