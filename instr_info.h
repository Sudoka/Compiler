#ifndef INSTR_INFO_H
#define INSTR_INFO_H

#include <string>

namespace Instr {
  enum Instr_Names { 
  VAL_COPY=0, 
  OUT_INT,
  OUT_CHAR,
  AR_SET_SIZ, 
  AR_SET_IDX, 
  AR_GET_IDX, 
  AR_GET_SIZ, 
  TEST_EQU, 
  TEST_NEQU,
  TEST_GTR,
  TEST_GTE,
  TEST_LESS,
  TEST_LTE,
  JUMP,
  JUMP_IF_0,
  JUMP_IF_N0, 
  ADD,
  MULT,
  SUB,
  DIV,
  MOD,
  RANDOM,
  NOP,
  PUSH,
  POP,
  __NO_INSTRUCTION__
  };
  
  std::string AsString(int type); // Convert the instruction type to a string like "val_copy"
};

#endif