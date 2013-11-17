#ifndef INST_H
#define INST_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class cHardware;

class cInstArg_Base {
protected:
  cHardware * hardware;
public:
  cInstArg_Base() { ; }
  virtual ~cInstArg_Base() { ; }

  virtual bool IsVar() { return false; }
  virtual bool SetInt(int value) { (void) value; return false; }

  virtual int AsInt() = 0;
  virtual float AsFloat() = 0;
  virtual string VerboseString() = 0;

  void SetHardware(cHardware * _h) { hardware = _h; }
};

class cInstArg_Int : public cInstArg_Base {
private:
  int value;
public:
  cInstArg_Int(int _v) : value(_v) { ; }
  ~cInstArg_Int() { ; }

  int AsInt() { return value; }
  float AsFloat() { return (float) value; }
  string VerboseString() {
    stringstream ss;
    ss << value;
    return ss.str();
  }
};

class cInstArg_Label : public cInstArg_Base {
private:
  string label;
  int value;
public:
  cInstArg_Label(string _l) : label(_l), value(-1) { ; }
  ~cInstArg_Label() { ; }

  int AsInt();
  float AsFloat() { return (float) AsInt(); }
  string VerboseString() {
    stringstream ss;
    ss << label;
    return ss.str();
  }
};

class cInstArg_Var : public cInstArg_Base {
private:
  int var_id;
public:
  cInstArg_Var(int _id) : var_id(_id) { ; }
  ~cInstArg_Var() { ; }

  bool IsVar() { return true; }
  bool SetInt(int value);
  string VerboseString() {
    stringstream ss;
    ss << "s" << var_id;
    return ss.str();
  }
 
  int AsInt();
  float AsFloat();
};

class cInstArg_Array : public cInstArg_Base {
private:
  int var_id;
public:
  cInstArg_Array(int _id) : var_id(_id) { ; }
  ~cInstArg_Array() { ; }

  int AsInt() { return var_id; };
  float AsFloat() { return 0.0; };
  string VerboseString() {
    stringstream ss;
    ss << "a" << var_id;
    return ss.str();
  }
};

class cInstArg_Reg : public cInstArg_Base {
private:
  int reg_id;
public:
  cInstArg_Reg(int _id) : reg_id(_id) { ; }
  ~cInstArg_Reg() { ; }

  bool IsVar() { return false; }
  bool SetInt(int value);
  string VerboseString() {
    stringstream ss;
    ss << "reg" << (char) ('A' + reg_id);
    return ss.str();
  }
 
  int AsInt();
  float AsFloat();
};

class cInstArg_IP : public cInstArg_Base {
private:
public:
  cInstArg_IP() { ; }
  ~cInstArg_IP() { ; }

  bool IsVar() { return false; }
  bool SetInt(int value);
  string VerboseString() {
    return "IP";
  }
 
  int AsInt();
  float AsFloat();
};


/////////////
//  cInst
/////////////
  
class cInst_Base {
protected:
  cHardware * hardware;
  int line_num;
  cInstArg_Base * arg1;
  cInstArg_Base * arg2;
  cInstArg_Base * arg3;
public:
  cInst_Base(int ln, cInstArg_Base * _a1=NULL, cInstArg_Base * _a2=NULL, cInstArg_Base * _a3=NULL)
    : line_num(ln), arg1(_a1), arg2(_a2), arg3(_a3) { ; }
  ~cInst_Base() { ; }
  
  virtual bool Run() { return false; }
  
  void SetHardware(cHardware * _h) {
    hardware = _h;
    if (arg1 != NULL) arg1->SetHardware(_h);
    if (arg2 != NULL) arg2->SetHardware(_h);
    if (arg3 != NULL) arg3->SetHardware(_h);
  }
  
  void PrintVerbose(string out_string);
};

class cInst_VAL_COPY : public cInst_Base {
private:
public:
  cInst_VAL_COPY(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2)
    : cInst_Base(ln, _a1, _a2) { ; }
  ~cInst_VAL_COPY() { ; }

  static string GetDesc() { return "val_copy : Duplicate the value of arg1 into arg2"; }
  bool Run() {
    PrintVerbose("val_copy");
    arg2->SetInt(arg1->AsInt());
    return true;
  }
};

class cInst_ADD : public cInst_Base {
 private:
 public:
  cInst_ADD(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2, cInstArg_Base * _a3)
    : cInst_Base(ln, _a1, _a2, _a3) { ; }
  ~cInst_ADD() { ; }

  static string GetDesc() { return "add : Add the values of arg1 and arg2 and place the sum in arg3"; }
  bool Run() {
    PrintVerbose("add");
    arg3->SetInt(arg1->AsInt() + arg2->AsInt());
    return true;
  }
};

class cInst_SUB : public cInst_Base {
private:
public:
  cInst_SUB(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2, cInstArg_Base * _a3)
    : cInst_Base(ln, _a1, _a2, _a3) { ; }
  ~cInst_SUB() { ; }

  static string GetDesc() { return "sub : Subtract the values of arg2 from arg1 and place the difference in arg3"; }
  bool Run() {
    PrintVerbose("sub");
    arg3->SetInt(arg1->AsInt() - arg2->AsInt());
    return true;
  }
};

class cInst_MULT : public cInst_Base {
private:
public:
  cInst_MULT(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2, cInstArg_Base * _a3)
    : cInst_Base(ln, _a1, _a2, _a3) { ; }
  ~cInst_MULT() { ; }

  static string GetDesc() { return "mult : Multiply the values of arg1 and arg2 and place the product in arg3"; }
  bool Run() {
    PrintVerbose("mult");
    arg3->SetInt(arg1->AsInt() * arg2->AsInt());
    return true;
  }
};

class cInst_DIV : public cInst_Base {
private:
public:
  cInst_DIV(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2, cInstArg_Base * _a3)
    : cInst_Base(ln, _a1, _a2, _a3) { ; }
  ~cInst_DIV() { ; }

  static string GetDesc() { return "div : Divide the value of arg1 by arg2 and place the floor of the ratio in arg3"; }
  bool Run();
};

class cInst_MOD : public cInst_Base {
private:
public:
  cInst_MOD(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2, cInstArg_Base * _a3)
    : cInst_Base(ln, _a1, _a2, _a3) { ; }
  ~cInst_MOD() { ; }

  static string GetDesc() { return "mod : Divide the value of arg1 by arg2 and place the *remainder* in arg3"; }
  bool Run();
};

class cInst_TEST_LESS : public cInst_Base {
private:
public:
  cInst_TEST_LESS(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2, cInstArg_Base * _a3)
    : cInst_Base(ln, _a1, _a2, _a3) { ; }
  ~cInst_TEST_LESS() { ; }

  static string GetDesc() { return "test_less : If (arg1 < arg2), arg3 is set to 1, else arg3 is set to 0"; }
  bool Run() {
    PrintVerbose("test_less");
    arg3->SetInt(arg1->AsInt() < arg2->AsInt());
    return true;
  }
};

class cInst_TEST_GTR : public cInst_Base {
private:
public:
  cInst_TEST_GTR(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2, cInstArg_Base * _a3)
    : cInst_Base(ln, _a1, _a2, _a3) { ; }
  ~cInst_TEST_GTR() { ; }

  static string GetDesc() { return "test_gtr : If (arg1 > arg2), arg3 is set to 1, else arg3 is set to 0"; }
  bool Run() {
    PrintVerbose("test_gtr");
    arg3->SetInt(arg1->AsInt() > arg2->AsInt());
    return true;
  }
};

class cInst_TEST_EQU : public cInst_Base {
private:
public:
  cInst_TEST_EQU(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2, cInstArg_Base * _a3)
    : cInst_Base(ln, _a1, _a2, _a3) { ; }
  ~cInst_TEST_EQU() { ; }

  static string GetDesc() { return "test_equ : If (arg1 == arg2), arg3 is set to 1, else arg3 is set to 0"; }
  bool Run() {
    PrintVerbose("test_equ");
    arg3->SetInt(arg1->AsInt() == arg2->AsInt());
    return true;
  }
};

class cInst_TEST_NEQU : public cInst_Base {
private:
public:
  cInst_TEST_NEQU(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2, cInstArg_Base * _a3)
    : cInst_Base(ln, _a1, _a2, _a3) { ; }
  ~cInst_TEST_NEQU() { ; }

  static string GetDesc() { return "test_nequ : If (arg1 != arg2), arg3 is set to 1, else arg3 is set to 0"; }
  bool Run() {
    PrintVerbose("test_nequ");
    arg3->SetInt(arg1->AsInt() != arg2->AsInt());
    return true;
  }
};

class cInst_TEST_GTE : public cInst_Base {
private:
public:
  cInst_TEST_GTE(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2, cInstArg_Base * _a3)
    : cInst_Base(ln, _a1, _a2, _a3) { ; }
  ~cInst_TEST_GTE() { ; }

  static string GetDesc() { return "test_gte : If (arg1 >= arg2), arg3 is set to 1, else arg3 is set to 0"; }
  bool Run() {
    PrintVerbose("test_gte");
    arg3->SetInt(arg1->AsInt() >= arg2->AsInt());
    return true;
  }
};

class cInst_TEST_LTE : public cInst_Base {
private:
public:
  cInst_TEST_LTE(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2, cInstArg_Base * _a3)
    : cInst_Base(ln, _a1, _a2, _a3) { ; }
  ~cInst_TEST_LTE() { ; }

  static string GetDesc() { return "test_lte : If (arg1 <= arg2), arg3 is set to 1, else arg3 is set to 0"; }
  bool Run() {
    PrintVerbose("test_lte");
    arg3->SetInt(arg1->AsInt() <= arg2->AsInt());
    return true;
  }
};

class cInst_JUMP : public cInst_Base {
private:
public:
  cInst_JUMP(int ln, cInstArg_Base * _a1)
    : cInst_Base(ln, _a1) { ; }
  ~cInst_JUMP() { ; }

  static string GetDesc() { return "jump : Jump IP to position designated by arg1"; }
  bool Run();
  
};


class cInst_JUMP_IF_0 : public cInst_Base {  
private:
public:
  cInst_JUMP_IF_0(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2)
    : cInst_Base(ln, _a1, _a2) { ; }
  ~cInst_JUMP_IF_0() { ; }

  static string GetDesc() { return "jump_if_0 : If arg1 == 0, Jump IP to position designated by arg2"; }
  bool Run();
};

class cInst_JUMP_IF_N0 : public cInst_Base {
private:
public:
  cInst_JUMP_IF_N0(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2)
    : cInst_Base(ln, _a1, _a2) { ; }
  ~cInst_JUMP_IF_N0() { ; }

  static string GetDesc() { return "jump_if_n0 : If arg1 != 0, Jump IP to position designated by arg2"; }
  bool Run();
};

class cInst_NOP : public cInst_Base {
private:
public:
  cInst_NOP(int ln) : cInst_Base(ln) { ; }
  ~cInst_NOP() { ; }

  static string GetDesc() { return "nop : No-operation."; }
  bool Run() {
    PrintVerbose("nop");
    return true;
  }
};

class cInst_RANDOM : public cInst_Base {
private:
public:
  cInst_RANDOM(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2)
    : cInst_Base(ln, _a1, _a2) { ; }
  ~cInst_RANDOM() { ; }

  static string GetDesc() { return "random : set arg2 to a random value x, where 0 <= x < arg1."; }
  bool Run();
};

class cInst_OUT_INT : public cInst_Base {
private:
public:
  cInst_OUT_INT(int ln, cInstArg_Base * _a1)
    : cInst_Base(ln, _a1) { ; }
  ~cInst_OUT_INT() { ; }

  static string GetDesc() { return "out_int : Print out arg1 as an integer"; }
  bool Run() {
    PrintVerbose("out_int");
    cout << arg1->AsInt();
    return true;
  }
};

class cInst_OUT_FLOAT : public cInst_Base {
private:
public:
  cInst_OUT_FLOAT(int ln, cInstArg_Base * _a1)
    : cInst_Base(ln, _a1) { ; }
  ~cInst_OUT_FLOAT() { ; }

  static string GetDesc() { return "out_float : Print out arg1 as a floating-point number"; }
  bool Run() {
    PrintVerbose("out_float");
    cout << arg1->AsFloat();
    return true;
  }
};

class cInst_OUT_CHAR : public cInst_Base {
private:
public:
  cInst_OUT_CHAR(int ln, cInstArg_Base * _a1)
    : cInst_Base(ln, _a1) { ; }
  ~cInst_OUT_CHAR() { ; }

  static string GetDesc() { return "out_char : Print out arg1 as a character"; }
  bool Run() {
    PrintVerbose("out_char");
    cout << (char) arg1->AsInt();
    return true;
  }
};

class cInst_PUSH_NUM : public cInst_Base {
private:
public:
  cInst_PUSH_NUM(int ln, cInstArg_Base * _a1)
    : cInst_Base(ln, _a1) { ; }
  ~cInst_PUSH_NUM() { ; }

  static string GetDesc() { return "push : Store arg1 in an internal control stack"; }
  bool Run();
};

class cInst_PUSH_ARRAY : public cInst_Base {
private:
public:
  cInst_PUSH_ARRAY(int ln, cInstArg_Base * _a1)
    : cInst_Base(ln, _a1) { ; }
  ~cInst_PUSH_ARRAY() { ; }

  static string GetDesc() { return "push : Store arg1 in an internal control stack"; }
  bool Run();
};

class cInst_POP_NUM : public cInst_Base {
private:
public:
  cInst_POP_NUM(int ln, cInstArg_Base * _a1)
    : cInst_Base(ln, _a1) { ; }
  ~cInst_POP_NUM() { ; }

  static string GetDesc() { return "pop : Retrieve arg1 from an internal control stack"; }
  bool Run();
};

class cInst_POP_ARRAY : public cInst_Base {
private:
public:
  cInst_POP_ARRAY(int ln, cInstArg_Base * _a1)
    : cInst_Base(ln, _a1) { ; }
  ~cInst_POP_ARRAY() { ; }

  static string GetDesc() { return "pop : Retrieve arg1 from an internal control stack"; }
  bool Run();
};

class cInst_AR_GET_IDX : public cInst_Base {
private:
public:
  cInst_AR_GET_IDX(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2, cInstArg_Base * _a3)
    : cInst_Base(ln, _a1, _a2, _a3) { ; }
  ~cInst_AR_GET_IDX() { ; }

  static string GetDesc() { return "ar_get_idx : In array arg1, find value @ index arg2, and put result in arg3"; }
  bool Run();
};

class cInst_AR_SET_IDX : public cInst_Base {
private:
public:
  cInst_AR_SET_IDX(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2, cInstArg_Base * _a3)
    : cInst_Base(ln, _a1, _a2, _a3) { ; }
  ~cInst_AR_SET_IDX() { ; }

  static string GetDesc() { return "ar_set_idx : In array arg1, set value @ index arg2 to value arg3"; }
  bool Run();
};

class cInst_AR_GET_SIZ : public cInst_Base {
private:
public:
  cInst_AR_GET_SIZ(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2)
    : cInst_Base(ln, _a1, _a2) { ; }
  ~cInst_AR_GET_SIZ() { ; }

  static string GetDesc() { return "ar_get_siz : Calculate size of array arg1 and put result in arg2"; }
  bool Run();
};

class cInst_AR_SET_SIZ : public cInst_Base {
private:
public:
  cInst_AR_SET_SIZ(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2)
    : cInst_Base(ln, _a1, _a2) { ; }
  ~cInst_AR_SET_SIZ() { ; }

  static string GetDesc() { return "ar_set_siz : Resize array arg1 to arg2"; }
  bool Run();
};

class cInst_AR_COPY : public cInst_Base {
private:
public:
  cInst_AR_COPY(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2)
    : cInst_Base(ln, _a1, _a2) { ; }
  ~cInst_AR_COPY() { ; }

  static string GetDesc() { return "ar_copy : Duplicate the value in array arg1 to array arg2"; }
  bool Run();
};

class cInst_LOAD : public cInst_Base {
private:
public:
  cInst_LOAD(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2)
    : cInst_Base(ln, _a1, _a2) { ; }
  ~cInst_LOAD() { ; }

  static string GetDesc() { return "load : Copy from memory position arg1 into register arg2"; }
  bool Run();
};

class cInst_STORE : public cInst_Base {
private:
public:
  cInst_STORE(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2)
    : cInst_Base(ln, _a1, _a2) { ; }
  ~cInst_STORE() { ; }

  static string GetDesc() { return "store : Copy from register arg1 into memory position arg2"; }
  bool Run();
};

class cInst_MEM_COPY : public cInst_Base {
private:
public:
  cInst_MEM_COPY(int ln, cInstArg_Base * _a1, cInstArg_Base * _a2)
    : cInst_Base(ln, _a1, _a2) { ; }
  ~cInst_MEM_COPY() { ; }

  static string GetDesc() { return "mem_copy : Copy from memory position arg1 to memory position arg2"; }
  bool Run();
};

#endif
