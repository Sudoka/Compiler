%{
#include "symbol_table.h"
#include "type_info.h"
#include "ast.h"
#include "tube5-parser.tab.hh"

#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

// Two global variables (not clean, but works...)
int line_num = 1;
string out_filename = "";
%}

%option nounput

type		        int|char|string
meta_type       array
id	            _*[a-zA-Z][a-zA-Z0-9_]*
int_lit         [0-9]+
char_lit        '(.|(\\[\\'nt]))'
string_lit      \"(\\[nt"\\]|[^\\"])*\"
string_err      \"(\\.|[^\\"])*\"
string_err2     \"(\\.|[^\\"])*
comment		      #[^\n]*
end_statement   ;
eol		          \n
whitespace	    [ \t]
operator	      [+\-*/%=(),!{}[\].]

%%

"print"  { return COMMAND_PRINT; }
"if"     { return COMMAND_IF; }
"else"   { return COMMAND_ELSE; }
"while"  { return COMMAND_WHILE; }
"break"  { return COMMAND_BREAK; }
"random" { return COMMAND_RANDOM; }

{type}        { yylval.lexeme = strdup(yytext);  return TYPE; }
{meta_type}   { yylval.lexeme = strdup(yytext);  return META_TYPE; }
{id}          { yylval.lexeme = strdup(yytext);  return ID; }
{int_lit}     { yylval.lexeme = strdup(yytext);  return INT_LIT; }
{char_lit}    { yylval.lexeme = strdup(yytext);  return CHAR_LIT; }
{string_lit}  { yylval.lexeme = strdup(yytext);  return STRING_LIT; }

{string_err} {
           cout << "ERROR(line " << line_num << "): Unknown escape char in string." << endl;
           exit(1);
         }

{string_err2} {
           cout << "ERROR(line " << line_num << "): Unterminated string." << endl;
           exit(1);
         }

{operator}  { yylval.lexeme = strdup(yytext);  return (int) yytext[0]; }
{end_statement} { return ENDLINE; }

"+=" { return CASSIGN_ADD;  }
"-=" { return CASSIGN_SUB;  }
"*=" { return CASSIGN_MULT; }
"/=" { return CASSIGN_DIV;  }
"%=" { return CASSIGN_MOD;  }

"==" { return COMP_EQU;  }
"!=" { return COMP_NEQU; }
"<"  { return COMP_LESS; }
"<=" { return COMP_LTE;  }
">"  { return COMP_GTR;  }
">=" { return COMP_GTE;  }

"&&" { return BOOL_AND; }
"||" { return BOOL_OR;  }

{comment} { ; }
{whitespace} { ; }
{eol}  { line_num++; }

.      { cout << "ERROR(line " << line_num << "): Unknown Token '" << yytext << "'." << endl; exit(1); }

%%

void LexMain(int argc, char * argv[])
{
  FILE * file = NULL;
  bool input_found = false;

  // Loop through all of the command-line arguments.
  for (int arg_id = 1; arg_id < argc; arg_id++) {
    string cur_arg(argv[arg_id]);

    if (cur_arg == "-h") {
      cout << "Tubular Compiler v. 0.4 (Project 4)"  << endl
           << "Format: " << argv[0] << "[flags] [filename]" << endl
           << endl
           << "Available Flags:" << endl
           << "  -h  :  Help (this information)" << endl
        ;
      exit(0);
    }

    // PROCESS OTHER ARGUMENTS HERE IF YOU ADD THEM

    // If the next argument begins with a dash, assume it's an unknown flag...
    if (cur_arg[0] == '-') {
      cerr << "ERROR: Unknown command-line flag: " << cur_arg << endl;
      exit(1);
    }

    // Assume the current argument is a filename (first input, then output)
    if (!input_found) {
      file = fopen(argv[arg_id], "r");
      if (!file) {
        cerr << "Error opening " << cur_arg << endl;
        exit(1);
      }
      yyin = file;
      input_found = true;
      continue;
    } else if (out_filename == "") {
      out_filename = cur_arg;
    }

    // Both files already loaded!
    else {
      cout << "ERROR: Unknown argument '" << cur_arg << "'" << endl;
      exit(1);
    }
  }

  // Make sure we've loaded input and output filenames before we finish...
  if (input_found == false || out_filename == "") {
    cerr << "Format: " << argv[0] << "[flags] [input filename] [output filename]" << endl;
    cerr << "Type '" << argv[0] << " -h' for help." << endl;
    exit(1);
  }
 
  return;
}

