#include "instr_info.h"

namespace Instr {
  std::string AsString(int instr_type) {
    switch (instr_type) {
    case VAL_COPY: return "val_copy";
    case OUT_INT: return "out_int";
    case OUT_CHAR: return "out_char";
    case AR_SET_SIZ: return "ar_set_siz";
    case AR_SET_IDX: return "ar_set_idx";
    case AR_GET_IDX: return "ar_get_idx";
    case AR_GET_SIZ: return "ar_get_siz";
    case TEST_EQU: return "test_equ";
    case TEST_NEQU: return "test_nequ";
    case TEST_GTR: return "test_gtr";
    case TEST_GTE: return "test_gte";
    case TEST_LESS: return "test_less";
    case TEST_LTE: return "test_lte";
    case JUMP: return "jump";
    case JUMP_IF_N0: return "jump_if_n0";
    case JUMP_IF_0: return "jump_if_0";
    case ADD: return "add";
    case MULT: return "mult";
    case SUB: return "sub";
    case DIV: return "div";
    case MOD: return "mod";
    case RANDOM: return "random";
    case NOP: return "nop";
    case PUSH: return "push";
    case POP: return "pop";
    case __NO_INSTRUCTION__: return "";
    };
    return "unknown";
  }
};
