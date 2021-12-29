/*
  Clockwork
  Paolo Bosetti 2015
*/
#ifndef CLOCKWORK_H
#define CLOCKWORK_H

#if ARDUINO >= 100
#include "Arduino.h" // for delayMicroseconds,digitalPinToBitMask, etc
#else
#include "WProgram.h"     // for delayMicroseconds
#include "pins_arduino.h" // for digitalPinToBitMask, etc
#endif

typedef unsigned long int  micros_t;
typedef void (*CallbackType)(long);

class Clockwork {
public:
  Clockwork(unsigned int micros);
  Clockwork(unsigned int micros, CallbackType cb);
  void init(unsigned int ms, CallbackType cb);
  void start();
  bool stop();
  micros_t last_start() { return _last_start; }
  micros_t last_stop() { return _last_stop; }
  micros_t last_delay() {return (_base * 1000) - _tet; }
  micros_t tet() { return _tet; }
  micros_t base() {return _base; }
  
private:
  micros_t _base;
  micros_t _last_start;
  micros_t _last_stop;
  micros_t _tet;
  CallbackType _cb;
};

#endif