bool pin_2,pin_3,pin_18,pin_19,pin_20,pin_21;

void setup() { Serial.begin(2000000); }
void loop() {
  if (digitalRead(2) != pin_2)   { pin_2 = !pin_2;   Serial.println("2: " + String(pin_2));   }
  if (digitalRead(3) != pin_3)   { pin_3 = !pin_3;   Serial.println("3: " + String(pin_3));   }
  if (digitalRead(18) != pin_18) { pin_18 = !pin_18; Serial.println("18: " + String(pin_18)); }
  if (digitalRead(19) != pin_19) { pin_19 = !pin_19; Serial.println("19: " + String(pin_19)); }
  if (digitalRead(20) != pin_20) { pin_20 = !pin_20; Serial.println("20: " + String(pin_20)); }
  if (digitalRead(21) != pin_21) { pin_21 = !pin_21; Serial.println("21: " + String(pin_21)); }
}
