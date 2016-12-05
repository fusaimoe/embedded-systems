#ifndef __DETECTPROXIMITYTASK__
#define __DETECTPROXIMITYTASK__

#include "Task.h"
#include "ProximitySensorImpl.h"

class DetectProximityTask: public Task {

    int echo, trig;
    ProximitySensor* proximity;
    enum { OUT, SINK, WC, EXIT } state;

  public:

    DetectProximityTask(int echo, int trig);
    void init(int period);
    void tick();
};

#endif
