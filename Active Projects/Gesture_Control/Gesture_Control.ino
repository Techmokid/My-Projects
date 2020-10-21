#include <Wire.h>
#include <paj7620.h>

void setup() {
 Serial.begin(115200);
 int error = paj7620Init();
 if (error) {
  if (error == 2) {
    Serial.print("Sensor not connected");
  } else { Serial.print("Sensor error " + String(error)); }
  
  for (;;);
 }
 Serial.println("Go");
}

void loop() {
  //see the examples for more complete code
  char data = 0;
  paj7620ReadReg(0x43, 1, &data); // Read Bank_0_Reg_0x43/0x44 for gesture result.
  
  if (data == GES_LEFT_FLAG) {
    Serial.println("Forward");
  } else if (data == GES_RIGHT_FLAG) {
    Serial.println("Backward");
  } else {
    paj7620ReadReg(0x44, 1, &data); //wave is stored in another register
    if (data == GES_WAVE_FLAG) {
      Serial.println("wave");
    }
  }
  
  delay(100);
}
