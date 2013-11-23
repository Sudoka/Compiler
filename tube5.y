%{
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

using namespace std;

#include "symbol_table.h"
#include "ast.h"
#include "type_info.h"

extern int line_num;
extern int yylex();
extern string out_filename;
 
symbolTable symbol_table;
int error_count = 0;

// Create an error function to call when the current line has an error
void yyerror(string err_string) {
  cout << "ERROR(line " << line_num << "): "
       << err_string << endl;
  error_count++;
}

// Create an alternate error function when a *different* line than being read in has an error.
void yyerror2(string err_string, int orig_line) {
  cout << "ERROR(line " << orig_line << "): "
       << err_string << endl;
  error_count++;
}

%}

%union {
  char * lexeme;
  ASTNode * ast_node;
  ASTNode_BaseChildren * ast_node_children;
}

%token ENDLINE 
%token CASSIGN_ADD CASSIGN_SUB CASSIGN_MULT CASSIGN_DIV CASSIGN_MOD 
%token COMP_EQU COMP_NEQU COMP_LESS COMP_LTE COMP_GTR COMP_GTE 
%token BOOL_AND BOOL_OR 
%token COMMAND_PRINT COMMAND_IF COMMAND_ELSE COMMAND_WHILE COMMAND_BREAK COMMAND_RANDOM
%token FUNCTION_DEFINE FUNCTION_RETURN

%token <lexeme> INT_LIT CHAR_LIT STRING_LIT TYPE META_TYPE ID

%right '=' CASSIGN_ADD CASSIGN_SUB CASSIGN_MULT CASSIGN_DIV CASSIGN_MOD
%left BOOL_OR
%left BOOL_AND
%nonassoc COMP_EQU COMP_NEQU COMP_LESS COMP_LTE COMP_GTR COMP_GTE
%left '+' '-'
%left '*' '/' '%'
%nonassoc UMINUS '!'
%left '.'

%nonassoc NOELSE
%nonassoc COMMAND_ELSE


%type <ast_node> var_declare expression declare_assign statement statement_list var_usage array_index lhs_ok command argument_list argument code_block
%type <ast_node_children> if_start while_start flow_command
%%

program:      statement_list {
                 IC_Array ic_array;                         // Array to contain the intermediate code
                 $1->CompileTubeIC(symbol_table, ic_array); // Traverse AST, filling ic_array with code

                 ofstream out_file(out_filename.c_str());   // Open the output file
                 ic_array.PrintTC(symbol_table, out_file);  // Write TC to output file!
              }
	     ;

statement_list:	 {
	           $$ = new ASTNode_Root;
                 }
       	|        statement_list statement {
                   if ($2 != NULL) $1->AddChild($2);
                   $$ = $1;
		 }
	;

statement:   var_declare ENDLINE    {  $$ = $1;  }
        |    function_declare          { ; }
        |    function_return_statement { ; }
	       |    declare_assign ENDLINE {  $$ = $1;  }
       	|    expression ENDLINE     {  $$ = $1;  }
	       |    command ENDLINE        {  $$ = $1;  }
        |    flow_command           {  $$ = $1;  }
        |    code_block             {  $$ = $1;  }
        |    ENDLINE                {  $$ = NULL;  }
	;

function_declare: function_declare_with_args | function_declare_no_args;

function_declare_with_args: FUNCTION_DEFINE TYPE ID '(' function_argument_list ')' statement {

}
;

function_declare_no_args: FUNCTION_DEFINE TYPE ID '(' ')' statement {
    
    string return_type_name = $2;
    int return_type_id = 0;

    if (return_type_name == "int") return_type_id = Type::INT;
		  else if (return_type_name == "char") return_type_id = Type::CHAR;
		  else if (return_type_name == "string") return_type_id = Type::STRING;
		  else {
		    string err_string = "unknown type '";
		    err_string += $2;
                    err_string += "'";
		    yyerror(err_string);
		  }

    symbol_table.AddEntry(return_type_id, $3);
}
;

function_return_statement: FUNCTION_RETURN expression {

}
;

var_declare:	TYPE ID {
	          if (symbol_table.Lookup($2) != 0) {
		    string err_string = "re-defining variable '";
		    err_string += $2;
                    err_string += "'";
                    yyerror(err_string);
		    exit(1);
                  }
		  string type_name = $1;
		  int type_id = 0;
		  if (type_name == "int") type_id = Type::INT;
		  else if (type_name == "char") type_id = Type::CHAR;
		  else if (type_name == "string") type_id = Type::STRING;
		  else {
		    string err_string = "unknown type '";
		    err_string += $1;
                    err_string += "'";
		    yyerror(err_string);
		  }
	          tableEntry * cur_entry = symbol_table.AddEntry(type_id, $2);

	          $$ = new ASTNode_Variable(cur_entry);
                  $$->SetLineNum(line_num);
	        }
	|     META_TYPE '(' TYPE ')' ID {
	          if (symbol_table.Lookup($5) != 0) {
		    string err_string = "re-defining variable '";
		    err_string += $5;
                    err_string += "'";
                    yyerror(err_string);
		    exit(1);
                  }
		  string type_name = $3;
		  int type_id = 0;
		  if (type_name == "int") type_id = Type::INT_ARRAY;
		  else if (type_name == "char") type_id = Type::STRING;
		  else {
		    string err_string = "unknown type 'array(";
		    err_string += $3;
                    err_string += ")'";
		    yyerror(err_string);
		  }
	          tableEntry * cur_entry = symbol_table.AddEntry(type_id, $5);

	          $$ = new ASTNode_Variable(cur_entry);
                  $$->SetLineNum(line_num);
	        }
	;

declare_assign:  var_declare '=' expression {
	           $$ = new ASTNode_Assign($1, $3);
                   $$->SetLineNum(line_num);
	         }
	;

var_usage:   ID {
	       tableEntry * cur_entry = symbol_table.Lookup($1);
               if (cur_entry == NULL) {
		 string err_string = "unknown variable '";
		 err_string += $1;
                 err_string += "'";
		 yyerror(err_string);
                 exit(1);
               }
	       $$ = new ASTNode_Variable(cur_entry);
               $$->SetLineNum(line_num);
             }
	;

array_index: var_usage '[' expression ']' {
               $$ = new ASTNode_ArrayAccess($1, $3);
               $$->SetLineNum(line_num);
             }
        ;

lhs_ok:  var_usage { $$ = $1; }
      |  array_index { $$ = $1; }
      ;

expression:  expression '+' expression { 
	       $$ = new ASTNode_Math2($1, $3, '+');
               $$->SetLineNum(line_num);
             }
	|    expression '-' expression {
	       $$ = new ASTNode_Math2($1, $3, '-');
               $$->SetLineNum(line_num);
             }
	|    expression '*' expression {
	       $$ = new ASTNode_Math2($1, $3, '*');
               $$->SetLineNum(line_num);
             }
	|    expression '/' expression {
	       $$ = new ASTNode_Math2($1, $3, '/');
               $$->SetLineNum(line_num);
             }
	|    expression '%' expression {
	       $$ = new ASTNode_Math2($1, $3, '%');
               $$->SetLineNum(line_num);
             }
	|    expression COMP_EQU expression {
               $$ = new ASTNode_Math2($1, $3, COMP_EQU);
               $$->SetLineNum(line_num);
             }
	|    expression COMP_NEQU expression {
               $$ = new ASTNode_Math2($1, $3, COMP_NEQU);
               $$->SetLineNum(line_num);
             }
	|    expression COMP_LESS expression {
               $$ = new ASTNode_Math2($1, $3, COMP_LESS);
               $$->SetLineNum(line_num);
             }
	|    expression COMP_LTE expression {
               $$ = new ASTNode_Math2($1, $3, COMP_LTE);
               $$->SetLineNum(line_num);
             }
	|    expression COMP_GTR expression {
               $$ = new ASTNode_Math2($1, $3, COMP_GTR);
               $$->SetLineNum(line_num);
             }
	|    expression COMP_GTE expression {
               $$ = new ASTNode_Math2($1, $3, COMP_GTE);
               $$->SetLineNum(line_num);
             }
	|    expression BOOL_AND expression {
               $$ = new ASTNode_Bool2($1, $3, '&');
               $$->SetLineNum(line_num);
             }
	|    expression BOOL_OR expression {
               $$ = new ASTNode_Bool2($1, $3, '|');
               $$->SetLineNum(line_num);
             }
	|    lhs_ok '=' expression {
               $$ = new ASTNode_Assign($1, $3);
               $$->SetLineNum(line_num);
             }
	|    lhs_ok CASSIGN_ADD expression {
               $$ = new ASTNode_Assign($1, new ASTNode_Math2($1, $3, '+') );
               $$->SetLineNum(line_num);
             }
	|    lhs_ok CASSIGN_SUB expression {
               $$ = new ASTNode_Assign($1, new ASTNode_Math2($1, $3, '-') );
               $$->SetLineNum(line_num);
             }
	|    lhs_ok CASSIGN_MULT expression {
               $$ = new ASTNode_Assign($1, new ASTNode_Math2($1, $3, '*') );
               $$->SetLineNum(line_num);
             }
	|    lhs_ok CASSIGN_DIV expression {
               $$ = new ASTNode_Assign($1, new ASTNode_Math2($1, $3, '/') );
               $$->SetLineNum(line_num);
             }
	|    lhs_ok CASSIGN_MOD expression {
               $$ = new ASTNode_Assign($1, new ASTNode_Math2($1, $3, '%') );
               $$->SetLineNum(line_num);
             }
	|    '-' expression %prec UMINUS {
               $$ = new ASTNode_Math1($2, '-');
               $$->SetLineNum(line_num);
             }
	|    '!' expression %prec UMINUS {
               $$ = new ASTNode_Math1($2, '!');
               $$->SetLineNum(line_num);
             }
	|    '(' expression ')' { $$ = $2; } // Ignore parens; used for order
	|    INT_LIT {
               $$ = new ASTNode_Literal(Type::INT, $1);
               $$->SetLineNum(line_num);
             }
	|    CHAR_LIT {
               $$ = new ASTNode_Literal(Type::CHAR, $1);
               $$->SetLineNum(line_num);
             }
        |    STRING_LIT {
               $$ = new ASTNode_Literal(Type::STRING, $1);
               $$->SetLineNum(line_num);
             }
	|    var_usage { $$ = $1; }
	|    array_index { $$ = $1; }
        |    expression '.' ID '(' ')' {
               $$ = new ASTNode_Method($1, $3);
               $$->SetLineNum(line_num);
             }
        |    expression '.' ID '(' argument_list ')' {
               ASTNode_Method * node = new ASTNode_Method($1, $3);
	       node->TransferChildren((ASTNode_VarChildren *) $5);
	       delete $5;
               node->TypeCheckArgs();
               $$ = node;
               $$->SetLineNum(line_num);
             }
       |   COMMAND_RANDOM '(' expression ')' {
               $$ = new ASTNode_Random($3);
               $$->SetLineNum(line_num);
            }
	;

function_argument_list: function_argument_list ',' function_argument {

   }
   | function_argument {

   }
   ;

function_argument: TYPE ID { ; }

argument_list:	argument_list ',' argument {
		  ASTNode * node = $1; // Grab the node used for arg list.
		  node->AddChild($3);    // Save this argument in the node.
		  $$ = node;
		}
	|	argument {
		  // Create a temporary AST node to hold the arg list.
		  $$ = new ASTNode_TempNode(Type::VOID);
		  $$->AddChild($1);   // Save this argument in the temp node.
                  $$->SetLineNum(line_num);
		}
	;

argument:	expression { $$ = $1; }
	;

command:   COMMAND_PRINT argument_list {
	         $$ = new ASTNode_Print(NULL);
	         $$->TransferChildren((ASTNode_VarChildren *) $2);
             $$->SetLineNum(line_num);
	         delete $2;
           }
        |  COMMAND_BREAK {
             $$ = new ASTNode_Break();
             $$->SetLineNum(line_num);
           }
	;

if_start:  COMMAND_IF '(' expression ')' {
             $$ = new ASTNode_If($3, NULL, NULL);
             $$->SetLineNum(line_num);
           }
        ;

while_start:  COMMAND_WHILE '(' expression ')' {
                $$ = new ASTNode_While($3, NULL);
                $$->SetLineNum(line_num);
              }
           ;

flow_command:  if_start statement COMMAND_ELSE statement {
                 $$->SetChild(1, $2);
                 $$->SetChild(2, $4);
                 $$ = $1;
               }
            |  if_start statement %prec NOELSE {
                 $$ = $1;
                 $$->SetChild(1, $2);
               }
            |  while_start statement {
                 $$ = $1;
                 $$->SetChild(1, $2);
               }
            ;

block_start: '{' { symbol_table.IncScope(); } ;
block_end:   '}' { symbol_table.DecScope(); } ;
code_block:  block_start statement_list block_end { $$ = $2; } ;

%%
void LexMain(int argc, char * argv[]);

int main(int argc, char * argv[])
{
  error_count = 0;
  LexMain(argc, argv);

  yyparse();

  if (error_count == 0) cout << "Parse Successful!" << endl;

  return 0;
}
