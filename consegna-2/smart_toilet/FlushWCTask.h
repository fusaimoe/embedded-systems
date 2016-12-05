#ifndef __FLUSHWCTASK__
#define __FLUSHWCTASK__

#include "Task.h"
#include "LedImpl.h"

class FlushWCTask: public Task {

    int pin;
    Led* led;
    enum { OFF, ON, WAIT } state;
    int counter;

  public:

    FlushWCTask(int pin);
    void init(int period);
    void tick();
};

#endif
