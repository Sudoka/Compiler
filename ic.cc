#include "ic.h"

void IC_Entry::PrintTC(symbolTable & table, ofstream & ofs)
{ 
  stringstream out_line;

  // If there is a label, include it in the output.
  if (label != "") { out_line << label << ": "; }
  else { out_line << "### Converting: "; }

  // If there is an instruction, print it and all its arguments.
  if (instr_type != Instr::__NO_INSTRUCTION__) {
    out_line << Instr::AsString(instr_type) << " ";
    for (int i = 0; i < (int) args.size(); i++) {
      out_line << args[i]->AsString() << " ";
    }
  }

  // If there is a comment, print it!
  if (comment != "") {
    while (out_line.str().size() < 40) out_line << " "; // Align comments for easy reading.
    out_line << "# " << comment;
  }

  ofs << out_line.str() << endl;
  
  switch (instr_type) {
    case Instr::VAL_COPY: return PrintTC_Val_Copy(ofs);
    case Instr::OUT_INT: return PrintTC_Out_Int(ofs);
    case Instr::OUT_CHAR: return PrintTC_Out_Char(ofs);
    case Instr::AR_SET_SIZ: return PrintTC_Ar_Set_Siz(table, ofs);
    case Instr::AR_SET_IDX: return PrintTC_Ar_Set_Idx(ofs);
    case Instr::AR_GET_IDX: return PrintTC_Ar_Get_Idx(ofs);
    case Instr::AR_GET_SIZ: return PrintTC_Ar_Get_Siz(ofs);
    case Instr::TEST_EQU: return PrintTC_Test_Equ(ofs);
    case Instr::TEST_NEQU: return PrintTC_Test_Nequ(ofs);
    case Instr::TEST_GTR: return PrintTC_Test_Gtr(ofs);
    case Instr::TEST_GTE: return PrintTC_Test_Gte(ofs);
    case Instr::TEST_LESS: return PrintTC_Test_Less(ofs);
    case Instr::TEST_LTE: return PrintTC_Test_Lte(ofs);
    case Instr::JUMP: return PrintTC_Jump(ofs);
    case Instr::JUMP_IF_N0: return PrintTC_Jump_If_N0(ofs);
    case Instr::JUMP_IF_0: return PrintTC_Jump_If_0(ofs);
    case Instr::ADD: return PrintTC_Add(ofs);
    case Instr::MULT: return PrintTC_Mult(ofs);
    case Instr::SUB: return PrintTC_Sub(ofs);
    case Instr::DIV: return PrintTC_Div(ofs);
    case Instr::MOD: return PrintTC_Mod(ofs);
    case Instr::RANDOM: return PrintTC_Random(ofs);
    case Instr::__NO_INSTRUCTION__:
    default: return;
  };
}

void IC_Entry::PrintTC_Val_Copy(ofstream & ofs)
{
	if (args[0]->IsScalar())
	{
		ofs << "  load " << args[0]->GetID() << " regA" << endl;
		ofs << "  val_copy " << "regA regB" << endl;
	}
	else if (args[0]->IsConst() && args[1]->IsScalar())
	{
		ofs << "  val_copy " << args[0]->AsString() << " regB" << endl;
	}
	ofs << "  store regB " << args[1]->GetID() << endl;
};
  
void IC_Entry::PrintTC_Out_Int(ofstream & ofs)
{
  if (args[0]->IsScalar())
  {
    ofs << "  load " << args[0]->GetID() << " regA" << endl;
    ofs << "  out_int regA" << endl;
  }
};
  
void IC_Entry::PrintTC_Out_Char(ofstream & ofs)
{
  if (args[0]->IsScalar())
  {
    ofs << "  load " << args[0]->GetID() << " regA" << endl;
    ofs << "  out_char regA" << endl;
  }
  else if (args[0]->IsConst())
  {
    ofs << "  out_char " << args[0]->AsString() << endl;
  }
};
  
void IC_Entry::PrintTC_Ar_Set_Siz(symbolTable & table, ofstream & ofs)
{
  if (args[0]->IsArray())
  {
    string ar_resize_do_copy = table.NextLabelID("ar_resize_do_copy_");
    string ar_resize_start = table.NextLabelID("ar_resize_start_");
    string ar_resize_end = table.NextLabelID("ar_resize_end_");
  
    ofs << "  load " << args[0]->GetID() << " regA" << endl;
    
    if (args[1]->IsScalar())
    {
       ofs << "  load " << args[1]->GetID() << " regB" << endl;
    }
    else if (args[1]->IsConst())
    {
      ofs << "  val_copy " << args[1]->AsString() << " regB" << endl;
    }
    
    ofs << "  val_copy 0 regC                       # Default old array size to 0 if uninitialized." << endl;
    ofs << "  jump_if_0 regA " << ar_resize_do_copy << endl;
    ofs << "  load regA regC                        # Load old array size into regC" << endl;
    ofs << "  test_gtr regB regC regD               # regD = new_size > old_size?" << endl;
    ofs << "  jump_if_n0 regD " << ar_resize_do_copy << endl;
    ofs << "  store regB regA                       # Otherwise, replace old size w/ new size.  Done." << endl;
    ofs << "  jump " << ar_resize_end << endl;
    ofs << ar_resize_do_copy << ":" << endl;
    ofs << "  load 0 regD                           # Set regD = free mem position" << endl;
    ofs << "  store regD " << args[0]->GetID() << endl;
    ofs << "  store regB regD                       # Store new size at new array start" << endl;
    ofs << "  add regD 1 regE                       # Set regE = first pos. in new array" << endl;
    ofs << "  add regE regB regE                    # Set regE = new free mem position" << endl;
    ofs << "  store regE 0                          # Store new free memory at pos. zero" << endl;
    ofs << "  add regA regC regE                    # Set regE = the last index to be copied" << endl;
    ofs << ar_resize_start << ":" << endl;
    ofs << "  add regA 1 regA                       # Increment pointer for FROM array" << endl;
    ofs << "  add regD 1 regD                       # Increment pointer for TO array" << endl;
    ofs << "  test_gtr regA regE regF               # If we are done copying, jump to end of loop" << endl;
    ofs << "  jump_if_n0 regF " << ar_resize_end << endl;
    ofs << "  mem_copy regA regD                    # Copy the current index." << endl;
    ofs << "  jump " << ar_resize_start << endl;
    ofs << ar_resize_end << ":" << endl;
  }
};
  
void IC_Entry::PrintTC_Ar_Set_Idx(ofstream & ofs)
{
  if (args[0]->IsArray())
  {
  	ofs << "  load " << args[0]->GetID() << " regA" << endl;
  	
  	if (args[1]->IsScalar())
  	{
  	  ofs << "  load " << args[1]->GetID() << " regB" << endl;
  	}
  	else if (args[1]->IsConst())
  	{
  	  ofs << "  val_copy " << args[1]->AsString() << " regB" << endl;
  	}
  	
  	if (args[2]->IsScalar())
  	{
  	  ofs << "  load " << args[2]->GetID() << " regC" << endl;
  	}
  	else if (args[2]->IsConst())
  	{
  	  ofs << "  val_copy " << args[2]->AsString() << " regC" << endl;
  	}
  	
  	ofs << "  add regA 1 regA" << endl;
  	ofs << "  add regA regB regA" << endl;
  	ofs << "  store regC regA" << endl;
  }
};
  
void IC_Entry::PrintTC_Ar_Get_Idx(ofstream & ofs)
{
  if (args[0]->IsArray() && args[1]->IsScalar() && args[2]->IsScalar())
  {
  	ofs << "  load " << args[0]->GetID() << " regA" << endl;
  	ofs << "  load " << args[1]->GetID() << " regB" << endl;
  	ofs << "  add regA 1 regA" << endl;
  	ofs << "  add regA regB regA" << endl;
  	ofs << "  load regA regC" << endl;
  	ofs << "  store regC " << args[2]->GetID() << endl;
  }
};
  
void IC_Entry::PrintTC_Ar_Get_Siz(ofstream & ofs)
{
  if (args[0]->IsArray() && args[1]->IsScalar())
  {
  	ofs << "  load " << args[0]->GetID() << " regA" << endl;
  	ofs << "  load regA regB" << endl;
  	ofs << "  store regB " << args[1]->GetID() << endl;
  }
};
  
void IC_Entry::PrintTC_Test_Equ(ofstream & ofs)
{
  if (args[0]->IsScalar() && args[2]->IsScalar())
	{
	  ofs << "  load " << args[0]->GetID() << " regA" << endl;
   if (args[1]->IsScalar())
   {
     ofs << "  load " << args[1]->GetID() << " regB" << endl;
     ofs << "  test_equ regA regB regC" << endl; 
   }
   else if (args[1]->IsConst())
   {
     ofs << "  test_equ regA " << args[1]->AsString() << " regC" << endl; 
   }
    ofs << "  store regC " << args[2]->GetID() << endl;
	}
};
  
void IC_Entry::PrintTC_Test_Nequ(ofstream & ofs)
{
  if (args[0]->IsScalar() && args[2]->IsScalar())
	{
	  ofs << "  load " << args[0]->GetID() << " regA" << endl;
   if (args[1]->IsScalar())
   {
     ofs << "  load " << args[1]->GetID() << " regB" << endl;
     ofs << "  test_nequ regA regB regC" << endl; 
   }
   else if (args[1]->IsConst())
   {
     ofs << "  test_nequ regA " << args[1]->AsString() << " regC" << endl; 
   }
   ofs << "  store regC " << args[2]->GetID() << endl;
	}

};
  
void IC_Entry::PrintTC_Test_Gtr(ofstream & ofs)
{
	if (args[0]->IsScalar() && args[2]->IsScalar())
	{
	  ofs << "  load " << args[0]->GetID() << " regA" << endl;
   if (args[1]->IsScalar())
   {
     ofs << "  load " << args[1]->GetID() << " regB" << endl;
     ofs << "  test_gtr regA regB regC" << endl; 
   }
   else if (args[1]->IsConst())
   {
     ofs << "  test_gtr regA " << args[1]->AsString() << " regC" << endl; 
   }
    ofs << "  store regC " << args[2]->GetID() << endl;
	}
};
  
void IC_Entry::PrintTC_Test_Gte(ofstream & ofs)
{
  if (args[0]->IsScalar() && args[2]->IsScalar())
	{
	  ofs << "  load " << args[0]->GetID() << " regA" << endl;
   if (args[1]->IsScalar())
   {
     ofs << "  load " << args[1]->GetID() << " regB" << endl;
     ofs << "  test_gte regA regB regC" << endl; 
   }
   else if (args[1]->IsConst())
   {
     ofs << "  test_gte regA " << args[1]->AsString() << " regC" << endl; 
   }
    ofs << "  store regC " << args[2]->GetID() << endl;
	}
};
  
void IC_Entry::PrintTC_Test_Less(ofstream & ofs)
{
	if (args[0]->IsScalar() && args[2]->IsScalar())
	{
		ofs << "  load " << args[0]->GetID() << " regA" << endl;
		 if (args[1]->IsScalar())
   {
     ofs << "  load " << args[1]->GetID() << " regB" << endl;
     ofs << "  test_less regA regB regC" << endl; 
   }
   else if (args[1]->IsConst())
   {
     ofs << "  test_less regA " << args[1]->AsString() << " regC" << endl; 
   }
    ofs << "  store regC " << args[2]->GetID() << endl;
	}
};
  
void IC_Entry::PrintTC_Test_Lte(ofstream & ofs)
{
  if (args[0]->IsScalar() && args[2]->IsScalar())
	{
	  ofs << "  load " << args[0]->GetID() << " regA" << endl;
   if (args[1]->IsScalar())
   {
     ofs << "  load " << args[1]->GetID() << " regB" << endl;
     ofs << "  test_lte regA regB regC" << endl; 
   }
   else if (args[1]->IsConst())
   {
     ofs << "  test_lte regA " << args[1]->AsString() << " regC" << endl; 
   }
    ofs << "  store regC " << args[2]->GetID() << endl;
	}
};
  
void IC_Entry::PrintTC_Jump(ofstream & ofs)
{
  if (args[0]->IsConst())
  {
  	ofs << "  jump " << args[0]->AsString() << endl;
  }
};
  
void IC_Entry::PrintTC_Jump_If_N0(ofstream & ofs)
{
	if (args[0]->IsScalar() && args[1]->IsConst())
	{
  	ofs << "  load " << args[0]->GetID() << " regA" << endl;
  	ofs << "  jump_if_n0 regA " << args[1]->AsString() << endl;
  }
};
  
void IC_Entry::PrintTC_Jump_If_0(ofstream & ofs)
{
	if (args[0]->IsScalar() && args[1]->IsConst())
	{
  	ofs << "  load " << args[0]->GetID() << " regA" << endl;
  	ofs << "  jump_if_0 regA " << args[1]->AsString() << endl;
  }
};
  
void IC_Entry::PrintTC_Add(ofstream & ofs)
{
  if (args[0]->IsScalar() && args[2]->IsScalar())
	{
	  ofs << "  load " << args[0]->GetID() << " regA" << endl;
	  
	  if (args[1]->IsScalar())
	  {
    	ofs << "  load " << args[1]->GetID() << " regB" << endl;
    	ofs << "  add regA regB regC" << endl; 
    }
    else if (args[1]->IsConst())
    {
    	ofs << "  add regA " << args[1]->AsString() << " regC" << endl; 
    }
    
    ofs << "  store regC " << args[2]->GetID() << endl;
	}
};
  
void IC_Entry::PrintTC_Mult(ofstream & ofs)
{
  if (args[0]->IsScalar() && args[2]->IsScalar())
	{
	  ofs << "  load " << args[0]->GetID() << " regA" << endl;
    
    if (args[1]->IsScalar())
	  {
    	ofs << "  load " << args[1]->GetID() << " regB" << endl;
    	ofs << "  mult regA regB regC" << endl; 
    }
    else if (args[1]->IsConst())
    {
    	ofs << "  mult regA " << args[1]->AsString() << " regC" << endl; 
    }
    
    ofs << "  store regC " << args[2]->GetID() << endl;
	}
};
  
void IC_Entry::PrintTC_Sub(ofstream & ofs)
{
  if (args[0]->IsScalar() && args[2]->IsScalar())
	{
	  ofs << "  load " << args[0]->GetID() << " regA" << endl;
    
    if (args[1]->IsScalar())
	  {
    	ofs << "  load " << args[1]->GetID() << " regB" << endl;
    	ofs << "  sub regA regB regC" << endl; 
    }
    else if (args[1]->IsConst())
    {
    	ofs << "  sub regA " << args[1]->AsString() << " regC" << endl; 
    }
    
    ofs << "  store regC " << args[2]->GetID() << endl;
	}
};
  
void IC_Entry::PrintTC_Div(ofstream & ofs)
{
  if (args[0]->IsScalar() && args[2]->IsScalar())
	{
	  ofs << "  load " << args[0]->GetID() << " regA" << endl;
   
   	if (args[1]->IsScalar())
	  {
    	ofs << "  load " << args[1]->GetID() << " regB" << endl;
    	ofs << "  div regA regB regC" << endl; 
    }
    else if (args[1]->IsConst())
    {
    	ofs << "  div regA " << args[1]->AsString() << " regC" << endl; 
    }
    
    ofs << "  store regC " << args[2]->GetID() << endl;
	}
};
  
void IC_Entry::PrintTC_Mod(ofstream & ofs)
{
  if (args[0]->IsScalar() && args[2]->IsScalar())
	{
	  ofs << "  load " << args[0]->GetID() << " regA" << endl;
    
    if (args[1]->IsScalar())
	  {
    	ofs << "  load " << args[1]->GetID() << " regB" << endl;
    	ofs << "  mod regA regB regC" << endl; 
    }
    else if (args[1]->IsConst())
    {
    	ofs << "  mod regA " << args[1]->AsString() << " regC" << endl; 
    }
     
    ofs << "  store regC " << args[2]->GetID() << endl;
	}
};
  
void IC_Entry::PrintTC_Random(ofstream & ofs)
{
  if (args[0]->IsScalar() && args[1]->IsScalar())
  {
  	ofs << "  load " << args[0]->GetID() << " regA" << endl;
  	ofs << "  random regA regB" << endl;
  	ofs << "  store regB " << args[1]->GetID() << endl;
  }
};
  
IC_Entry& IC_Array::AddLabel(string label_id, string cmt)
{
  IC_Entry * new_entry = new IC_Entry();
  new_entry->SetLabel(label_id);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::Add(int inst, int arg1, int arg2, int arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  if (arg1 >= 0) new_entry->AddScalar(arg1);
  if (arg2 >= 0) new_entry->AddScalar(arg2);
  if (arg3 >= 0) new_entry->AddScalar(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::Add(int inst, int arg1, int arg2, string arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  new_entry->AddScalar(arg1);
  new_entry->AddScalar(arg2);
  new_entry->AddConst(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::Add(int inst, int arg1, string arg2, int arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  new_entry->AddScalar(arg1);
  new_entry->AddConst(arg2);
  if (arg3 >= 0) new_entry->AddScalar(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::Add(int inst, int arg1, string arg2, string arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  new_entry->AddScalar(arg1);
  new_entry->AddConst(arg2);
  new_entry->AddConst(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::Add(int inst, string arg1, int arg2, int arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  new_entry->AddConst(arg1);
  if (arg2 >= 0) new_entry->AddScalar(arg2);
  if (arg3 >= 0) new_entry->AddScalar(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::Add(int inst, string arg1, int arg2, string arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  new_entry->AddConst(arg1);
  new_entry->AddScalar(arg2);
  new_entry->AddConst(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::Add(int inst, string arg1, string arg2, int arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  new_entry->AddConst(arg1);
  new_entry->AddConst(arg2);
  if (arg3 >= 0) new_entry->AddScalar(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::Add(int inst, string arg1, string arg2, string arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  new_entry->AddConst(arg1);
  new_entry->AddConst(arg2);
  new_entry->AddConst(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::AddArray(int inst, int arg1, int arg2, int arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  new_entry->AddArray(arg1);
  if (arg2 >= 0) new_entry->AddScalar(arg2);
  if (arg3 >= 0) new_entry->AddScalar(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::AddArray(int inst, int arg1, int arg2, string arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  new_entry->AddArray(arg1);
  new_entry->AddScalar(arg2);
  new_entry->AddConst(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::AddArray(int inst, int arg1, string arg2, int arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  new_entry->AddArray(arg1);
  new_entry->AddConst(arg2);
  if (arg3 >= 0) new_entry->AddScalar(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::AddArray(int inst, int arg1, string arg2, string arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  new_entry->AddArray(arg1);
  new_entry->AddConst(arg2);
  new_entry->AddConst(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

void IC_Array::PrintTC(symbolTable & table, ofstream & ofs)
{
  table.ResetLabelID();
  
  int next_free_memory_loc = table.GetTempVarID();
  ofs << "  store " << next_free_memory_loc << " 0" << endl;
  table.FreeTempVarID(next_free_memory_loc);
  
  for (int i = 0; i < (int) ic_array.size(); i++) {
    ic_array[i]->PrintTC(table, ofs);
  }
}
