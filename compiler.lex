%{
/*
Faisal Tameesh
Kodai Ishikawa
Matt Wein
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include "ast.h"
#include "fais.tab.hh"

using namespace std;

struct arguments
{
	int argc, arg;
	char **argv;
};

int nextargument(struct arguments *args)
{
	if(YY_CURRENT_BUFFER)
		yy_delete_buffer(YY_CURRENT_BUFFER);
	if(args->argc == args->arg)
		return 1;
	yy_scan_string(args->argv[args->arg++]);

	return 0;
}

long line_count = 1;
%}
%x C_COMMENT

COMMENT #+.*
TYPE int
COMMAND print
ID _*[a-zA-Z][_a-zA-Z0-9]*
STATIC_INT [0-9]+
ADD "+"
SUB "-"
MULT "*"
DIV "/"
MOD "%"
ADDE "+="
SUBE "-="
MULTE "*="
DIVE "/="
MODE "%="

NOT "!"
AND "&&"
OR "||"
REQ "=="
RNEQ "!="
RLES "<"
RGTR ">"
RLEQ "<="
RGEQ ">="

OPEN_P "("
CLOSE_P ")"
OPEN_B "{"
CLOSE_B "}"
ASSIGNMENT "="
SEPARATOR ,
ENDLINE ;
WHITESPACE [ \t\n]
UNKNOWN .

%%

{TYPE} {return TYPE;}
{COMMAND} {return COMMAND;}
{ID} {yylval.lexeme = strdup(yytext); return ID;}
{STATIC_INT} {yylval.number = atoi(yytext); return STATIC_INT;}
{ADD} {return ADD;}
{SUB} {return SUB;}
{MULT} {return MULT;}
{DIV} {return DIV;}
{MOD} {return MOD;}
{ADDE} {return ADDE;}
{SUBE} {return SUBE;}
{MULTE} {return MULTE;}
{DIVE} {return DIVE;}
{MODE} {return MODE;}

{NOT} {return NOT;}
{AND} {return AND;}
{OR} {return OR;}
{REQ} {return REQ;}
{RNEQ} {return RNEQ;}
{RLES} {return RLES;}
{RGTR} {return RGTR;}
{RLEQ} {return RLEQ;}
{RGEQ} {return RGEQ;}

{OPEN_P} {return OPEN_P;}
{CLOSE_P} {return CLOSE_P;}
{OPEN_B} {return OPEN_B;}
{CLOSE_B} {return CLOSE_B;}
{ASSIGNMENT} {return ASSIGNMENT;}
{SEPARATOR} {return SEPARATOR;}
{ENDLINE} {return ENDLINE;}
{WHITESPACE} { if(yytext == string("\n")) line_count++; }
{COMMENT} { }
{UNKNOWN} { }

<INITIAL>{
"/*"              BEGIN(C_COMMENT);
}
<C_COMMENT>{
"*/"      BEGIN(INITIAL);
[^*\n]+   // eat comment in chunks
"*"       // eat the lone star
\n        line_count++;
}

%%
