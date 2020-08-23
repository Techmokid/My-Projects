bool state = false;

void flashLED() {
  if (!running) { return; }
  if (millis() - flashTimer >= flashInterval) {
    flashTimer = millis();
    state = !state;
    digitalWrite(LED_BUILTIN,state);
  }
}

//unsigned long delayTimer = 0;
//void delayFunction(int timeToDelay) {
//  delayTimer = millis();
//  while (millis() - delayTimer < timeToDelay) {
//    yield();
//    flashLED();
//  }
//}
