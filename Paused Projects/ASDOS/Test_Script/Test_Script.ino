void setup() {
  Serial.begin(115200);
  Serial.println(splitString("Hello,World,!,How,Is,Everyone,Doing,Today,Kiddos?",',', 0));
  Serial.println(splitString("Hello,World,!,How,Is,Everyone,Doing,Today,Kiddos?",',', 1));
  Serial.println(splitString("Hello,World,!,How,Is,Everyone,Doing,Today,Kiddos?",',', 2));
  Serial.println(splitString("Hello,World,!,How,Is,Everyone,Doing,Today,Kiddos?",',', 3));
  Serial.println(splitString("Hello,World,!,How,Is,Everyone,Doing,Today,Kiddos?",',', 4));
  Serial.println(splitString("Hello,World,!,How,Is,Everyone,Doing,Today,Kiddos?",',', 5));
  Serial.println(splitString("Hello,World,!,How,Is,Everyone,Doing,Today,Kiddos?",',', 6));
  Serial.println(splitString("Hello,World,!,How,Is,Everyone,Doing,Today,Kiddos?",',', 7));
}

void loop() { }

String splitString(String input_string, char delimiter, int position) {
  //Find the number of required elements in the output array
  int numberOfPieces = 0;
  for(int i = 0; i < input_string.length(); i++) { if (input_string[i] == delimiter) { numberOfPieces++; } }
  
  String result[numberOfPieces + 1];
  int lastIndex = 0;
  int counter = 0;
  
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
