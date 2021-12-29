#define len 20

float arr[len];

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(A0));
}

float averageArray(float arr[]) {
  float result = 0;
  
  for (int i=0; i<len; i++) {
    result += arr[i];
  }
  
  return (result / len);
}

void addToNextPosition (float val) {
  for (int i=0; i < len; i++) {
    if (i < len - 1) {
      arr[i] = arr[i+1];
    } else {
      arr[i] = val;
    }
  }
}

