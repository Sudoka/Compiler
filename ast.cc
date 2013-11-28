#include "ast.h"
#include "tube5-parser.tab.hh"

extern void yyerror(string err_string);
extern void yyerror2(string err_string, int orig_line);

void CompileFunctions(symbolTable & table, IC_Array & ica);

////////////////////////////
//  ASTNode_VarChildren

void ASTNode_VarChildren::TransferChildren(ASTNode_VarChildren * in_node)
{
  for (int i = 0; i < in_node->GetNumChildren(); i++) {
    AddChild(in_node->GetChild(i));
  }
  in_node->children.resize(0);
}


/////////////////////
//  ASTNode_Root

tableEntry * ASTNode_Root::CompileTubeIC(symbolTable & table, IC_Array & ica)
{
  // Compile the code for each sub-tree below a root.
  for (int i = 0; i < (int) children.size(); i++) {
    tableEntry * cur_entry = children[i]->CompileTubeIC(table, ica);
    if (cur_entry != NULL && cur_entry->GetTemp() == true) {
      table.RemoveEntry( cur_entry );
    }
  }

  return NULL;
}

void ASTNode_BaseChildren::CompileFunctionDefinitionsToIC(symbolTable & table, IC_Array & ica)
{
  string function_label = "define_functions_end";
  
  ica.Add(Instr::NOP);
  ica.Add(Instr::NOP);
  ica.Add(Instr::NOP, -1, -1, -1, "============ FUNCTIONS ============");
  ica.Add(Instr::JUMP, function_label, -1, -1, "Skip over function defs during normal execution");
  ica.Add(Instr::NOP);

  vector<tableEntry *> functions = table.getFunctions();
		
  for (int i = 0; i < functions.size(); i++)
		{
     ASTNode_FunctionDefinition * node = functions[i]->GetASTNode_FunctionDefinition();
					node->CompileTubeIC(table, ica);
		}

		ica.AddLabel(function_label);
}

/////////////////////
// ASTNode_FunctionDefinition

ASTNode_FunctionDefinition::ASTNode_FunctionDefinition(ASTNode *in, tableEntry * in_function)
  : ASTNode_BaseChildren(Type::VOID), name(in_function->GetName())
{
  children.push_back(in);
}

tableEntry * ASTNode_FunctionDefinition::CompileTubeIC(symbolTable & table, IC_Array & ica)
{
  tableEntry * out_var = table.AddTempEntry(Type::STRING);
  ica.Add(Instr::NOP, -1, -1, -1, "FUNCTION: " + name);
  ica.AddLabel("function_" + name);
  children[0]->CompileTubeIC(table,ica);
  ica.Add(Instr::POP, out_var->GetVarID());
  ica.Add(Instr::JUMP, out_var->GetVarID());
  return NULL;
}

/////////////////////
// ASTNode_FunctionReturn

ASTNode_FunctionReturn::ASTNode_FunctionReturn(ASTNode *in, tableEntry * current_function)
  : ASTNode_BaseChildren(Type::VOID), curr_fn(current_function)
{
  if (in->GetType() != current_function->GetType()) {
    string err_message = "incorrect return type for function '";
    err_message += curr_fn->GetName();
    err_message += "'.  Expected: '";
    err_message += Type::AsString(current_function->GetType());
    err_message += "', but found '";
    err_message += Type::AsString(in->GetType());
    err_message += "')";
    yyerror(err_message);
    exit(1);
  }
  children.push_back(in);
}

tableEntry * ASTNode_FunctionReturn::CompileTubeIC(symbolTable & table, IC_Array & ica)
{
  if (curr_fn != NULL)
  {
  		tableEntry * curr = children[0]->CompileTubeIC(table,ica);
  		ica.Add(Instr::VAL_COPY, curr->GetVarID(), curr_fn->GetVarID());
  }
 	return NULL;
}

/////////////////////
// ASTNode_FunctionInvocation

ASTNode_FunctionInvocation::ASTNode_FunctionInvocation(tableEntry * in_function)
  : ASTNode_VarChildren(in_function->GetType()), in_func(in_function)
{
}

tableEntry * ASTNode_FunctionInvocation::CompileTubeIC(symbolTable & table, IC_Array & ica)
{
  vector<tableEntry *> args = in_func->GetArgs();

  for (int i = 0; i < children.size(); i++)
  {
     tableEntry * in_var = children[0]->CompileTubeIC(table, ica);
     tableEntry * out_var = args[i];
     
     ica.Add(Instr::VAL_COPY, in_var->GetVarID(), out_var->GetVarID());
  }

  string function_return_label = table.NextLabelID("function_return_");
  string function_label = "function_" + in_func->GetName();

  tableEntry * out_var = table.AddTempEntry(type);

  ica.Add(Instr::PUSH, function_return_label);
  ica.Add(Instr::JUMP, function_label);
  ica.AddLabel(function_return_label);
  ica.Add(Instr::VAL_COPY, in_func->GetVarID(), out_var->GetVarID());

  return out_var;
}

void ASTNode_FunctionInvocation::TypeCheckArgs()
{
  vector<tableEntry *> args = in_func->GetArgs();

  if (args.size() != children.size()) {
    string err_message = "Incorrect number of arguments provided for function '";
    err_message += in_func->GetName();
    err_message += "'";
    yyerror(err_message);
    exit(1);
  }

  for (int i = 0; i < children.size(); i++)
  {
     int expected_type = args[i]->GetType();
     int arg_type = children[i]->GetType();

					if (arg_type != expected_type) {
							string err_message = "invalid type for param '";
							err_message += args[i]->GetName();
       err_message += "', (Expected '";
							err_message += Type::AsString(expected_type);
							err_message += "', but found '";
       err_message += Type::AsString(arg_type);
       err_message += "')";
							yyerror(err_message);
							exit(1);
					}
  }
}

/////////////////////////
//  ASTNode_Variable

tableEntry * ASTNode_Variable::CompileTubeIC(symbolTable & table, IC_Array & ica)
{
  return var_entry;
}


////////////////////////
//  ASTNode_Literal

ASTNode_Literal::ASTNode_Literal(int in_type, string in_lex)
  : ASTNode(in_type), lexeme(in_lex)
{
}  

tableEntry * ASTNode_Literal::CompileTubeIC(symbolTable & table, IC_Array & ica)
{
  tableEntry * out_var = table.AddTempEntry(type);
  if (type == Type::INT || type == Type::CHAR) {
    ica.Add(Instr::VAL_COPY, lexeme, out_var->GetVarID());
  } else if (type == Type::STRING) {
    // Drop the beginning and ending quotes and process escape chars.
    string str_value = "";
    for (int i = 1; i < (int) lexeme.size() - 1; i++) {
      if (lexeme[i] == '\\') {
        switch (lexeme[++i]) {
        case '\\': str_value += '\\'; break;
        case '"':  str_value += '"';  break;
        case 't':  str_value += '\t'; break;
        case 'n':  str_value += '\n'; break;
        };
      } else {
        str_value += lexeme[i];
      }
    }        

    stringstream size_str;
    size_str << str_value.size();
    ica.AddArray(Instr::AR_SET_SIZ, out_var->GetVarID(), size_str.str());
    for (int i = 0; i < (int) str_value.size(); i++) {
      stringstream set_val;
      switch (str_value[i]) {
      case '\\': set_val << "'\\\\'"; break;
      case '\t': set_val << "'\\t'"; break;
      case '\n': set_val << "'\\n'"; break;
      case '\'': set_val << "'\\''"; break;
      default: set_val << "'" << str_value[i] << "'";
      };

      stringstream idx_str;
      idx_str << i;
      ica.AddArray(Instr::AR_SET_IDX, out_var->GetVarID(), idx_str.str(), set_val.str());
    }
  } else {
    cerr << "INTERNAL ERROR: Unknown type!" << endl;
  }

  return out_var;
}


//////////////////////
// ASTNode_Assign

ASTNode_Assign::ASTNode_Assign(ASTNode * lhs, ASTNode * rhs)
  : ASTNode_BaseChildren(lhs->GetType())
{ 
  if (lhs->GetType() != rhs->GetType()) {
    string err_message = "types do not match for assignment (lhs='";
    err_message += Type::AsString(lhs->GetType());
    err_message += "', rhs='";
    err_message += Type::AsString(rhs->GetType());
    err_message += "')";
    yyerror(err_message);
    exit(1);
  }
  children.push_back(lhs);
  children.push_back(rhs);
}

tableEntry * ASTNode_Assign::CompileTubeIC(symbolTable & table,
						IC_Array & ica)
{
  tableEntry * lhs_var = children[0]->CompileTubeIC(table, ica);
  tableEntry * rhs_var = children[1]->CompileTubeIC(table, ica);

  if (type == Type::INT || type == Type::CHAR) {
    // Determine if the lhs is part of an array
    if (lhs_var->GetArrayID() == -1) {    // NOT an array on the LHS!
      ica.Add(Instr::VAL_COPY, rhs_var->GetVarID(), lhs_var->GetVarID());
    } else {                              // An array on the LHS!
      ica.AddArray(Instr::AR_SET_IDX, lhs_var->GetArrayID(), lhs_var->GetIndexID(), rhs_var->GetVarID());
    }
  } else if (type == Type::INT_ARRAY || type == Type::STRING) {
    int size_id = table.GetTempVarID();
    int index_id = table.GetTempVarID();
    int entry_id = table.GetTempVarID();        
    string start_label = table.NextLabelID("copy_array_start_");
    string end_label = table.NextLabelID("copy_array_end_");
    
    ica.Add(Instr::VAL_COPY, "0", index_id, -1, "Init loop variable for copying array.");
    ica.AddArray(Instr::AR_GET_SIZ, rhs_var->GetVarID(), size_id, -1, "Save size of RHS array into variable.");
    ica.AddArray(Instr::AR_SET_SIZ, lhs_var->GetVarID(), size_id, -1, "Make LHS same size as RHS.");
    ica.AddLabel(start_label);
    ica.Add(Instr::TEST_EQU, index_id, size_id, entry_id, "Test if we are finished yet...");
    ica.Add(Instr::JUMP_IF_N0, entry_id, end_label, -1, " ...and jump if we are.");
    ica.AddArray(Instr::AR_GET_IDX, rhs_var->GetVarID(), index_id, entry_id, "Collect the value at next index.");
    ica.AddArray(Instr::AR_SET_IDX, lhs_var->GetVarID(), index_id, entry_id, "Write this entry to the LHS!");
    ica.Add(Instr::ADD, index_id, "1", index_id, "Increment to the next index.");
    ica.Add(Instr::JUMP, start_label, -1, -1, " ...and jump if not.");
    ica.AddLabel(end_label);
        
    table.FreeTempVarID(size_id);
    table.FreeTempVarID(index_id);
    table.FreeTempVarID(entry_id);
  } else {
    cerr << "Internal Compiler ERROR: Unknown type in Assign!" << endl;
    exit(1);
  }

  if (rhs_var->GetTemp() == true) table.RemoveEntry( rhs_var );

  return lhs_var;
}


/////////////////////
// ASTNode_Math1

ASTNode_Math1::ASTNode_Math1(ASTNode * in_child, int op)
  : ASTNode_BaseChildren(ChooseType(in_child)), math_op(op)
{
  if (in_child->GetType() != Type::INT) {
    string err_message = "cannot use type '";
    err_message += Type::AsString(in_child->GetType());
    err_message += "' in mathematical expressions";
    yyerror(err_message);
    exit(1);
  }
  children.push_back(in_child);
}

int ASTNode_Math1::ChooseType(ASTNode * child)
{
  // For the moment, lets always convert to a number.
  return Type::INT;
}

tableEntry * ASTNode_Math1::CompileTubeIC(symbolTable & table, IC_Array & ica)
{
  tableEntry * in_var = children[0]->CompileTubeIC(table, ica);
  tableEntry * out_var = table.AddTempEntry(type);

  switch (math_op) {
  case '-':
    ica.Add(Instr::MULT, in_var->GetVarID(), "-1", out_var->GetVarID());
    break;
  case '!':
    ica.Add(Instr::TEST_EQU, in_var->GetVarID(), "0", out_var->GetVarID());
    break;
  default:
    cerr << "Internal compiler error: unknown Math1 operation '" << math_op << "'." << endl;
    exit(1);
  };

  if (in_var->GetTemp() == true) table.RemoveEntry( in_var );

  return out_var;
}


/////////////////////
// ASTNode_Math2

ASTNode_Math2::ASTNode_Math2(ASTNode * in1, ASTNode * in2, int op)
  : ASTNode_BaseChildren(ChooseType(in1, in2)), math_op(op)
{
  bool rel_op = (op==COMP_EQU) || (op==COMP_NEQU) || (op==COMP_LESS) || (op==COMP_LTE) ||
    (op==COMP_GTR) || (op==COMP_GTE);

  ASTNode * in_test = (in1->GetType() != Type::INT) ? in1 : in2;
  if (in_test->GetType() != Type::INT) {
    if (!rel_op || in_test->GetType() != Type::CHAR) {
      string err_message = "cannot use type '";
      err_message += Type::AsString(in_test->GetType());
      err_message += "' in mathematical expressions";
      yyerror(err_message);
      exit(1);
    } else if (rel_op && (in1->GetType() != Type::CHAR || in2->GetType() != Type::CHAR)) {
      string err_message = "types do not match for relationship operator (lhs='";
      err_message += Type::AsString(in1->GetType());
      err_message += "', rhs='";
      err_message += Type::AsString(in2->GetType());
      err_message += "')";
      yyerror(err_message);
      exit(1);
    }
  }

  children.push_back(in1);
  children.push_back(in2);
}


int ASTNode_Math2::ChooseType(ASTNode * child1, ASTNode * child2)
{
  // At the moment, both sides need to be of the same type, so return the type of either child.
  // @CAO Always return INT, regardless of inputs...
  return Type::INT; // child1->GetType();
}


tableEntry * ASTNode_Math2::CompileTubeIC(symbolTable & table, IC_Array & ica)
{
  tableEntry * in_var1 = children[0]->CompileTubeIC(table, ica);
  tableEntry * in_var2 = children[1]->CompileTubeIC(table, ica);
  tableEntry * out_var = table.AddTempEntry(type);

  int i1 = in_var1->GetVarID();
  int i2 = in_var2->GetVarID();
  int o3 = out_var->GetVarID();

  // Determine the correct operation...  
  if (math_op == '+') { ica.Add(Instr::ADD, i1, i2, o3); }
  else if (math_op == '-') { ica.Add(Instr::SUB,  i1, i2, o3); }
  else if (math_op == '*') { ica.Add(Instr::MULT, i1, i2, o3); }
  else if (math_op == '/') { ica.Add(Instr::DIV,  i1, i2, o3); }
  else if (math_op == '%') { ica.Add(Instr::MOD,  i1, i2, o3); }
  else if (math_op == COMP_EQU)  { ica.Add(Instr::TEST_EQU,  i1, i2, o3); }
  else if (math_op == COMP_NEQU) { ica.Add(Instr::TEST_NEQU, i1, i2, o3); }
  else if (math_op == COMP_GTR)  { ica.Add(Instr::TEST_GTR,  i1, i2, o3); }
  else if (math_op == COMP_GTE)  { ica.Add(Instr::TEST_GTE,  i1, i2, o3); }
  else if (math_op == COMP_LESS) { ica.Add(Instr::TEST_LESS, i1, i2, o3); }
  else if (math_op == COMP_LTE)  { ica.Add(Instr::TEST_LTE,  i1, i2, o3); }
  else {
    cerr << "INTERNAL ERROR: Unknown Math2 type '" << math_op << "'" << endl;
  }

  // Cleanup symbol table.
  if (in_var1->GetTemp() == true) table.RemoveEntry( in_var1 );
  if (in_var2->GetTemp() == true) table.RemoveEntry( in_var2 );

  return out_var;
}


/////////////////////
// ASTNode_Bool2

ASTNode_Bool2::ASTNode_Bool2(ASTNode * in1, ASTNode * in2, int op)
  : ASTNode_BaseChildren(ChooseType(in1, in2)), bool_op(op)
{
  ASTNode * in_test = (in1->GetType() != Type::INT) ? in1 : in2;
  if (in_test->GetType() != Type::INT) {
    string err_message = "cannot use type '";
    err_message += Type::AsString(in_test->GetType());
    err_message += "' in mathematical expressions";
    yyerror(err_message);
    exit(1);
  }

  children.push_back(in1);
  children.push_back(in2);
}


int ASTNode_Bool2::ChooseType(ASTNode * child1, ASTNode * child2)
{
  return Type::INT;
}


tableEntry * ASTNode_Bool2::CompileTubeIC(symbolTable & table, IC_Array & ica)
{
  tableEntry * in_var1 = children[0]->CompileTubeIC(table, ica);
  tableEntry * out_var = table.AddTempEntry(type);
  string end_label = table.NextLabelID("end_bool_");

  // Convert the first answer to a 0 or 1 and put it in out_var.
  ica.Add(Instr::TEST_NEQU, in_var1->GetVarID(), "0", out_var->GetVarID());

  // Determine the correct operation for short-circuiting...  
  if (bool_op == '&') {
    ica.Add(Instr::JUMP_IF_0, out_var->GetVarID(), end_label, -1, "AND!");
  }
  else if (bool_op == '|') {
    ica.Add(Instr::JUMP_IF_N0, out_var->GetVarID(), end_label, -1, "OR!");
  }
  else { cerr << "INTERNAL ERROR: Unknown Bool2 type '" << bool_op << "'" << endl; }

  // The output code should only get here if the first part didn't short-circuit...
  tableEntry * in_var2 = children[1]->CompileTubeIC(table, ica);

  // Convert the second answer to a 0 or 1 and put it in out_var.
  ica.Add(Instr::TEST_NEQU, in_var2->GetVarID(), "0", out_var->GetVarID());

  // Leave the output label to jump to.
  ica.AddLabel(end_label);

  // Cleanup symbol table.
  if (in_var1->GetTemp() == true) table.RemoveEntry( in_var1 );
  if (in_var2->GetTemp() == true) table.RemoveEntry( in_var2 );

  return out_var;
}


///////////////////////////
// ASTNode_ArrayAccess

ASTNode_ArrayAccess::ASTNode_ArrayAccess(ASTNode * in1, ASTNode * in2)
  : ASTNode_BaseChildren(Type::InternalType(in1->GetType()))
{
  if (Type::IsArray(in1->GetType()) == false) {
    string err_message = "Trying to index into non-array type '";
    err_message += Type::AsString(in1->GetType());
    err_message += "'.";
    yyerror(err_message);
    exit(1);
  }

  if (in2->GetType() != Type::INT) {
    yyerror ("array indicies must be of type int");
    exit(1);
  }

  children.push_back(in1);
  children.push_back(in2);
}


tableEntry * ASTNode_ArrayAccess::CompileTubeIC(symbolTable & table, IC_Array & ica)
{
  tableEntry * in_var0 = children[0]->CompileTubeIC(table, ica);
  tableEntry * in_var1 = children[1]->CompileTubeIC(table, ica);
  tableEntry * out_var = table.AddTempEntry(type);
    
  out_var->SetArrayIndex(in_var0->GetVarID(), in_var1->GetVarID());
  ica.AddArray(Instr::AR_GET_IDX, in_var0->GetVarID(), in_var1->GetVarID(), out_var->GetVarID());

  if (in_var0->GetTemp() == true) table.RemoveEntry( in_var0 );
  if (in_var1->GetTemp() == true) table.RemoveEntry( in_var1 );

  return out_var;
}

/////////////////////
// ASTNode_Random

ASTNode_Random::ASTNode_Random(ASTNode *in)
  : ASTNode_BaseChildren(Type::INT)
{
  if (in->GetType() != Type::INT) {
    yyerror ("random argument must be of type int");
    exit(1);
  }

  children.push_back(in);
}

tableEntry * ASTNode_Random::CompileTubeIC(symbolTable & table, IC_Array & ica)
{
  tableEntry * in_var = children[0]->CompileTubeIC(table, ica);
  tableEntry * out_var = table.AddTempEntry(type);

  ica.Add(Instr::RANDOM, in_var->GetVarID(), out_var->GetVarID());

  return out_var;
}

//////////////////////
// ASTNode_Method

ASTNode_Method::ASTNode_Method(ASTNode * in_base, string in_name)
  : ASTNode_VarChildren(Type::VOID), name(in_name)
{
  children.push_back(in_base);

  if (name == "size") SetType(Type::INT);
  else if (name == "resize") SetType(Type::VOID);
  else {
    string err_message = "unknown method '";
    err_message += name;
    err_message += "'";
    yyerror(err_message);
    exit(1);
  }

  // @CAO For the moment, require the base to be an array.
  if (!Type::IsArray(in_base->GetType())) {
    string err_message = "array methods cannot be run on type '";
    err_message += Type::AsString(in_base->GetType());
    err_message += "'";
    yyerror(err_message);
    exit(1);
  }
}


tableEntry * ASTNode_Method::CompileTubeIC(symbolTable & table, IC_Array & ica)
{
  tableEntry * array_var = children[0]->CompileTubeIC(table, ica);
  tableEntry * out_var = table.AddTempEntry(type);

  if (name == "size") {
    ica.AddArray(Instr::AR_GET_SIZ, array_var->GetVarID(), out_var->GetVarID());
  }
  else if (name == "resize") {
    tableEntry * size_var = children[1]->CompileTubeIC(table, ica);
    ica.AddArray(Instr::AR_SET_SIZ, array_var->GetVarID(), size_var->GetVarID());
    if (size_var->GetTemp() == true) table.RemoveEntry( size_var );
  }
  else {
    cerr << "Internal Compiler ERROR: Unknown method in ASTNode_Method" << endl;
    exit(1);
  }

  // Cleanup symbol table.
  if (array_var->GetTemp() == true) table.RemoveEntry( array_var );

  return out_var;
}

void ASTNode_Method::TypeCheckArgs()
{
  if (name == "size") {
    if (children.size() != 1) {
      yyerror("array size() method does not take any arguments.");
      exit(1);
    }
  }
  else if (name == "resize") {
    if (children.size() != 2) {
      yyerror("array resize() method takes exactly one (int) argument.");
      exit(1);
    }
    if (children[1]->GetType() != Type::INT) {
      yyerror("array resize() method argument must be of type int.");
      exit(1);
    }
  }
}


/////////////////////
// ASTNode_If

ASTNode_If::ASTNode_If(ASTNode * in1, ASTNode * in2, ASTNode * in3)
  : ASTNode_BaseChildren(Type::VOID)
{
  if (in1->GetType() != Type::INT) {
    yyerror("condition for if statements must evaluate to type int");
    exit(1);
  }

  children.push_back(in1);
  children.push_back(in2);
  children.push_back(in3);
}


tableEntry * ASTNode_If::CompileTubeIC(symbolTable & table, IC_Array & ica)
{
  string else_label = table.NextLabelID("if_else_");
  string end_label = table.NextLabelID("if_end_");

  tableEntry * in_var0 = children[0]->CompileTubeIC(table, ica);

  // If the condition is false, jump to else.  Otherwise continue through if.
  ica.Add(Instr::JUMP_IF_0, in_var0->GetVarID(), else_label);

  if (children[1]) {
    tableEntry * in_var1 = children[1]->CompileTubeIC(table, ica);
    if (in_var1 && in_var1->GetTemp() == true) table.RemoveEntry( in_var1 );
  }

  // Now that we are done with "if", jump to the end; also start the else here.
  ica.Add(Instr::JUMP, end_label);
  ica.AddLabel(else_label);

  if (children[2]) {
    tableEntry * in_var2 = children[2]->CompileTubeIC(table, ica);
    if (in_var2 && in_var2->GetTemp() == true) table.RemoveEntry( in_var2 );
  }

  // Close off the code with the end label.
  ica.AddLabel(end_label);

  return NULL;
}


/////////////////////
// ASTNode_While

ASTNode_While::ASTNode_While(ASTNode * in1, ASTNode * in2)
  : ASTNode_BaseChildren(Type::VOID)
{
  children.push_back(in1);
  children.push_back(in2);

  if (in1->GetType() != Type::INT) {
    yyerror("condition for while statements must evaluate to type int");
    exit(1);
  }
}


tableEntry * ASTNode_While::CompileTubeIC(symbolTable & table, IC_Array & ica)
{
  string start_label = table.NextLabelID("while_start_");
  string end_label = table.NextLabelID("while_end_");

  table.PushWhileEndLabel(end_label);

  ica.AddLabel(start_label);

  tableEntry * in_var0 = children[0]->CompileTubeIC(table, ica);

  // If the condition is false, jump to end.  Otherwise continue through body.
  ica.Add(Instr::JUMP_IF_0, in_var0->GetVarID(), end_label);

  if (children[1]) {
    tableEntry * in_var1 = children[1]->CompileTubeIC(table, ica);
    if (in_var1 && in_var1->GetTemp() == true) table.RemoveEntry( in_var1 );
  }

  // Now that we are done with the while body, jump back to the start.
  ica.Add(Instr::JUMP, start_label);
  ica.AddLabel(end_label);

  table.PopWhileEndLabel();

  return NULL;
}

/////////////////////
// ASTNode_Break

ASTNode_Break::ASTNode_Break()
  : ASTNode(Type::VOID)
{
}


tableEntry * ASTNode_Break::CompileTubeIC(symbolTable & table, IC_Array & ica)
{
  if (table.GetWhileDepth() == 0) {
    yyerror2("'break' command used outside of any loop", line_num);
    exit(1);
  }

  ica.Add(Instr::JUMP, table.GetWhileEndLabel());

  return NULL;
}


/////////////////////
// ASTNode_Print

ASTNode_Print::ASTNode_Print(ASTNode * out_child)
  : ASTNode_VarChildren(Type::VOID)
{
  // Save the child...
  if (out_child != NULL) AddChild(out_child);
}


tableEntry * ASTNode_Print::CompileTubeIC(symbolTable & table, IC_Array & ica)
{
  // Collect the output arguments as they are calculated...
  for (int i = 0; i < (int) children.size(); i++) {
    tableEntry * cur_var = children[i]->CompileTubeIC(table, ica);
    switch (cur_var->GetType()) {
    case Type::INT:
      ica.Add(Instr::OUT_INT, cur_var->GetVarID());
      break;
    case Type::CHAR:
      ica.Add(Instr::OUT_CHAR, cur_var->GetVarID());
      break;
    case Type::STRING:
    case Type::INT_ARRAY:
      {
        int size_id = table.GetTempVarID();
        int index_id = table.GetTempVarID();
        int entry_id = table.GetTempVarID();        
        string start_label = table.NextLabelID("print_array_start_");
        string end_label = table.NextLabelID("print_array_end_");
        
        ica.Add(Instr::VAL_COPY, "0", index_id, -1, "Init loop variable for printing array.");
        ica.AddArray(Instr::AR_GET_SIZ, cur_var->GetVarID(), size_id, -1, "Save size of array into variable.");
        ica.AddLabel(start_label);

        ica.Add(Instr::TEST_GTE, index_id, size_id, entry_id, "Test if we are finished yet...");
        ica.Add(Instr::JUMP_IF_N0, entry_id, end_label, -1, " ...and jump to end if so.");

        ica.AddArray(Instr::AR_GET_IDX, cur_var->GetVarID(), index_id, entry_id,
                     "Collect the value at the next index.");

        if (cur_var->GetType() == Type::STRING) ica.Add(Instr::OUT_CHAR, entry_id, -1, -1,
                                                        "Print this entry!");
        else if (cur_var->GetType() == Type::INT_ARRAY) ica.Add(Instr::OUT_INT, entry_id, -1, -1,
                                                                "Print this entry!");

        ica.Add(Instr::ADD, index_id, "1", index_id, "Increment to the next index.");
        
        ica.Add(Instr::JUMP, start_label);
        ica.AddLabel(end_label);

        table.FreeTempVarID(size_id);
        table.FreeTempVarID(index_id);
        table.FreeTempVarID(entry_id);
      }
      break;
    default:
      cerr << "Internal Compiler ERROR: Unknown Type in Write::CompilerTubeIC" << endl;
      exit(1);
    };

    if (cur_var->GetTemp() == true) table.RemoveEntry( cur_var );
  }
  ica.Add(Instr::OUT_CHAR, "'\\n'", -1, -1, "End print statements with a newline.");
  
  return NULL;
}
