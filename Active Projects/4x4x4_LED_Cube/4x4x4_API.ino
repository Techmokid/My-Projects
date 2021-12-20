bool LED_MEM[4][4][4];
int layer_pins[] = { A2,A3,A4,A5 };
int pixel_pins[] = { 12,13,A0,A1,8,9,10,11,4,5,6,7,0,1,2,3 };

void setupLEDs() {
  for (int i = 0; i < sizeof(layer_pins)/sizeof(layer_pins[0]); i++) {
    pinMode(layer_pins[i],OUTPUT); digitalWrite(layer_pins[i],LOW);
  }
  for (int i = 0; i < sizeof(pixel_pins)/sizeof(pixel_pins[0]); i++) {
    pinMode(pixel_pins[i],OUTPUT); digitalWrite(pixel_pins[i],HIGH);
  }
  
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      for (int z = 0; z < 4; z++) {
        LED_MEM[x][y][z] = false;
      }
    }
  }
}

void setPixel(int x, int y, int z, bool state) {
  digitalWrite(layer_pins[y],HIGH);
  digitalWrite(pixel_pins[x + z*4],LOW);
  LED_MEM[x][y][z] = state;
}

void allOff() {
  for (int x = 0; x < 4; x++) {
    for(int y = 0; y < 4; y++) {
      for(int z = 0; z < 4; z++) {
        LED_MEM[x][y][z] = false;
        setupLEDs();
      }
    }
  }
}

void updateLEDs() {
  //allOff();
}
