#ifndef __ILLUMINATEWARNINGPTASK__
#define __ILLUMINATEWARNINGTASK__

#include "Task.h"
#include "LedImpl.h"
#include "SharedContext.h"

class IlluminateWarningTask: public Task {

private:

    Led* led;
    SharedContext* shared;
    int counter;
    enum { OFF, ON, WAIT } state;

  public:

    IlluminateWarningTask(SharedContext* shared, Led* led);
    void init(int period);
    void tick();
};
