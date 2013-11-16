#include "ic.h"

void IC_Entry::PrintIC(ostream & ofs)
{
  stringstream out_line;

  // If there is a label, include it in the output.
  if (label != "") { out_line << label << ": "; }
  else { out_line << "  "; }

  // If there is an instruction, print it and all its arguments.
  if (inst != "") {
    out_line << inst << " ";
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
}

IC_Entry& IC_Array::AddLabel(string label_id, string cmt)
{
  IC_Entry * new_entry = new IC_Entry();
  new_entry->SetLabel(label_id);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}


IC_Entry& IC_Array::Add(string inst, int arg1, int arg2, int arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  if (arg1 >= 0) new_entry->AddScalar(arg1);
  if (arg2 >= 0) new_entry->AddScalar(arg2);
  if (arg3 >= 0) new_entry->AddScalar(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::Add(string inst, int arg1, int arg2, string arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  new_entry->AddScalar(arg1);
  new_entry->AddScalar(arg2);
  new_entry->AddConst(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::Add(string inst, int arg1, string arg2, int arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  new_entry->AddScalar(arg1);
  new_entry->AddConst(arg2);
  if (arg3 >= 0) new_entry->AddScalar(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::Add(string inst, int arg1, string arg2, string arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  new_entry->AddScalar(arg1);
  new_entry->AddConst(arg2);
  new_entry->AddConst(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::Add(string inst, string arg1, int arg2, int arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  new_entry->AddConst(arg1);
  if (arg2 >= 0) new_entry->AddScalar(arg2);
  if (arg3 >= 0) new_entry->AddScalar(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::Add(string inst, string arg1, int arg2, string arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  new_entry->AddConst(arg1);
  new_entry->AddScalar(arg2);
  new_entry->AddConst(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::Add(string inst, string arg1, string arg2, int arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  new_entry->AddConst(arg1);
  new_entry->AddConst(arg2);
  if (arg3 >= 0) new_entry->AddScalar(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::Add(string inst, string arg1, string arg2, string arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  new_entry->AddConst(arg1);
  new_entry->AddConst(arg2);
  new_entry->AddConst(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::AddArray(string inst, int arg1, int arg2, int arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  new_entry->AddArray(arg1);
  if (arg2 >= 0) new_entry->AddScalar(arg2);
  if (arg3 >= 0) new_entry->AddScalar(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::AddArray(string inst, int arg1, int arg2, string arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  new_entry->AddArray(arg1);
  new_entry->AddScalar(arg2);
  new_entry->AddConst(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::AddArray(string inst, int arg1, string arg2, int arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  new_entry->AddArray(arg1);
  new_entry->AddConst(arg2);
  if (arg3 >= 0) new_entry->AddScalar(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

IC_Entry& IC_Array::AddArray(string inst, int arg1, string arg2, string arg3, string cmt)
{
  IC_Entry * new_entry = new IC_Entry(inst);
  new_entry->AddArray(arg1);
  new_entry->AddConst(arg2);
  new_entry->AddConst(arg3);
  new_entry->SetComment(cmt);
  ic_array.push_back(new_entry);
  return *new_entry;
}

void IC_Array::PrintIC(ostream & ofs)
{
  for (int i = 0; i < (int) ic_array.size(); i++) {
    ic_array[i]->PrintIC(ofs);
  }
}
