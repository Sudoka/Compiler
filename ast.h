#ifndef AST_H
#define AST_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

#include "ic.h"
#include "type_info.h"
#include "symbol_table.h"

class ASTNode_VarChildren;

// The classes in this file hold info about the nodes that form the Abstract Syntax Tree (AST)
//
// ASTNode : The base class for all of the others, with useful virtual functions.
// ASTNode_BaseChildren : Base class for internal tree nodes (with children)
// ASTNode_VarChildren : Base class for nodes with a variable number of children (like Print)
//
// ASTNode_TempNode : AST Node that will be replaced (used for argument lists).
// ASTNode_Root : Blocks of statements, including the overall program.
// ASTNode_Variable : Leaf node containing a variable.
// ASTNode_Literal : Leaf node contiaing a literal value.
// ASTNode_Assign : Assignements
// ASTNode_Math1 : One-input math operations (unary '-' and '!')
// ASTNode_Math2 : Two-input math operations ('+', '-', '*', '/', '%', and comparisons)
// ASTNode_Bool2 : Two-input bool operations ('&&' and '||')
// ASTNode_ArrayAccess : Index into an array
// ASTNode_Method : Currently, array methods .size() and .resize()
// ASTNode_If : If-conditional node.
// ASTNode_While : While-loop node.
// ASTNode_Random : Random command
// ASTNode_Break : Break node
// ASTNode_Print : Print command

class ASTNode {
protected:
  int type;       // What type should this node pass up?
  int line_num;   // What line of the source program generated this node?

  void SetType(int new_type) { type = new_type; } // Use inside constructor only!
public:
  ASTNode(int in_type) : type(in_type), line_num(-1) { ; }
  virtual ~ASTNode() { ; }

  int GetType() { return type; }
  int GetLineNum() { return line_num; }

  void SetLineNum(int _in) { line_num = _in; }
  virtual void AddChild(ASTNode * in_child) {
    cerr << "ERROR: Calling AddChild() in base class!" << endl;
  }
  virtual void TransferChildren(ASTNode_VarChildren * in_node) {
    cerr << "ERROR: Calling TransferChildren() in base class!" << endl;
  }

  // Convert a single node to TubeIC and return information about the
  // variable where the results are saved.  Call children recursively.
  virtual tableEntry * CompileTubeIC(symbolTable & table, IC_Array & ica) = 0;

  // Return the name of the node being called.  This function is useful for debbing the AST.
  virtual string GetName() { return "ASTNode (base class)"; }
};


// Create a second base class for nodes with children...

class ASTNode_BaseChildren : public ASTNode {
protected:
  vector<ASTNode *> children;  // What sub-trees does this node have?
public:
  ASTNode_BaseChildren(int in_type) : ASTNode(in_type) { ; }
  virtual ~ASTNode_BaseChildren() {
    for (int i = 0; i < (int) children.size(); i++) {
      delete children[i];
    }
  }

  ASTNode * GetChild(int id) { return children[id]; }
  int GetNumChildren() { return children.size(); }

  void SetChild(int id, ASTNode * in_node) { children[id] = in_node; }

  virtual tableEntry * CompileTubeIC(symbolTable & table, IC_Array & ica) = 0;

  virtual string GetName() {
    return "ASTNode_BaseChildren (level 2 base class)";
  }
};

// Create a third base AST node for those node type with a variable
// number of children.

class ASTNode_VarChildren : public ASTNode_BaseChildren {
public:
  ASTNode_VarChildren(int in_type) : ASTNode_BaseChildren(in_type) { ; }
  virtual ~ASTNode_VarChildren() { ; }

  void AddChild(ASTNode * in_child) { children.push_back(in_child); }
  void TransferChildren(ASTNode_VarChildren * in_node);

  virtual tableEntry * CompileTubeIC(symbolTable & table, IC_Array & ica) = 0;
  virtual string GetName() {
    return "ASTNode_VarChildren (level 3 base class)";
  }
};

// A placeholder in the AST.
class ASTNode_TempNode : public ASTNode_VarChildren {
public:
  ASTNode_TempNode(int in_type) : ASTNode_VarChildren(in_type) { ; }
  ~ASTNode_TempNode() { ; }
  tableEntry * CompileTubeIC(symbolTable & table, IC_Array & ica) { return NULL; }

  virtual string GetName() {
    return "ASTNode_TempNode (under construction)";
  }
};

// Root...
class ASTNode_Root : public ASTNode_VarChildren {
public:
  ASTNode_Root() : ASTNode_VarChildren(Type::VOID) { ; }
  tableEntry * CompileTubeIC(symbolTable & table, IC_Array & ica);

  virtual string GetName() { return "ASTNode_Root (container class)"; }
};

// Leaves...
class ASTNode_Variable : public ASTNode {
private:
  tableEntry * var_entry;
public:
  ASTNode_Variable(tableEntry * in_entry)
    : ASTNode(in_entry->GetType()), var_entry(in_entry) {;}

  tableEntry * GetVarEntry() { return var_entry; }
  tableEntry * CompileTubeIC(symbolTable & table, IC_Array & ica);

  virtual string GetName() {
    string out_string = "ASTNode_Variable (";
    out_string += var_entry->GetName();
    out_string += ")";
    return out_string;
  }
};

class ASTNode_Literal : public ASTNode {
private:
  string lexeme;     // When we print, how should this node look?
public:
  ASTNode_Literal(int in_type, string in_lex);
  tableEntry * CompileTubeIC(symbolTable & table, IC_Array & ica);

  virtual string GetName() {
    string out_string = "ASTNode_Literal (";
    out_string += lexeme;
    out_string += ")";
    return out_string;
  }
};

// Math...

class ASTNode_Assign : public ASTNode_BaseChildren {
public:
  ASTNode_Assign(ASTNode * lhs, ASTNode * rhs);
  ~ASTNode_Assign() { ; }

  tableEntry * CompileTubeIC(symbolTable & table, IC_Array & ica);
  virtual string GetName() { return "ASTNode_Assign (operator=)"; }
};

class ASTNode_Math1 : public ASTNode_BaseChildren {
protected:
  int math_op;
  static int ChooseType(ASTNode * child);
public:
  ASTNode_Math1(ASTNode * in_child, int op);
  virtual ~ASTNode_Math1() { ; }

  tableEntry * CompileTubeIC(symbolTable & table, IC_Array & ica);
  virtual string GetName() {
    string out_string = "ASTNode_Math1 (operator";
    out_string += (char) math_op;
    out_string += ")";
    return out_string;
  }
};

class ASTNode_Math2 : public ASTNode_BaseChildren {
protected:
  int math_op;
  static int ChooseType(ASTNode * child1, ASTNode * child2);
public:
  ASTNode_Math2(ASTNode * in1, ASTNode * in2, int op);
  virtual ~ASTNode_Math2() { ; }

  tableEntry * CompileTubeIC(symbolTable & table, IC_Array & ica);
  virtual string GetName() {
    string out_string = "ASTNode_Math2 (operator";
    out_string += (char) math_op;
    out_string += ")";
    return out_string;
  }
};

class ASTNode_Bool2 : public ASTNode_BaseChildren {
protected:
  int bool_op;
  static int ChooseType(ASTNode * child1, ASTNode * child2);
public:
  ASTNode_Bool2(ASTNode * in1, ASTNode * in2, int op);
  virtual ~ASTNode_Bool2() { ; }

  tableEntry * CompileTubeIC(symbolTable & table, IC_Array & ica);
  virtual string GetName() {
    string out_string = "ASTNode_Bool2 (operator";
    out_string += (char) bool_op;
    out_string += ")";
    return out_string;
  }
};

class ASTNode_ArrayAccess : public ASTNode_BaseChildren {
protected:
public:
  ASTNode_ArrayAccess(ASTNode * in1, ASTNode * in2);
  virtual ~ASTNode_ArrayAccess() { ; }

  tableEntry * CompileTubeIC(symbolTable & table, IC_Array & ica);
  virtual string GetName() {
    string out_string = "ASTNode_ArrayAccess";
    return out_string;
  }
};


class ASTNode_Method : public ASTNode_VarChildren {
protected:
  string name;
public:
  ASTNode_Method(ASTNode * in_base, string in_name);
  virtual ~ASTNode_Method() { ; }

  tableEntry * CompileTubeIC(symbolTable & table, IC_Array & ica);
  virtual string GetName() {
    string out_string = "ASTNode_Method";
    return out_string;
  }

  void TypeCheckArgs();  // Run after args are added.
};

class ASTNode_If : public ASTNode_BaseChildren {
protected:
public:
  ASTNode_If(ASTNode * in1, ASTNode * in2, ASTNode * in3);
  virtual ~ASTNode_If() { ; }

  tableEntry * CompileTubeIC(symbolTable & table, IC_Array & ica);
  virtual string GetName() {
    string out_string = "ASTNode_If";
    return out_string;
  }
};

class ASTNode_While : public ASTNode_BaseChildren {
protected:
public:
  ASTNode_While(ASTNode * in1, ASTNode * in2);
  virtual ~ASTNode_While() { ; }

  tableEntry * CompileTubeIC(symbolTable & table, IC_Array & ica);
  virtual string GetName() {
    string out_string = "ASTNode_While";
    return out_string;
  }
};

class ASTNode_Break : public ASTNode {
public:
  ASTNode_Break();
  virtual ~ASTNode_Break() { ; }

  tableEntry * CompileTubeIC(symbolTable & table, IC_Array & ica);
  virtual string GetName() {
    string out_string = "ASTNode_Break";
    return out_string;
  }
};

class ASTNode_Print : public ASTNode_VarChildren {
public:
  ASTNode_Print(ASTNode * out_child);
  virtual ~ASTNode_Print() {;}

  tableEntry * CompileTubeIC(symbolTable & table, IC_Array & ica);
  virtual string GetName() { return "ASTNode_Print"; }
};

class ASTNode_Random : public ASTNode_BaseChildren {
public:
  ASTNode_Random(ASTNode * in);
  virtual ~ASTNode_Random() { ; }

  tableEntry * CompileTubeIC(symbolTable & table, IC_Array & ica);
  virtual string GetName() {
    string out_string = "ASTNode_Random";
    return out_string;
  }
};

#endif
