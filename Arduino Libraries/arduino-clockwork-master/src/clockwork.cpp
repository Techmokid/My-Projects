/*
  Clockwork
  Paolo Bosetti 2015
*/
#include "clockwork.h"

Clockwork::Clockwork(unsigned int ms) {
  init(ms, NULL);
}

Clockwork::Clockwork(unsigned int ms, CallbackType cb) {
  init(ms, cb);
}

void Clockwork::init(unsigned int ms, CallbackType cb) {
  _base = ms;
  _cb = cb;
  _last_start = 0;
  _last_stop = 0;
  _tet = 0;
}

void Clockwork::start() {
  _last_start = micros();
}

bool Clockwork::stop() {
  _last_stop = micros();
  
  if (_last_stop < _last_start) { // Overflow!
    micros_t max = -1;
    _tet = _last_start + (max - _last_stop);
  }
  else {
    _tet = _last_stop - _last_start;
  }
  
  long time_to_wait = last_delay();
  
  if (time_to_wait < 0) {
    if (_cb != NULL) {
      _cb(time_to_wait);
    }
    return false;
  }
  
  if (time_to_wait > 1000) {
    delay(time_to_wait / 1000);
  }
  delayMicroseconds(time_to_wait % 1000);
  
  return true;
}

