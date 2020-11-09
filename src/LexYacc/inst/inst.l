%{
#include "inst.tab.h"
#include <string.h>
%}

%option yylineno

%%
"program"\n	        	        { return(PROG); }
"begin"  	        	        { return(DEBUT); }
"end"		                    { return(FIN); }
"<-"		        	        { return(OPAFF); }
([0]|[1-9][0-9]*)		        { yylval.intVal = atoi(yytext); return(INT); }
([0]|[1-9][0-9]*)\.[0-9]*	    { yylval.floatVal = atof(yytext); return(FLOAT); }
('[^']')|'\\''                  { yylval.charVal = yytext[0]; return(CHAR); }
\"((\\\")|[^(\")])*\"           { yylval.stringVal = strdup(yytext); return(STRING); }
"true"|"false"                  { strcmp(yytext, "true") == 0 ? yylval.boolVal = 1 : yylval.boolVal = 0; 
                                  return(BOOL); }
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
"print"                         { return(AFFICHER); }
\/\/.*
[a-zA-Z][a-zA-Z0-9]* 	        { yylval.stringVal = strdup(yytext); return(IDF); }
[[:blank:]\r\n]
\"                              { return(GUILLEMET); }
'                               { return(PARENTHESE); }
.                               { return(UNEXPECTED); }
%%
