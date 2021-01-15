//This is the variable manager. It relies HEAVILY on the file_functions code to operate

void createVariable(String variableName,String variableType) {
  if (SD.exists("_ASDOS/runVars/" + variableType)) {
    writeall("_ASDOS/runVars/" + variableType + "/" + variableName + ".var");
  } else { SYSTEM_errorBlink(5,"MEDIUM"); }
}

void createVariableList(String variableName,String variableType) {
  if (SD.exists("_ASDOS/runVars/" + variableType)) {
    writeall("_ASDOS/runVars/" + variableType + "/" + variableName + ".lst");
  } else { SYSTEM_errorBlink(5,"MEDIUM"); }
}

void setVariable(String variableName,String variableType, String data) { writeall("_ASDOS/runVars/" + variableType + "/" + variableName + ".var",data); }
void setList(String variableName,String variableType, String data) { writeall("_ASDOS/runVars/" + variableType + "/" + variableName + ".lst",data); }

void destroyVariable(String variableName,String variableType) { SD.remove("_ASDOS/runVars/" + variableType + "/" + variableName + ".var"); }
void destroyList(String variableName,String variableType) { SD.remove("_ASDOS/runVars/" + variableType + "/" + variableName + ".lst"); }

bool doesVariableExist(String variableDirectory) { return SD.exists(variableDirectory); }
bool doesVariableExist(String variableName,String variableType) { return SD.exists("_ASDOS/runVars/" + variableType + "/" + variableName + ".var"); }
bool doesListExist(String variableName,String variableType) { return SD.exists("_ASDOS/runVars/" + variableType + "/" + variableName + ".lst"); }

String getVariable(String variableName,String variableType) {
  if (doesVariableExist("_ASDOS/runVars/" + variableType + "/" + variableName + ".var") == false) { SYSTEM_errorBlink(5,"MEDIUM"); }
  return readall("_ASDOS/runVars/" + variableType + "/" + variableName + ".var");
}

String getList(String variableName,String variableType) {
  if (doesVariableExist("_ASDOS/runVars/" + variableType + "/" + variableName + ".lst") == false) { SYSTEM_errorBlink(5,"MEDIUM"); }
  return readall("_ASDOS/runVars/" + variableType + "/" + variableName + ".lst");
}
