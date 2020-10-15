%{
#include "inst.tab.h"
%}

%%
"program"\n	        	        { return(PROG); }
"begin"  	        	        { return(DEBUT); }
"end"		                    { return(FIN); }
"<-"		        	        { return(OPAFF); }
([0]|[1-9][0-9]*)		        { return(INT); }
\+			                    { return(PLUS); }
\-			                    { return(MOINS); }
\*			                    { return(MULT); }
\/		            	        { return(DIV); }
\%                              { return(MOD); }
\^                              { return(EXP); }
\(		            	        { return(PO); }
\)		            	        { return(PF); }
;		            	        { return(PV); }
\<                              { return(INF); }
"<="                            { return(INFE); }
\>                              { return(SUP); }
">="                            { return(SUPE); }
\=                              { return(EGAL); }
"!="                            { return(DIF); }
\!                              { return(NOT); }
\&                              { return(AND); }
\|                              { return(OR); }
\.                              { return(POINT); }
\[                              { return(CO); }
\]                              { return(CF); }
\,                              { return(VIRG); }
"if"                            { return(SI); }
"then"                          { return(ALORS); }
"else"                          { return(SINON); }
"while"                         { return(TANTQUE); }
"do"                            { return(FAIRE); }
"for"                           { return(POUR); }
"return"                        { return(RETOURNE); }
[a-zA-Z][a-zA-Z0-9\_]* 	        { return(IDF); }
[\n]
.
%%

//([0]|[1-9][0-9]*)(.[0-9]*)?	    { return(FLOAT); }