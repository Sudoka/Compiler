#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

#include "type_info.h"

// This file contains all of the information about the symbol table.
//
// symbolTable : interacted with by the rest of the code to look up variables.
// tableEntry : all of the stored information about a single variable.

using namespace std;

class ASTNode_FunctionDefinition;
class symbolTable;
class IC_Array;

class tableEntry {
  friend class symbolTable;
protected:
  int type_id;       // What is the type of this variable?
  string name;       // Variable name used by sourcecode.
  bool is_temp;      // Is this variable just temporary (internal to compiler)
  int var_id;        // What is the intermediate code ID for this variable?
  int array_id;      // If this variable is an array index, which array?
  int index_id;      // If this variable is an array index, which index?
  vector<tableEntry * > args; // Arguments for functions
  
  bool is_function;  // Is this variable for a function
  ASTNode_FunctionDefinition * ast_node;

  tableEntry(int in_type) 
    : type_id (in_type)
    , name("__TEMP__")
    , is_temp(true)
    , var_id(-1)
    , array_id(-1)
    , index_id(-1)
    , is_function(false)
    , ast_node(NULL)
  {
  }

  tableEntry(int in_type, const string in_name)
    : type_id(in_type)
    , name(in_name)
    , is_temp(false)
    , var_id(-1)
    , array_id(-1)
    , index_id(-1)
    , is_function(false)
    , ast_node(NULL)
  {
  }

  tableEntry(int in_type, const string in_name, ASTNode_FunctionDefinition * ast_node_pointer)
    : type_id(in_type)
    , name(in_name)
    , is_temp(false)
    , var_id(-1)
    , array_id(-1)
    , index_id(-1)
    , is_function(true)
    , ast_node(ast_node_pointer)
  {
  }

  virtual ~tableEntry() { ; }

public:
  int GetType()        const { return type_id; }
  string GetName()     const { return name; }
  bool GetTemp()       const { return is_temp; }
  bool GetFunction()   const { return is_function; }
  int GetVarID()       const { return var_id; }
  int GetArrayID()     const { return array_id; }
  int GetIndexID()     const { return index_id; }
  void SetASTNode_FunctionDefinition(ASTNode_FunctionDefinition * fd) { ast_node = fd; }
  ASTNode_FunctionDefinition * GetASTNode_FunctionDefinition() const { return ast_node; }
  void AddArg(tableEntry * arg) { args.push_back(arg); }
  vector<tableEntry *> GetArgs() { return args; }
  void SetName(string in_name) { name = in_name; }
  void SetVarID(int in_id) { var_id = in_id; }
  void SetFunction(bool func) { is_function = func; }
  void SetArrayIndex(int a, int i) { array_id = a; index_id = i; }
};



class symbolTable {
private:
  map<string, tableEntry *> tbl_map;
  vector<vector<tableEntry *> *> scope_info;
  vector<tableEntry *> var_archive;
  int cur_scope;
  int next_var_id;   // Next variable ID to use.
  int next_label_id; // Next label ID to use.
  vector<string> while_end_stack; // End labels for while commands, in case of break

  // Figure out the next memory position to use.  Ideally, we should be
  // recycling these!!
  int GetNextID() { return ++next_var_id; }
public:
  symbolTable() : cur_scope(0), next_var_id(0), next_label_id(0) { 
    scope_info.push_back(new vector<tableEntry *>);
  }
  ~symbolTable() {
    while (cur_scope >= 0) DecScope();
    for (int i = 0; i < (int) var_archive.size(); i++) delete var_archive[i];
  }

  int GetSize() { return tbl_map.size(); }

  void IncScope() {
    scope_info.push_back(new vector<tableEntry *>);
    cur_scope++;
  }

  void DecScope() {
    // Remove variables in the old scope and store them in the archive.
    vector<tableEntry *> * old_scope = scope_info.back();
    scope_info.pop_back();
    var_archive.insert(var_archive.end(), old_scope->begin(), old_scope->end());

    // Make sure to clean up the tbl_map.
    for (int i = 0; i < (int) old_scope->size(); i++) {
      tbl_map.erase((*old_scope)[i]->GetName());
    }

    delete old_scope;
    cur_scope--;
  }

  int NextLabelID() { return next_label_id++; }
  string NextLabelID(string prefix) {
    stringstream sstm;
    sstm << prefix << next_label_id++;
    return sstm.str();
  }
  
  void ResetLabelID() { next_label_id = 0; }

  int GetWhileDepth() { return (int) while_end_stack.size(); }
  void PushWhileEndLabel(const string & end_label) { while_end_stack.push_back(end_label); }
  const string & GetWhileEndLabel() { return while_end_stack.back(); }
  void PopWhileEndLabel() { while_end_stack.pop_back(); }
      
  // Lookup will find an entry and return it.  If that entry is not in the table, it will return NULL
  tableEntry * Lookup(string in_name) {
    if (tbl_map.find(in_name) == tbl_map.end()) return NULL;
    return tbl_map[in_name];
  }

  // Insert an entry into the symbol table.
  tableEntry * AddEntry(int in_type, string in_name) {
    tableEntry * new_entry = new tableEntry(in_type, in_name);
    new_entry->SetVarID( GetNextID() );
    tbl_map[in_name] = new_entry;
    scope_info[cur_scope]->push_back(new_entry);
    return new_entry;
  }

  // Insert a temp variable entry into the symbol table.
  tableEntry * AddTempEntry(int in_type) {
    tableEntry * new_entry = new tableEntry(in_type);
    new_entry->SetVarID( GetNextID() );
    return new_entry;
  }

  // Insert a function entry into the symbol table.
  tableEntry * AddFunction(int in_type, string in_name) {
    tableEntry * new_entry = new tableEntry(in_type, in_name, NULL);
    new_entry->SetVarID( GetNextID() );
    tbl_map[in_name] = new_entry;
    scope_info[cur_scope]->push_back(new_entry);
    return new_entry;
  }

  vector<tableEntry *> getFunctions()
  {
    vector<tableEntry *> functions;

    map<string, tableEntry *>::iterator it;
				for (it = tbl_map.begin(); it != tbl_map.end(); ++it)
				{
						tableEntry * entry = it->second;
						if ( entry != NULL && entry->GetFunction() &&  entry->GetASTNode_FunctionDefinition() != NULL )
						{
								functions.push_back(entry);
						}
				}

				return functions;
  }

  // Don't create a full variable; just get an unused variable ID.
  int GetTempVarID() { return GetNextID(); }
  void FreeTempVarID(int id) { (void) id; /* Nothing for now... */ }

  void RemoveEntry(tableEntry * del_var) {
    // @CAO should remove this entry from the table?
    delete del_var;
  }
};

#endif
