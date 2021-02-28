//Serial.println("Result: " + calculate("7.7/8.2*5.9+2/cos(3+7/4*5+sin(5.1-2*(1+4.2))-2.64)-5/(12+6/4-6.24*(18.4-7))"));
  
void setup() {
  Serial.begin(115200);
  Serial.println("RESULT: " + calculate("2/cos(3+7/4*5+sin(5.1-2*(1+4.2))-2.64)"));
}

void loop() { }

String calculate(String string) {
  //Here we wanna essentially get rid of anything that isn't the calculation itself
  string.replace(" ",""); string.replace("\n",""); string.replace(";",""); //Remove invalid characters
  if (string.indexOf('=') > -1) { string = string.substring(string.indexOf('=') + 1,string.length()); } //return everything after the equals sign
  string.toLowerCase();
  
  string = detectFunctions(string);
  Serial.println(string);
  string = calculateBrackets(string);
  return finalCalculation(string);
}

String calculateBrackets(String in) {
  //This will trigger to calculate any brackets already existing to make the compiling process much faster and simpler
  //"7+6/5+2*(4-3)+2*(4+8*(2-3)+7*(2+4))" should become "7+6/5+2*1+2*38"
  //Should also be able to handle "2*(4+8*(2-3)+7*())"
 
  while (in.indexOf('(') > -1) {
    //We wanna find the deepest recursion of brackets until there are none left
    int index = 0;
    int deepestIndex = 0;
    int deepestIndexBracketStart = 0;
    for (int i = 0; i < in.length(); i++) {
      if (in[i] == '(') {
        index++;
        if ((i > deepestIndexBracketStart) and (index > deepestIndex)) { deepestIndexBracketStart = i; deepestIndex = index; }
      } else if (in[i] == ')') { index--; }
    }
    
    int deepestIndexBracketEnd = 0;
    int i = deepestIndexBracketStart;
    while (true) { if (in[i] == ')') { deepestIndexBracketEnd = i; break; } i++; }
    
    //We have found the deepest recursion. Now work backwards to calculate each bracket one by one
    in = in.substring(0,deepestIndexBracketStart) + finalCalculation(in.substring(deepestIndexBracketStart + 1,deepestIndexBracketEnd)) + in.substring(deepestIndexBracketEnd + 1,in.length());
  }
  
  return in;
}

int count_chars(String string, char ch) { int count = 0; for(int i = 0; i < string.length(); i++) { if (string[i] == ch) { count++; } } return count; }

String getNextNumber(String in, int symbolIndex) {
  bool running = true;
  String result = "";
  
  //FirstDigitCheck allows us to skip the first digit and always assume it's part of the number (Because of negative numbers)
  bool firstDigitCheck = true;
  for (int i = symbolIndex + 1; running; i++) {
    if (i > symbolIndex + 1) { firstDigitCheck = false; }
    
    if ((in[i] != '.') and (!isDigit(in[i])) and (!firstDigitCheck)) {
      running = false;
    } else { result += in[i]; }
    
    if (i == in.length()) { running = false; }
  }
  
  return result;
}

String getPrevNumber(String in, int symbolIndex) {
  bool running = true;
  String result = "";
  for (int i = symbolIndex - 1; running; i--) {
    if ((in[i] != '.') and (!isDigit(in[i]))) {
      // Give an exception for negative numbers.
      // The if(i != 0) check allows us to also completely ignore the next digit in our checks and presume it's part of the formula.
      // This prevents bugs if the first digit is a negative number (Difficult problem to solve later on down the line)
      if (i != 0) {
        if ((in[i] == '-') and ((in[i-1] == '/') or (in[i-1] == '*') or (in[i-1] == '+') or (in[i-1] == '-'))) { result = in[i] + result; }
      } else { result = in[i] + result; }
      running = false;
    } else {
      result = in[i] + result;
    }
    
    if (i == 0) { running = false; }
  }
  
  return result;
}

String finalCalculation(String in) {
  // Here is where we finally do the calculation. All brackets have been taken care of, all invalid characters have been removed. Now all we need is to finally finish it up
  // We should get on something like "7+8/9*4-2+9" and be able to equate it in two steps using getPreviousNumber() to help us
  // Step 1, multiplication and division: "7+8/9*4-2+9" becomes: "7+3.55555555555556-2+9"
  // Step 2, addition and subtraction: "7+3.55555555555556-2+9" becomes "17.55555555555556" plus or minus some error due to floating point precision
  
  //Step 1
  for (int i = 0; i < in.length(); i++) {
    if (in[i] == '*') {
      String a = getPrevNumber(in,i); String b = getNextNumber(in,i);
      int index = in.indexOf(a+"*"+b);
      
      in = in.substring(0,index) + String(a.toFloat()*b.toFloat(),8) + in.substring(index+a.length()+b.length()+1,in.length());
      i = index;
    } else if (in[i] == '/') {
      String a = getPrevNumber(in,i); String b = getNextNumber(in,i);
      int index = in.indexOf(a+"/"+b);
      
      in = in.substring(0,index) + String(a.toFloat()/b.toFloat(),8) + in.substring(index+a.length()+b.length()+1,in.length());
      i = index;
    }
  }
  
  for (int i = 0; i < in.length(); i++) {
    if (in[i] == '+') {
      String a = getPrevNumber(in,i); String b = getNextNumber(in,i);
      int index = in.indexOf(a+"+"+b);
      
      in = in.substring(0,index) + String(a.toFloat()+b.toFloat(),8) + in.substring(index+a.length()+b.length()+1,in.length());
      i = index;
    } else if (in[i] == '-') {
      String a = getPrevNumber(in,i); String b = getNextNumber(in,i);
      int index = in.indexOf(a+"-"+b);
      
      in = in.substring(0,index) + String(a.toFloat()-b.toFloat(),8) + in.substring(index+a.length()+b.length()+1,in.length());
      i = index;
    }
  }
  
  return in;
}

String purgeAndCleanString(String in) {
  String result = "";
  for (int i = 0; i < in.length(); i++) { if (32 <= in[i] <= 126) { result += in[i]; } }
  return result;
}

bool containsLetter(String in) {
  for (int i = 0; i < in.length(); i++) {
    if ((in[i] >= 65) && (in[i] <= 90)) { return true; }
    if ((in[i] >= 97) && (in[i] <= 122)) { return true; }
  }
  
  return false;
}

int endBracket(int position, String in) {
  int bracketCount = 0;
  for (int i = position; i < in.length(); i++) {
    if (in[i] == '(') {
      bracketCount++;
    } else if (in[i] == ')') {
      bracketCount--;
      if (bracketCount == 0) { return i; }
    }
    
    //This if statement should never be called, but it's there to handle wrong syntax
    if (bracketCount < 0) { return -1; }
  }
  
  if (bracketCount == 0) { return 0; }
  return -1;
}

String detectFunctions(String in) {
  //Just before we go ahead and start calculating anything, we wanna detect any special (trigonometric or user defined) functions
  //2*cos(4+5) should be done in 2 steps.
  //2*cos(9)
  //2*-.91113
  //-1.82226
  
  while(containsLetter(in)) {
    int positionToCheck = in.indexOf("sin");
    if (positionToCheck != -1) {
      int endBracketIndex = endBracket(positionToCheck,in);
      float solution = sin(calculate(in.substring(positionToCheck + 4,endBracketIndex)).toFloat());
      in = in.substring(0,positionToCheck) + String(solution,8) + in.substring(endBracketIndex+1,in.length());
    }
    
    positionToCheck = in.indexOf("cos");
    if (positionToCheck != -1) {
      int endBracketIndex = endBracket(positionToCheck,in);
      float solution = cos(calculate(in.substring(positionToCheck + 4,endBracketIndex)).toFloat());
      in = in.substring(0,positionToCheck) + String(solution,8) + in.substring(endBracketIndex+1,in.length());
    }
    
    positionToCheck = in.indexOf("tan");
    if (positionToCheck != -1) {
      int endBracketIndex = endBracket(positionToCheck,in);
      float solution = tan(calculate(in.substring(positionToCheck + 4,endBracketIndex)).toFloat());
      in = in.substring(0,positionToCheck) + String(solution,8) + in.substring(endBracketIndex+1,in.length());
    }
    
    positionToCheck = in.indexOf("asin");
    if (positionToCheck != -1) {
      int endBracketIndex = endBracket(positionToCheck,in);
      float solution = asin(calculate(in.substring(positionToCheck + 4,endBracketIndex)).toFloat());
      in = in.substring(0,positionToCheck) + String(solution,8) + in.substring(endBracketIndex+1,in.length());
    }
    
    positionToCheck = in.indexOf("acos");
    if (positionToCheck != -1) {
      int endBracketIndex = endBracket(positionToCheck,in);
      float solution = acos(calculate(in.substring(positionToCheck + 4,endBracketIndex)).toFloat());
      in = in.substring(0,positionToCheck) + String(solution,8) + in.substring(endBracketIndex+1,in.length());
    }
    
    positionToCheck = in.indexOf("atan");
    if (positionToCheck != -1) {
      int endBracketIndex = endBracket(positionToCheck,in);
      float solution = atan(calculate(in.substring(positionToCheck + 4,endBracketIndex)).toFloat());
      in = in.substring(0,positionToCheck) + String(solution,8) + in.substring(endBracketIndex+1,in.length());
    }
  }
  
  return in;
}
