void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(11,INPUT);
  pinMode(12,INPUT);
  pinMode(13,INPUT);
}

void loop() {
  String sentence = "               ";
  bool detected = false;
  
  int looper = 2;
  while (looper < 14) {
    if (digitalRead(looper)) {
      sentence += "X ";
      detected = true;
    } else {
      sentence += "   ";
    }
    
    looper++;
  }
  
  if (detected) {
    Serial.println("Detected Pins: 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13");
    Serial.println(sentence);
    Serial.println();
  }
  
  delay(500);
}
