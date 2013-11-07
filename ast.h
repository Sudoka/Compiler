/*
  - Faisal Tameesh
  - Kodai Ishikawa
  - Matt Wein
*/

#ifndef AST_H
#define AST_H

#include <iostream>
#include <vector>

extern long boolNumber;

using namespace std;

class ASTNode_Base {
protected:
  vector<ASTNode_Base *> args;
  
public:
  ASTNode_Base() { ; }
  virtual ~ASTNode_Base() {
    for (int i = 0; i < (int) args.size(); i++) delete args[i];    
  }

  virtual void Print() { cerr << "ERROR: Printing Base class!" << endl; }
  virtual int WriteIC(int & nvar) { cerr << "ERROR: WriteIC called from base class!" << endl; }
  
};

class ASTNode_Number : public ASTNode_Base {
private:
  int value;

public:
  ASTNode_Number(int in_value) : value(in_value) { ; }
  ~ASTNode_Number() { ; }

  void Print() { cout << "STATIC_NUMBER: " << value << endl; }
  int WriteIC(int & nvar) {
    int out_var = nvar++;;
    cout << "val_copy " << value << " s" << out_var << endl;
    return out_var;
  }
};

class ASTNode_UMinus : public ASTNode_Base {
public:
  ASTNode_UMinus(ASTNode_Base * in_node) { args.push_back(in_node); }
  ~ASTNode_UMinus() { ; }

  void Print() {
    args[0]->Print();
    cout << "NEGATE!" << endl;
  }
  
  int WriteIC(int & nvar) {
    int arg_var = args[0]->WriteIC(nvar);
    int out_var = nvar++;;
    cout << "sub 0 s" << arg_var << " s" << out_var << endl;
    return out_var;
  }
};

class ASTNode_Add : public ASTNode_Base
{
public:
  ASTNode_Add(ASTNode_Base * node1, ASTNode_Base * node2) {
    args.push_back(node1);
    args.push_back(node2);
  }
  int WriteIC(int & nvar) {
    int var0 = args[0]->WriteIC(nvar);
    int var1 = args[1]->WriteIC(nvar);
    int out_var = nvar++;;
    cout << "add s" << var0 << " s" << var1 << " s" << out_var << endl;
    return out_var;
  }
};

class ASTNode_Var : public ASTNode_Base {
 private:
  int var_id;

 public:
  ASTNode_Var(int in_id) : var_id(in_id) { ; }
  ~ASTNode_Var() { ; }

  void Print() { cout << "VARIABLE!" << endl; }
  int WriteIC(int & nvar) {
    return var_id;
  }
};

class ASTNode_Sub : public ASTNode_Base
{
public:
  ASTNode_Sub(ASTNode_Base * node1, ASTNode_Base * node2) {
    args.push_back(node1);
    args.push_back(node2);
  }
  int WriteIC(int & nvar) {
    int var0 = args[0]->WriteIC(nvar);
    int var1 = args[1]->WriteIC(nvar);
    int out_var = nvar++;;
    cout << "sub s" << var0 << " s" << var1 << " s" << out_var << endl;
    return out_var;
  }
};

class ASTNode_Mult : public ASTNode_Base
{
public:
  ASTNode_Mult(ASTNode_Base * node1, ASTNode_Base * node2) {
    args.push_back(node1);
    args.push_back(node2);
  }
  int WriteIC(int & nvar) {
    int var0 = args[0]->WriteIC(nvar);
    int var1 = args[1]->WriteIC(nvar);
    int out_var = nvar++;;
    cout << "mult s" << var0 << " s" << var1 << " s" << out_var << endl;
    return out_var;
  }
};

class ASTNode_Div : public ASTNode_Base
{
public:
  ASTNode_Div(ASTNode_Base * node1, ASTNode_Base * node2) {
    args.push_back(node1);
    args.push_back(node2);
  }
  int WriteIC(int & nvar) {
    int var0 = args[0]->WriteIC(nvar);
    int var1 = args[1]->WriteIC(nvar);
    int out_var = nvar++;;
    cout << "div s" << var0 << " s" << var1 << " s" << out_var << endl;
    return out_var;
  }
};

class ASTNode_Mod : public ASTNode_Base
{
public:
  ASTNode_Mod(ASTNode_Base * node1, ASTNode_Base * node2) {
    args.push_back(node1);
    args.push_back(node2);
  }
  int WriteIC(int & nvar) {
    int var0 = args[0]->WriteIC(nvar);
    int var1 = args[1]->WriteIC(nvar);
    int out_var = nvar++;;
    cout << "mod s" << var0 << " s" << var1 << " s" << out_var << endl;
    return out_var;
  }
};

class ASTNode_Req : public ASTNode_Base
{
public:
  ASTNode_Req(ASTNode_Base * node1, ASTNode_Base * node2) {
    args.push_back(node1);
    args.push_back(node2);
  }
  int WriteIC(int & nvar) {
    int var0 = args[0]->WriteIC(nvar);
    int var1 = args[1]->WriteIC(nvar);
    int out_var = nvar++;;
    cout << "test_equ s" << var0 << " s" << var1 << " s" << out_var << endl;
    return out_var;
  }
};

class ASTNode_Rneq : public ASTNode_Base
{
public:
  ASTNode_Rneq(ASTNode_Base * node1, ASTNode_Base * node2) {
    args.push_back(node1);
    args.push_back(node2);
  }
  int WriteIC(int & nvar) {
    int var0 = args[0]->WriteIC(nvar);
    int var1 = args[1]->WriteIC(nvar);
    int out_var = nvar++;;
    cout << "test_nequ s" << var0 << " s" << var1 << " s" << out_var << endl;
    return out_var;
  }
};

class ASTNode_Rles : public ASTNode_Base
{
public:
  ASTNode_Rles(ASTNode_Base * node1, ASTNode_Base * node2) {
    args.push_back(node1);
    args.push_back(node2);
  }
  int WriteIC(int & nvar) {
    int var0 = args[0]->WriteIC(nvar);
    int var1 = args[1]->WriteIC(nvar);
    int out_var = nvar++;;
    cout << "test_less s" << var0 << " s" << var1 << " s" << out_var << endl;
    return out_var;
  }
};

class ASTNode_Rgtr : public ASTNode_Base
{
public:
  ASTNode_Rgtr(ASTNode_Base * node1, ASTNode_Base * node2) {
    args.push_back(node1);
    args.push_back(node2);
  }
  int WriteIC(int & nvar) {
    int var0 = args[0]->WriteIC(nvar);
    int var1 = args[1]->WriteIC(nvar);
    int out_var = nvar++;;
    cout << "test_gtr s" << var0 << " s" << var1 << " s" << out_var << endl;
    return out_var;
  }
};

class ASTNode_Rleq : public ASTNode_Base
{
public:
  ASTNode_Rleq(ASTNode_Base * node1, ASTNode_Base * node2) {
    args.push_back(node1);
    args.push_back(node2);
  }
  int WriteIC(int & nvar) {
    int var0 = args[0]->WriteIC(nvar);
    int var1 = args[1]->WriteIC(nvar);
    int out_var = nvar++;;
    cout << "test_lte s" << var0 << " s" << var1 << " s" << out_var << endl;
    return out_var;
  }
};

class ASTNode_Rgeq : public ASTNode_Base
{
public:
  ASTNode_Rgeq(ASTNode_Base * node1, ASTNode_Base * node2) {
    args.push_back(node1);
    args.push_back(node2);
  }
  int WriteIC(int & nvar) {
    int var0 = args[0]->WriteIC(nvar);
    int var1 = args[1]->WriteIC(nvar);
    int out_var = nvar++;;
    cout << "test_gte s" << var0 << " s" << var1 << " s" << out_var << endl;
    return out_var;
  }
};

class ASTNode_And : public ASTNode_Base
{
public:
  ASTNode_And(ASTNode_Base * node1, ASTNode_Base * node2) {
    args.push_back(node1);
    args.push_back(node2);
  }
  int WriteIC(int & nvar) {
    int var0 = args[0]->WriteIC(nvar);
    int out_var = nvar++;;
    cout << "test_nequ s" << var0 << " 0" << " s" << out_var << endl;
    cout << "jump_if_0 s" << out_var << " BOOL_END_" << boolNumber << endl;
    int var1 = args[1]->WriteIC(nvar);
    cout << "test_nequ s" << var1 << " 0" << " s" << out_var << endl;
    cout << "BOOL_END_" << boolNumber << ":" << endl;
    boolNumber++;
    return out_var;
  }
};

class ASTNode_Or : public ASTNode_Base
{
public:
  ASTNode_Or(ASTNode_Base * node1, ASTNode_Base * node2) {
    args.push_back(node1);
    args.push_back(node2);
  }
  int WriteIC(int & nvar) {
    int var0 = args[0]->WriteIC(nvar);
    int out_var = nvar++;;
    cout << "test_nequ s" << var0 << " 0" << " s" << out_var << endl;
    cout << "jump_if_n0 s" << out_var << " BOOL_END_" << boolNumber << endl;
    int var1 = args[1]->WriteIC(nvar);
    cout << "test_nequ s" << var1 << " 0" << " s" << out_var << endl;
    cout << "BOOL_END_" << boolNumber << ":" << endl;
    boolNumber++;
    return out_var;
  }
};

class ASTNode_Not : public ASTNode_Base
{
public:
  ASTNode_Not(ASTNode_Base * node1) {
    args.push_back(node1);
  }
  int WriteIC(int & nvar) {
    int arg_var = args[0]->WriteIC(nvar);
    int out_var = nvar++;;
    cout << "test_equ 0 s"<<arg_var<<" s"<<out_var<<endl;
    return out_var;
  }
};

class ASTNode_Print : public ASTNode_Base {
public:
  ASTNode_Print(ASTNode_Base * _in) { args.push_back(_in); }
  ~ASTNode_Print() { ; }

  void Print() { cout << "PRINT!" << endl; }
  int WriteIC(int & nvar) {
    int print_var = args[0]->WriteIC(nvar);
    cout << "out_int s" << print_var << endl;
    cout << "out_char '\\n'" << endl;
    return -1;
  }
  int WriteICMulti(int & nvar) {
    int print_var = args[0]->WriteIC(nvar);
    cout << "out_int s" << print_var << endl;
    return -1;
  }
};

class ASTNode_Assign : public ASTNode_Base {
 public:
  ASTNode_Assign(ASTNode_Base * lhs, ASTNode_Base * rhs) {
    args.push_back(lhs);
    args.push_back(rhs);
  }

  void Print() { args[0]->Print(); args[1]->Print(); cout << "ASSIGN!" << endl; }
  int WriteIC(int & nvar) {  // Remember, in your project this is part of expression!;
    int lhs_var = args[0]->WriteIC(nvar);
    int rhs_var = args[1]->WriteIC(nvar);
    cout << "val_copy s" << rhs_var << " s" << lhs_var << endl;
    return lhs_var;
  }
};

/*
class ASTNode_MultExp : public ASTNode_Base {
 public:
  ASTNode_Assign(ASTNode_Base * in) {
    args.push_back(in);
  }

  //void Print() { args[0]->Print(); args[1]->Print(); cout << "ASSIGN!" << endl; }
  int WriteIC(int & nvar) {  // Remember, in your project this is part of expression!;
  for(int x = 0; x<args.size(); x++)
     args[x]->WriteIC(nvar);
  }
  
  void clear() {args.clear();}
};
*/

#endif
