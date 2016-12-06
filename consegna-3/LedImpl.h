#ifndef __LEDIMPL__
#define __LEDIMPL__

#include "Led.h"

class LedImpl: public Led {
public:
  LedImpl(int pin);
  void switchOn();
  void switchOff();
private:
  int pin;
};

#endif
