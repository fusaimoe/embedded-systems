#ifndef __ILLUMINATELAMPTASK__
#define __ILLUMINATELAMPTASK__

#include "Task.h"
#include "LedImpl.h"
#include "SharedContext.h"

class IlluminateLampTask: public Task {

private:

    Led* led;
    SharedContext* shared;
    enum { OFF, ON, WAIT } state;

  public:

    IlluminateLampTask(SharedContext* shared, Led* led);
    void init(int period);
    void tick();
};

#endif
