%{
#include "inst.tab.h"
%}

%%
"program"\n	        	{ return(PROG); }
"begin"  	        	{ return(DEBUT); }
"end"		            { return(FIN); }
"<-"		        	{ return(OPAFF); }
[a-zA-Z][a-zA-Z0-9\_]* 	{ return(IDF); }
[1-9][0-9]*		        { return(INT); }
\+			            { return(PLUS); }
\-			            { return(MOINS); }
\*			            { return(MULT); }
\/		            	{ return(DIV); }
\(		            	{ return(PO); }
\)		            	{ return(PF); }
;		            	{ return(PV); }
\<                      { return(INF); }
"<="                    { return(INFE); }
\>                      { return(SUP); }
">="                    { return(SUPE); }
\=                      { return(EGAL); }
"!="                    { return(DIF); }
\!                      { return(NOT); }
\&                      { return(AND); }
\|                      { return(OR); }
[\n]
.
%%