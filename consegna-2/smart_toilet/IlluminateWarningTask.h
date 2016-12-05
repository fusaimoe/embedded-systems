#ifndef __ILLUMINATEWARNINGTASK__
#define __ILLUMINATEWARNINGTASK__

#include "Task.h"
#include "LedImpl.h"
#include "MsgService.h"

class IlluminateWarningTask: public Task {

    int pin;
    Led* led;
    enum { OFF, CLEANING, EMERGENCY, WAIT } state;
    int counter;
    bool sent;

  public:

    IlluminateWarningTask(int pin);
    void init(int period);
    void tick();
};

#endif
