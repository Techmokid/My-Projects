#include <digitalWriteFast.h>

class AudioHandler {
public:
  //Alter these as you require
  float frequency = 1;
  float dutyCycle = 1;
    
  //These are internal variables that you shouldn't touch
  unsigned long prevMicros = 0;
  bool onHalf = true;  //This just asks which half of the wave the sound is on

  void updateSound(const int pinVar) {
    if ((micros() - prevMicros > (1000000 / frequency) * dutyCycle) && (onHalf)) {
      prevMicros = micros(); onHalf = false; digitalWriteFast(pinVar,false);
    } else if ((micros() - prevMicros > (1000000 / frequency) * (1 - dutyCycle)) && (!onHalf)) {
      prevMicros = micros(); onHalf = true;  digitalWriteFast(pinVar,true);
    }
  }
};

AudioHandler test_1;
AudioHandler test_2;
AudioHandler test_3;
AudioHandler test_4;

void setup() {
  Serial.begin(115200);
  pinModeFast(3,OUTPUT); test_1.frequency = 440; test_1.dutyCycle = 0.5;
  pinModeFast(4,OUTPUT); test_2.frequency = 440; test_2.dutyCycle = 0.5;
  pinModeFast(5,OUTPUT); test_3.frequency = 440; test_3.dutyCycle = 0.5;
  pinModeFast(6,OUTPUT); test_4.frequency = 440; test_4.dutyCycle = 0.5;
}

void loop() {
  Serial.println(test_1.dutyCycle);
  test_1.updateSound(3);
  test_2.updateSound(4);
  test_3.updateSound(5);
  test_4.updateSound(6);

  test_1.dutyCycle += 0.0001;
  if (test_1.dutyCycle > 1) {
    test_1.dutyCycle = 0;
  }
}
