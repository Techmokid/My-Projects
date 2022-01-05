void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);

  Serial.begin(9600);
  String gate = detectGate(10, 4, 5, 2, 3);
  Serial.println(gate);
}

void loop() {}

String detectGate(bool waitTimeBetweenSwitching, int pinIn1, int pinIn2, int pinOut1, int pinOut2) {
  bool Detection1A = false;
  bool Detection1B = false;
  bool Detection2A = false;
  bool Detection2B = false;
  bool Detection3A = false;
  bool Detection3B = false;
  bool Detection4A = false;
  bool Detection4B = false;
  
  digitalWrite(pinOut1, LOW);
  digitalWrite(pinOut2, LOW);
  delay(waitTimeBetweenSwitching);
  Detection1A = digitalRead(pinIn1);
  Detection1B = digitalRead(pinIn2);
  
  digitalWrite(pinOut1, LOW);
  digitalWrite(pinOut2, HIGH);
  delay(waitTimeBetweenSwitching);
  Detection2A = digitalRead(pinIn1);
  Detection2B = digitalRead(pinIn2);
  
  digitalWrite(pinOut1, HIGH);
  digitalWrite(pinOut2, LOW);
  delay(waitTimeBetweenSwitching);
  Detection3A = digitalRead(pinIn1);
  Detection3B = digitalRead(pinIn2);
  
  digitalWrite(pinOut1, HIGH);
  digitalWrite(pinOut2, HIGH);
  delay(waitTimeBetweenSwitching);
  Detection4A = digitalRead(pinIn1);
  Detection4B = digitalRead(pinIn2);

  digitalWrite(pinOut1, LOW);
  digitalWrite(pinOut2, LOW);
  
  if ((!Detection1A) and (!Detection1B) and (!Detection2A) and (!Detection2B) and (!Detection3A) and (!Detection3B) and (!Detection4A) and (!Detection4B)) {
    return "Not Connected";
  } else if ((!Detection1A) and (!Detection1B) and (!Detection2A) and (Detection2B) and (!Detection3A) and (Detection3B) and (Detection4A) and (!Detection4B)) {
    return "Half Adder - Carry on Pin 4";
  } else if ((!Detection1A) and (!Detection1B) and (Detection2A) and (!Detection2B) and (Detection3A) and (!Detection3B) and (!Detection4A) and (Detection4B)) {
    return "Half Adder - Carry on Pin 5";
  } else if ((!Detection1A) and (!Detection2A) and (!Detection3A) and (Detection4A)) {
    return "AND";
  } else if ((!Detection1A) and (Detection2A) and (Detection3A) and (Detection4A)) {
    return "OR";
  } else if ((!Detection1A) and (Detection2A) and (Detection3A) and (!Detection4A)) {
    return "XOR";
  } else if ((Detection1A) and (Detection2A) and (Detection3A) and (!Detection4A)) {
    return "NAND";
  } else if ((Detection1A) and (!Detection2A) and (!Detection3A) and (!Detection4A)) {
    return "NOR";
  } else if ((Detection1A) and (!Detection2A) and (!Detection3A) and (Detection4A)) {
    return "XNOR";
  } else {
    if ((!Detection1B) and (!Detection2B) and (!Detection3B) and (!Detection4B)) {
      return "Single Unrecognised: " + String(Detection1A) + String(Detection2A) + String(Detection3A) + String(Detection4A);
    } else {
      return "Dual Unrecognised: " + String(Detection1A) + String(Detection1B) + String(Detection2A) + String(Detection2B) + String(Detection3A) + String(Detection3B) + String(Detection4A) + String(Detection4B);
    }
  }
}

