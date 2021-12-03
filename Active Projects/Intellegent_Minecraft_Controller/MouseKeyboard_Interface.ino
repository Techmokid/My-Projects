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
void stopMining() { Mouse.release(MOUSE_LEFT); delay(100); }
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
void placeBlock() {
  Mouse.press(MOUSE_RIGHT);
  delay(50);
  Mouse.release(MOUSE_RIGHT);
}

void rotateXAngle(float angle) {
  //W.I.P
  int steps = floor(abs(angle)/180*100 + 0.5f);
  for (int i = 0; i < steps; i++) {
    if (angle > 0) {
      Mouse.move(-500,0,0); delay(10);
    } else {
      Mouse.move(500,0,0); delay(10);
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

void placeSquare(int sideLength) { placeRectangle(sideLength,sideLength); }
void placeRectangle(int x, int y) {
  lookDown();
  startPlacing();
  jump();
  
  rotateYAngle(20);
  moveForwardsBlocks(y-1);

  //rotateXAngle(90);
  moveRightBlocks(x-1);
  
  //rotateXAngle(90);
  moveBackwardsBlocks(y-1);

  //rotateXAngle(90);
  moveLeftBlocks(x-1);
}

void moveForwards() { Keyboard.press('w'); }
void moveBackwards() { Keyboard.press('s'); }
void moveLeft() { Keyboard.press('a'); }
void moveRight() { Keyboard.press('d'); }
void crouch() { Keyboard.press(KEY_LEFT_SHIFT); }
void stopCrouch() { Keyboard.release(KEY_LEFT_SHIFT); }
void jump() { Keyboard.write(char(32)); }
void stopMoving() {
  Keyboard.release('w');
  Keyboard.release('s');
  Keyboard.release('a');
  Keyboard.release('d');
}

void stripMine(int hotbar_Pickaxe, int hotbar_Torch) {
  for (int i = 0; i < 25; i++) {
    selectHotbarSlot(hotbar_Pickaxe);
    delay(100);
    
    mineForwards(true);
    delay(25000);

    stopMining();
    stopCrouch();
    stopMoving();
    
    rotateXAngle(90);
    lookDown(); rotateYAngle(90);
    
    selectHotbarSlot(hotbar_Torch);
    delay(100);
  
    placeBlock();
    rotateXAngle(-90);
  }
}

void selectHotbarSlot(int slot) {
  Keyboard.write( String(slot)[0] );
}

void openCloseInventory() { Keyboard.write('e'); }

void printChatMsg(char msg[]) {
  Keyboard.write('t'); delay(100);
  for(int i = 0; i < strlen(msg); i++) {
    Keyboard.write(msg[i]); delay(1);
  }
  Keyboard.write(KEY_RETURN); delay(100);
}
