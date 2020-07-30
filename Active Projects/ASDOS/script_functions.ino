void endOfScript() {
  digitalWrite(ERROR_LED_PIN,HIGH); delay(150);
  digitalWrite(ERROR_LED_PIN,LOW); delay(150);
  digitalWrite(ERROR_LED_PIN,HIGH); delay(150);
  digitalWrite(ERROR_LED_PIN,LOW);
  
  serPrintln("Script complete!");
  
  while(true) {}
}

void serPrintln(String val) { if (SERIAL_OUTPUT) { Serial.println(val); } }
void serPrint(String val) { if (SERIAL_OUTPUT) { Serial.print(val); } }

String splitString(String input_string, char delimiter, int position) {
  //Find the number of required elements in the output array
  int numberOfPieces = 0;
  for(int i = 0; i < input_string.length(); i++) { if (input_string[i] == delimiter) { numberOfPieces++; } }
  
  int lastIndex = 0; int counter = 0; String result[numberOfPieces + 1];
  for (int i = 0; i < input_string.length(); i++) {
    if (i == input_string.length() - 1) { result[numberOfPieces-1] = input_string.substring(lastIndex, i + 1); }
    
    // Loop through each character and check if it's a comma
    if (input_string[i] == delimiter) {
      result[counter] = input_string.substring(lastIndex, i);
      lastIndex = i + 1; counter++;
    }
  }
  
  return result[position];
}

void runCommand(String command) {
  command.replace("\t"," ");
  
  //Scan the entire command and get rid of any spaces at the start of it
  bool running = true;
  while (running) {
    if (command[0] != ' ') { running = false; } else { command.remove(0,1); }
  }
  
  //Scan the entire command and get rid of any doubled up spaces or anything after a "//" symbol
  int currentIndex = 0;
  while (currentIndex < command.length()) {
    if ((command[currentIndex] == ' ') and (command[currentIndex+1] == ' ')) {
      command = command.substring(0,currentIndex) + command.substring(currentIndex+1,command.length());
      currentIndex--;
    } else { currentIndex++; }
    
    if ((command[currentIndex] == '/') and (command[currentIndex+1] == '/')) {
      //We found commented code. Get rid of it
      command = command.substring(0,currentIndex);
      currentIndex = command.length();
    }
  }
  
  String spaceless_command = command; spaceless_command.replace(" ","");
  
  if (spaceless_command == "") {
    //Do nothing. We wanna just ignore the line if it's blank after removing all spaces, tabs and semicolons
  } else if ((spaceless_command == F("ASDOS.endCode")) or (spaceless_command == F("ASDOS.endCode()"))) {
    endOfScript();
  } else if (command.substring(0,9) == "ASDOS.pwm") {
    //ASDOS.pwm(pin,value);
    int pin = calculate(spaceless_command.substring(10,spaceless_command.indexOf(','))).toInt();
    int value = calculate(spaceless_command.substring(spaceless_command.indexOf(',')+1,endBracket(0,spaceless_command))).toFloat();
    
    Serial.println("Pin: " + String(pin) + "\t\t\tValue: " + String(value,8));
  } else if (spaceless_command.indexOf('=') > -1) {
    String variableName = spaceless_command.substring(0,spaceless_command.indexOf('='));
    String calculationResult = calculate(spaceless_command);
    serPrintln("Variable Name: " + variableName + "\t\tValue: " + calculationResult);
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else if (command == "__PLACEHOLDER__") {
    
  } else { SYSTEM_errorBlink(1, "FAST"); }
}
