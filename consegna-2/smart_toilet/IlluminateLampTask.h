#ifndef __ILLUMINATELAMPTASK__
#define __ILLUMINATELAMPTASK__

#include "Task.h"
#include "LedImpl.h"

class IlluminateLampTask: public Task {

    int pin;
    Led* led;
    enum { OFF, ON, WAIT } state;
    int counter;

  public:

    IlluminateLampTask(int pin);
    void init(int period);
    void tick();
};

#endif
