#ifndef __DETECTPROXIMITYTASK__
#define __DETECTPROXIMITYTASK__

#include "Task.h"
#include "ProximitySensorImpl.h"
#include "SharedContext.h"

class DetectProximityTask: public Task {

  private:

    ProximitySensor* proximity;
    SharedContext* shared;
    enum { OUT, IN, CLOSE } state;

  public:

    DetectProximityTask(SharedContext* shared, ProximitySensor* proximity);
    void init(int period);
    void tick();
};

#endif
