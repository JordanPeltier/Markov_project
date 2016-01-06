%{
#include <iostream>
#include <vector>    
#include <unordered_map>    
#include "Pimc.h"
#include "parsepimc.tab.h"

using namespace std;
#define YY_DECL extern "C" int yylex()
%}

%% 
[ \t\n] ; // ignore whitespaces, carriage returns
pIMC        { return PIMC; }
end         { return END; }
with        { return WITH; }
->          { return ARROW; }
[0-9]+         { yylval.ival = atoi(yytext); return INT; }
[a-zA-Z0-9\.]+   {
	// we have to copy because we can't rely on yytext not changing underneath us:
	yylval.sval = strdup(yytext);
	return STRING;
}
.            ;
%%
