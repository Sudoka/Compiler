#ifndef IC_H
#define IC_H

#include "instr_info.h"
#include "symbol_table.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// The classes in this file hold information about the intermediate code (IC) and how it is stored
// in memory before the file is printed out.
//
// The IC_Arg_* classes hold information about the arguments associated with each instruction
//   IC_Arg_Base is the base class that all of the others are derived from.
//   IC_Arg_VarScalar holds info about scalar variables used as arguments (eg, s27).
//   IC_Arg_VarConst holds info about literal numbers or chars used as arguments (eg 10 or 'Q').
//   IC_Arg_VarArray holds info about array variables used as arguments (eg, a5).
//
// The IC_Entry class holds information about a single instruction.
//
// The IC_Array class holds an array of IC_Entries that make up the full intermediate code program.
//

class IC_Arg_Base {
public:
  IC_Arg_Base() { ; }
  virtual ~IC_Arg_Base() { ; }

  virtual string AsString() = 0;
  virtual int GetID() { return -1; }

  virtual bool IsScalar() { return false; }
  virtual bool IsConst() { return false; }
  virtual bool IsArray() { return false; }
};

class IC_Arg_VarScalar : public IC_Arg_Base {
private:
  int var_id;
public:
  IC_Arg_VarScalar(int _id) : var_id(_id) { ; }
  ~IC_Arg_VarScalar() { ; }

  string AsString() {
    stringstream out_str;
    out_str << "s" << var_id;
    return out_str.str();
  }
  int GetID() { return var_id; }

  bool IsScalar() { return true; }
};

// All constant values: int, char, or label.
class IC_Arg_Const : public IC_Arg_Base {
private:
  string value;
public:
  IC_Arg_Const(string _val) : value(_val) { ; }
  ~IC_Arg_Const() { ; }

  string AsString() { return value; }

  bool IsConst() { return true; }
};

class IC_Arg_VarArray : public IC_Arg_Base {
private:
  int var_id;
public:
  IC_Arg_VarArray(int _id) : var_id(_id) { ; }
  ~IC_Arg_VarArray() { ; }

  string AsString() {
    stringstream out_str;
    out_str << "a" << var_id;
    return out_str.str();
  }
  int GetID() { return var_id; }
  
  bool IsArray() { return true; }
};



class IC_Entry {
private:
  int instr_type;
  string label;
  string comment;
  vector<IC_Arg_Base*> args;
public:
  IC_Entry(int in_instr=Instr::__NO_INSTRUCTION__, string in_label="") : instr_type(in_instr), label(in_label) { ; }
  ~IC_Entry() { ; }

  void AddArray(int id)    { args.push_back(new IC_Arg_VarArray(id)); }
  void AddConst(string id) { args.push_back(new IC_Arg_Const(id)); }
  void AddScalar(int id)    { args.push_back(new IC_Arg_VarScalar(id)); }

  void SetLabel(string in_lab) { label = in_lab; }
  void SetComment(string cmt) { comment = cmt; }

  void PrintTC(symbolTable & table, ofstream & ofs);
  
  void PrintTC_Val_Copy(ofstream & ofs);  
  void PrintTC_Out_Int(ofstream & ofs);
  void PrintTC_Out_Char(ofstream & ofs);
  void PrintTC_Ar_Set_Siz(symbolTable & table, ofstream & ofs);
	void PrintTC_Ar_Set_Idx(ofstream & ofs);
	void PrintTC_Ar_Get_Idx(ofstream & ofs);
  void PrintTC_Ar_Get_Siz(ofstream & ofs);
  void PrintTC_Test_Equ(ofstream & ofs);
  void PrintTC_Test_Nequ(ofstream & ofs);
  void PrintTC_Test_Gtr(ofstream & ofs);
  void PrintTC_Test_Gte(ofstream & ofs);
  void PrintTC_Test_Less(ofstream & ofs);
  void PrintTC_Test_Lte(ofstream & ofs);
  void PrintTC_Jump(ofstream & ofs);
  void PrintTC_Jump_If_N0(ofstream & ofs);
  void PrintTC_Jump_If_0(ofstream & ofs);
  void PrintTC_Add(ofstream & ofs);
  void PrintTC_Mult(ofstream & ofs);
  void PrintTC_Sub(ofstream & ofs);
  void PrintTC_Div(ofstream & ofs);
  void PrintTC_Mod(ofstream & ofs);
  void PrintTC_Random(ofstream & ofs);
};


class IC_Array {
private:
  vector <IC_Entry*> ic_array;

public:
  IC_Array() { ; }
  ~IC_Array() { ; }

  IC_Entry& AddLabel(string label_id, string cmt="");

  // All forms of Add() method.
  // Arguments can either be variables (where an int represents the variable ID) or
  // constant values (where a string holds the constant's lexeme).
  IC_Entry& Add(int inst, int arg1=-1, int arg2=-1, int arg3=-1, string cmt="");
  IC_Entry& Add(int inst, string arg1, int arg2=-1, int arg3=-1, string cmt="");
  IC_Entry& Add(int inst, int arg1,    string arg2, int arg3=-1, string cmt="");
  IC_Entry& Add(int inst, string arg1, string arg2, int arg3=-1, string cmt="");
  IC_Entry& Add(int inst, int arg1,    int arg2,    string arg3, string cmt="");
  IC_Entry& Add(int inst, string arg1, int arg2,    string arg3, string cmt="");
  IC_Entry& Add(int inst, int arg1,    string arg2, string arg3, string cmt="");
  IC_Entry& Add(int inst, string arg1, string arg2, string arg3, string cmt="");

  // And an AddArray method to handle the four array-based instructions.
  // (first arg is always array id; second arg is always mandatory)
  IC_Entry& AddArray(int inst, int arg1, int arg2,    int arg3=-1, string cmt="");
  IC_Entry& AddArray(int inst, int arg1, string arg2, int arg3=-1, string cmt="");
  IC_Entry& AddArray(int inst, int arg1, int arg2,    string arg3, string cmt="");
  IC_Entry& AddArray(int inst, int arg1, string arg2, string arg3, string cmt="");

  void PrintTC(symbolTable & table, ofstream & ofs);
};

#endif
