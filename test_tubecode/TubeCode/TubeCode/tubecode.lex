%{

#include "inst.h"
#include "hardware.h"
#include "tubecode.tab.hh"

#include <iostream>
#include <cstdlib>
#include <stdio.h>
using namespace std;
int line_num = 1;
cHardware * main_hardware;
%}

int		[0-9]+
comment		#.*
eol		\n
whitespace	[ \t]

%%

val_copy { return INST_VAL_COPY; }
add { return INST_ADD; }
sub { return INST_SUB; }
mult { return INST_MULT; }
div { return INST_DIV; }
mod { return INST_MOD; }
test_less { return INST_TEST_LESS; }
test_gtr { return INST_TEST_GTR; }
test_equ { return INST_TEST_EQU; }
test_nequ { return INST_TEST_NEQU; }
test_gte { return INST_TEST_GTE; }
test_lte { return INST_TEST_LTE; }
jump { return INST_JUMP; }
jump_if_0 { return INST_JUMP_IF_0; }
jump_if_n0 { return INST_JUMP_IF_N0; }
jmp_if_0 { return INST_JUMP_IF_0; }
jmp_if_n0 { return INST_JUMP_IF_N0; }
nop { return INST_NOP; }
random { return INST_RANDOM; }
out_int { return INST_OUT_INT; }
out_float { return INST_OUT_FLOAT; }
out_char { return INST_OUT_CHAR; }

load { return INST_LOAD; }
store { return INST_STORE; }
mem_copy { return INST_MEM_COPY; }

"ar_get_idx"|"ar_set_idx"|"ar_get_siz"|"ar_set_siz"|"ar_get_size"|"ar_set_size"|((a|s){int}) { cerr << "Error(line " << line_num << "): instruction '" << yytext << "' valid only in TubeIC, not TubeCode assembly." << endl; exit(1); }


-?{int} { yylval.int_val = atoi(yytext); return ARG_INT; }
reg[A-H] { yylval.int_val = yytext[3]-'A'; return ARG_REG; }
reg[I-Z] { cerr << "Error(line " << line_num << "): " << yytext << "not a legal register; only 8 registers available." << endl; exit(1); }
IP { return ARG_IP; }
'.' { yylval.int_val = (int) yytext[1]; return ARG_CHAR; }
'\\n' { yylval.int_val = (int) '\n'; return ARG_CHAR; }
'\\t' { yylval.int_val = (int) '\t'; return ARG_CHAR; }
'\\'' { yylval.int_val = (int) '\''; return ARG_CHAR; }
'\\\\' { yylval.int_val = (int) '\\'; return ARG_CHAR; }
'\\\"' { yylval.int_val = (int) '\"'; return ARG_CHAR; }
[a-zA-Z][a-zA-Z0-9_]* { yylval.lexeme = strdup(yytext); return ARG_LABEL; }

[:] { return yytext[0]; }

{eol}  { line_num++; return ENDLINE; }
{comment} { ; }
{whitespace} { ; }
.      { cout << "ERROR(line " << line_num << "): Unknown Token '" << yytext << "'." << endl; exit(1); }

%%

void LexMain(int argc, char * argv[])
{
  int arg_id = 0;
  while (true) {
    arg_id++;
    if (arg_id >= argc) {
      cerr << "Format: " << argv[0] << "[flags] [filename]" << endl;
      cerr << "Type '" << argv[0] << " -h' for help." << endl;
      exit(1);
    }

    string cur_arg(argv[arg_id]);
    if (cur_arg == "-h") {
      cout << "Tube Code Assembly v. 0.1"  << endl
           << "Format: " << argv[0] << "[flags] [filename]" << endl
           << endl
           << "Flags:" << endl
           << "  -h  :  Help (this information)" << endl
           << "  -i  :  List Instructions" << endl
           << "  -t  [timeout] :  Set a max number of instructions executed before halting" << endl
           << "  -v  :  Verbose.  Print information about each line executed to trace.dat" << endl
        ;
      exit(0);
    }

    if (cur_arg == "-i") {
      cout << "Available Instructions:" << endl;
      cout << "  " << cInst_VAL_COPY::GetDesc() << endl;
      cout << "  " << cInst_ADD::GetDesc() << endl;
      cout << "  " << cInst_SUB::GetDesc() << endl;
      cout << "  " << cInst_MULT::GetDesc() << endl;
      cout << "  " << cInst_DIV::GetDesc() << endl;
      cout << "  " << cInst_MOD::GetDesc() << endl;
      cout << "  " << cInst_TEST_LESS::GetDesc() << endl;
      cout << "  " << cInst_TEST_GTR::GetDesc() << endl;
      cout << "  " << cInst_TEST_EQU::GetDesc() << endl;
      cout << "  " << cInst_TEST_NEQU::GetDesc() << endl;
      cout << "  " << cInst_TEST_GTE::GetDesc() << endl;
      cout << "  " << cInst_TEST_LTE::GetDesc() << endl;
      cout << "  " << cInst_JUMP::GetDesc() << endl;
      cout << "  " << cInst_JUMP_IF_0::GetDesc() << endl;
      cout << "  " << cInst_JUMP_IF_N0::GetDesc() << endl;
      cout << "  " << cInst_NOP::GetDesc() << endl;
      cout << "  " << cInst_RANDOM::GetDesc() << endl;
      cout << "  " << cInst_OUT_INT::GetDesc() << endl;
      cout << "  " << cInst_OUT_FLOAT::GetDesc() << endl;
      cout << "  " << cInst_OUT_CHAR::GetDesc() << endl;
      cout << "  " << cInst_LOAD::GetDesc() << endl;
      cout << "  " << cInst_STORE::GetDesc() << endl;
      cout << "  " << cInst_MEM_COPY::GetDesc() << endl;
      exit(0);
    }

    if (cur_arg == "-t") {
      int timeout;
      arg_id++;
      stringstream(argv[arg_id]) >> timeout;
      main_hardware->SetTimeout(timeout);
      continue;
    }

    if (cur_arg == "-v") {
      main_hardware->SetVerbose();
      continue;
    }

    // The only thing left to do is assume the current argument is the filename.
    FILE *file = fopen(argv[arg_id], "r");
    if (!file) {
      cerr << "Error opening " << cur_arg << endl;
      exit(2);
    }
    yyin = file;
    return;
  }

  return;
}
