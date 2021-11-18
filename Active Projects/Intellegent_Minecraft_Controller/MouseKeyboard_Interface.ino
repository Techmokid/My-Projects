#include "Keyboard.h"
#include "Mouse.h"

void setupKM() {
  Mouse.begin();
  delay(1000);
  
  Keyboard.begin();
  delay(1000);
}

void mineForwards(bool crouching) {
  lookForwards();
  if (crouching) {
    rotateYAngle(-15);
    crouch();
  } else {
    rotateYAngle(-30);
  }
  
  startMining();
  moveForwards();
}

void mineBelow() {
  lookDown();
  
  startMining();
  moveForwards();
}

void startMining() { Mouse.press(MOUSE_LEFT); delay(200); }
void startPlacing() { Mouse.press(MOUSE_RIGHT); delay(200); }
void lookDown() { rotateYAngle(-180); }
void lookUp() { rotateYAngle(180); }
void lookForwards() { lookDown(); rotateYAngle(90); }
void rotateYAngle(float angle) {
  int steps = floor(abs(angle)/180*100 + 0.5f);
  for (int i = 0; i < steps; i++) {
    if (angle > 0) {
      Mouse.move(0,500,0); delay(10);
    } else {
      Mouse.move(0,-500,0); delay(10);
    }
  }
}

void waitNumberOfBlocks(int blocks) {
  //250ms moves us 1.073 blocks
  //500ms moves us 2.155 blocks
  //750ms moves us 3.018 blocks
  //950ms moves us 4.098 blocks
  //1000ms moves us 4.313 blocks
  //3707ms moves us 15.97 blocks
  //3740ms moves us 16.186 blocks
  //4000ms moves us 17.265 blocks
  
  delay(ceil((float)blocks * (3740 / 16.186)));
}

void moveForwardsBlocks(int blocks) { Keyboard.press('w'); waitNumberOfBlocks(blocks); Keyboard.release('w'); }
void moveBackwardsBlocks(int blocks) { Keyboard.press('s'); waitNumberOfBlocks(blocks); Keyboard.release('s'); }
void moveLeftBlocks(int blocks) { Keyboard.press('a'); waitNumberOfBlocks(blocks); Keyboard.release('a'); }
void moveRightBlocks(int blocks) { Keyboard.press('d'); waitNumberOfBlocks(blocks); Keyboard.release('d'); }

void moveForwards() { Keyboard.press('w'); }
void moveBackwards() { Keyboard.press('s'); }
void moveLeft() { Keyboard.press('a'); }
void moveRight() { Keyboard.press('d'); }
void crouch() { Keyboard.press(KEY_LEFT_SHIFT); }
void stopMoving() {
  Keyboard.release('w');
  Keyboard.release('s');
  Keyboard.release('a');
  Keyboard.release('d');
}

void selectHotbarSlot(int slot) { Keyboard.write(slot); }
void openCloseInventory() { Keyboard.write('e'); }
