#include "hardware.h"

void cHardware::AddInst(cInst_Base * inst)
{
  inst->SetHardware(this);
  inst_vector.push_back(inst);
}

void cHardware::AddLabel(string _l)
{
  if (label_map.find(_l) != label_map.end()) {
    cout << "Warning: label '" << _l << "' being reused!" << endl;
  }
  label_map[_l] = (int) inst_vector.size(); // The current size represents the value of the next line.
}

int cHardware::FindLabel(string _l)
{
  if (label_map.find(_l) == label_map.end()) {
    string error_str = "Unknown label '";
    error_str += _l;
    error_str += "'";
    Error(error_str);
  }
  return label_map[_l];
}


bool cHardware::Run()
{
  while (IP >= 0 && IP < (int) inst_vector.size()) {
    advance_IP = true;  // Advance the instruction pointer after execution unless turned off.

    inst_vector[IP]->Run();
    exe_count++;

    if (timeout >= 0 && exe_count >= timeout) {
      cout << "Reached execution count limit of " << timeout << ".  Halting." << endl;
      exit(0);
    }

    if (advance_IP) IP++;
  }

  return true;
}
