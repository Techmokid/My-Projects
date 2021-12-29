float MyArray[10] = {0,1,2,3,4,5,6,7,8,9};

void setup() {
  Serial.begin(9600);
  
  printArray(MyArray);
  shiftArray(MyArray);
  printArray(MyArray);
}

void loop() {}

void shiftArray(float arr[10]) {
  for(int i = 0; i < 10; i++){
    arr[i] = arr[i+1];
  }
}

void printArray(float arr[10]) {
  String sentence = "[";
  for(int i = 0; i < 10; i++){
    sentence += String(arr[i]) + ",";
  }
  sentence += "]";

  Serial.println(sentence);
}

