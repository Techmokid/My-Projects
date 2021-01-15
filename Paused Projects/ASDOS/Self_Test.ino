bool closeEnough(String in, String targetValue, float acceptable_diff) { return closeEnough(in.toFloat(), targetValue.toFloat(), acceptable_diff); }
bool closeEnough(String in, float targetValue, float acceptable_diff) { return closeEnough(in.toFloat(), targetValue, acceptable_diff); }
bool closeEnough(float in, String targetValue, float acceptable_diff) { return closeEnough(in, targetValue.toFloat(), acceptable_diff); }
bool closeEnough(float in, float targetValue, float acceptable_diff) {
  return ((in < targetValue + acceptable_diff) and (in > targetValue - acceptable_diff));
}

bool self_test() {
  serPrintln("");
  
  bool success = true;
  
  //Here we wanna test every command at least once to test if it works correctly
  serPrintln(F("------------------------------------------------- ASDOS Self Test -------------------------------------------------"));
  
  //These lines test the calculation function and pushes it to it's limits
  if (closeEnough(calculate(F("7.7/8.2*5.9+2/cos(3+7/4*5+sin(5.1-2*(1+4.2))-2.64)-5/(12+6/4-6.24*(18.4-7))")),3.325667,0.000001)) {
    serPrintln(F("PASS - Internal Mathematics Check"));
  } else { serPrintln(F("FAIL - Internal Mathematics Check")); success = false; }
  
  //These lines test variable creation, modification, and deletion
  success = success and checkVar(F("Bool"));
  success = success and checkVar(F("Int"));
  success = success and checkVar(F("Float"));
  success = success and checkVar(F("String"));
  
  serPrintln(F("-------------------------------------------------------------------------------------------------------------------"));
  return success;
}

bool checkVar(String variableType) {
  bool result = true;
  
  createVariable(F("_ASDOS"),variableType);
  if (!doesVariableExist(F("_ASDOS"),variableType)) { serPrint(F("FAIL - ")); serPrint(variableType); serPrint(F(" Variable Declaration\t\t\tSUBFAILURE - Variable Creation")); result = false; }
  
  setVariable(F("_ASDOS"),variableType,F("THIS IS AN ASDOS SYSTEM SELF-TEST"));
  if (getVariable(F("_ASDOS"),variableType) != F("THIS IS AN ASDOS SYSTEM SELF-TEST")) {
    serPrintln(F("FAIL - ")); serPrint(variableType); serPrint(F(" Variable Declaration\t\t\tSUBFAILURE - Variable Set/Read")); result = false; }
  
  destroyVariable(F("_ASDOS"),variableType);
  if (doesVariableExist(F("_ASDOS"),variableType)) { serPrint(F("FAIL - ")); serPrint(variableType); serPrint(F(" Variable Declaration\t\t\tSUBFAILURE - Variable Destruction")); result = false; }
  
  if (result) { serPrint(F("PASS - ")); serPrint(variableType); serPrint(F(" Variable Declaration\n")); }
  return result;
}
