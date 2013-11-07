%{
/*
  - Faisal Tameesh
  - Kodai Ishikawa
  - Matt Wein
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>	
#include <string>
#include <sstream>
#include <map>
#include <list>
#include <stdio.h>
#include <cstdlib>
#include "ast.h"

using namespace std;

//For lex's input file.
extern FILE* yyin;
extern long line_count;
extern int yylex();

int nvar = 0;
long boolNumber = 1;
int scopeNumber = 1;

//vector<map<string, int> > scope_map; 

//map<string, ASTNode_Base *> id_map;
map<string, int> id_map;

void yyerror(char * err_string){ 
    cerr << "ERROR(line " << line_count << "): " << err_string << endl;
    exit(1);
}

void yyerror(char * err_string, string lexeme){ 
    cerr << "ERROR(line " << line_count <<"): "<< err_string << " : " << lexeme << endl;
    exit(1);
}

%}

%union {
char* lexeme;
int number;
ASTNode_Base * node;
}

%left ASSIGNMENT
%left OR
%left AND
%nonassoc REQ RNEQ RLES RGTR RLEQ RGEQ
%left ADD SUB
%left MULT DIV MOD
%nonassoc UMINUS NOT

//testing
%token <lexeme> TYPE
%token <lexeme> COMMAND 
%token <lexeme> ID 
%token <number> STATIC_INT
%token ASSIGNMENT
%token OPEN_P
%token CLOSE_P
%token OPEN_B
%token CLOSE_B
%token SEPARATOR 
%token ENDLINE
%token ADD
%token SUB
%token MULT
%token DIV
%token MOD
%token ADDE
%token SUBE
%token MULTE
%token DIVE
%token MODE

%token NOT
%token AND
%token OR
%token REQ
%token RNEQ
%token RLES
%token RGTR
%token RLEQ
%token RGEQ

%type <node> statement expr compound mult_expr clause  

%%

program:  program statement { if($2!=NULL){$2->WriteIC(nvar);} }
	  | program block_start program block_end {  }
	  | ;

statement: expr ENDLINE {$$ = $1;}
	  | TYPE ID ENDLINE 
	  {	
	    stringstream ss;
	    ss << scopeNumber; 
	    /*if (id_map.find(string($2)+string(ss.str())) != id_map.end()) {
	    cerr << "ERROR(line " << line_count << "): re-defining variable '" << $2 << "'" << endl;
	    exit(1);}*/
	    string temp;
	    for(int i=scopeNumber-1; i>0; i--)
	    {
	      stringstream ss;
	      ss << i;
	      temp = string($2)+string(ss.str());
	      if(id_map.find(temp) != id_map.end()) {
	      cerr << "ERROR(line " << line_count << "): re-defining variable '" << $2 << "'" << endl;
	      exit(1);}
	    }
	    id_map[string($2)+string(ss.str())]= nvar++; 
	    $$ = new ASTNode_Var(id_map[string($2)+string(ss.str())]);
	  }
	  | compound ENDLINE
	  | COMMAND expr ENDLINE {
	      $$ = new ASTNode_Print($2);
	      }
	  | COMMAND mult_expr SEPARATOR expr ENDLINE { 
	      (new ASTNode_Print($4))->WriteIC(nvar);
	      $$ = NULL;
	      }
	  | clause expr ENDLINE 
	  {
	    $$ = $2;
	  };
	
	  
block_start: OPEN_B {scopeNumber++;};

block_end: CLOSE_B {scopeNumber--;};
	  
clause:   expr SEPARATOR
	  {
	    $$ = $1;
	  }
	  | clause expr SEPARATOR
	  {
	    $$ = $2;
	  };

mult_expr:  mult_expr SEPARATOR expr { (new ASTNode_Print($3))->WriteICMulti(nvar);/*(new ASTNode_Print($3))->WriteICMulti(nvar); (new ASTNode_Print($1))->WriteICMulti(nvar);*/ }
	  | expr { (new ASTNode_Print($1))->WriteICMulti(nvar); };
    
    
expr:	   expr ADD expr { $$ = new ASTNode_Add($1, $3); }
	   | expr SUB expr { $$ = new ASTNode_Sub($1, $3); }
	   | expr MULT expr { $$ = new ASTNode_Mult($1, $3); }
	   | expr DIV expr { $$ = new ASTNode_Div($1, $3); }
	   | expr MOD expr { $$ = new ASTNode_Mod($1, $3); }
	   | expr REQ expr { $$ = new ASTNode_Req($1, $3); }
	   | expr RNEQ expr { $$ = new ASTNode_Rneq($1, $3); }
	   | expr RLES expr { $$ = new ASTNode_Rles($1, $3); }
	   | expr RGTR expr { $$ = new ASTNode_Rgtr($1, $3); }
	   | expr RLEQ expr { $$ = new ASTNode_Rleq($1, $3); }
	   | expr RGEQ expr { $$ = new ASTNode_Rgeq($1, $3); }
	   | expr AND expr { $$ = new ASTNode_And($1, $3); }
	   | expr OR expr { $$ = new ASTNode_Or($1, $3); }
	   | NOT expr { $$ = new ASTNode_Not($2); }
	   | OPEN_P expr CLOSE_P { $$ = $2; }
	   | OPEN_P compound CLOSE_P { $$ = $2; }
	  // | OPEN_P imexpr CLOSE_P { $$ = $2; }
	   | SUB expr %prec UMINUS { $$ = new ASTNode_UMinus($2); }
	   | ID { 
	     	stringstream ss;
	    ss << scopeNumber; if (id_map.find(string($1)+string(ss.str())) == id_map.end()) {
		   cerr << "ERROR(line " << line_count << "): unknown variable '" << $1 << "'" << endl;
		   exit(1);
		
		$$ = new ASTNode_Var(id_map[string($1)+string(ss.str())]); }
	   | STATIC_INT { $$ = new ASTNode_Number($1);}
	   | ID ASSIGNMENT expr { stringstream ss;
	    ss << scopeNumber; if (id_map.find(string($1)+string(ss.str())) == id_map.end()) {
		cerr << "ERROR(line " << line_count << "): unknown variable '" << $1 << "'" << endl;
		exit(1);}
	    ASTNode_Var *lhs = new ASTNode_Var(id_map[string($1)+string(ss.str())]);
	    $$ = new ASTNode_Assign(lhs, $3);  }
	   |  TYPE ID ASSIGNMENT expr { 
		stringstream ss;
		ss << scopeNumber; 
		/*if (id_map.find(string($2)+string(ss.str())) != id_map.end()) {
		cerr << "ERROR(line " << line_count << "): re-defining variable '" << $2 << "'" << endl;
		exit(1);}*/
		string temp;
		for(int i=scopeNumber-1; i>0; i--)
		{
		  stringstream ss;
		  ss << i;
		  temp = string($2)+string(ss.str());
		  if(id_map.find(temp) != id_map.end()) {
		  cerr << "ERROR(line " << line_count << "): re-defining variable '" << $2 << "'" << endl;
		  exit(1);}
		}
	    id_map[string($2)+string(ss.str())]= nvar++;
	    ASTNode_Var *lhs = new ASTNode_Var(id_map[string($2)+string(ss.str())]);
	    $$ = new ASTNode_Assign(lhs, $4); };
	   
compound:  ID ADDE expr { stringstream ss;
	    ss << scopeNumber; if (id_map.find(string($1)+string(ss.str())) == id_map.end()) { 	
		   cerr << "ERROR(line " << line_count << "): unknown variable '" << $1 << "'" << endl;
		   exit(1); } ASTNode_Var *lhs = new ASTNode_Var(id_map[string($1)+string(ss.str())]); $$ = new ASTNode_Assign(lhs, new ASTNode_Add(lhs, $3)); }
	   | ID SUBE expr { stringstream ss;
	    ss << scopeNumber; if (id_map.find(string($1)+string(ss.str())) == id_map.end()) { 	
		   cerr << "ERROR(line " << line_count << "): unknown variable '" << $1 << "'" << endl;
		   exit(1); } ASTNode_Var *lhs = new ASTNode_Var(id_map[string($1)+string(ss.str())]); $$ = new ASTNode_Assign(lhs, new ASTNode_Sub(lhs, $3)); }
	   | ID MULTE expr { stringstream ss;
	    ss << scopeNumber; if (id_map.find(string($1)+string(ss.str())) == id_map.end()) { 	
		   cerr << "ERROR(line " << line_count << "): unknown variable '" << $1 << "'" << endl;
		   exit(1); } ASTNode_Var *lhs = new ASTNode_Var(id_map[string($1)+string(ss.str())]); $$ = new ASTNode_Assign(lhs, new ASTNode_Mult(lhs, $3)); }
	   | ID DIVE expr { stringstream ss;
	    ss << scopeNumber; if (id_map.find(string($1)+string(ss.str())) == id_map.end()) { 	
		   cerr << "ERROR(line " << line_count << "): unknown variable '" << $1 << "'" << endl;
		   exit(1); } ASTNode_Var *lhs = new ASTNode_Var(id_map[string($1)+string(ss.str())]); $$ = new ASTNode_Assign(lhs, new ASTNode_Div(lhs, $3));}
	   | ID MODE expr { stringstream ss;
	    ss << scopeNumber; if (id_map.find(string($1)+string(ss.str())) == id_map.end()) { 	
		   cerr << "ERROR(line " << line_count << "): unknown variable '" << $1 << "'" << endl;
		   exit(1); } ASTNode_Var *lhs = new ASTNode_Var(id_map[string($1)+string(ss.str())]); $$ = new ASTNode_Assign(lhs, new ASTNode_Mod(lhs, $3));};

%% 

int main(int argc, char *argv[]) 
{
  ofstream out(argv[2]);
  if(argc==3)
  {
      yyin = fopen(argv[1], "r");
      if(!yyin)
      {
	  fprintf(stderr, "can't read file %s\n", argv[1]);
	  return 1;
      }
  }

  streambuf *coutbuf = cout.rdbuf();
  cout.rdbuf(out.rdbuf());
  cout<<"main: "<<endl;
  yyparse();
  cerr << "Parse successful!" << endl;
  cout.rdbuf(coutbuf);
  
  return 0;
}
