#include "type_info.h"

namespace Type {
  std::string AsString(int type) {
    switch (type) {
    case VOID: return "void";
    case INT: return "int";
    case CHAR: return "char";
    case STRING: return "array(char)";
    case INT_ARRAY: return "array(int)";
    };
    return "unknown";
  }

  int InternalType(int type) {
    if (type == STRING) return CHAR;
    if (type == INT_ARRAY) return INT;
    return VOID;
  }

  bool IsArray(int type) {
    if (type == STRING || type == INT_ARRAY) return true;
    return false;
  }
};
