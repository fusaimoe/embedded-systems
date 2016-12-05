#ifndef __DETECTMOTIONTASK__
#define __DETECTMOTIONTASK__

#include "Task.h"
#include "PresenceSensorImpl.h"

class DetectMotionTask: public Task {

    int pin;
    PresenceSensor* presence;
    enum { UNDETECTED, DETECTED } state;

  public:

    DetectMotionTask(int pin);
    void init(int period);
    void tick();
};

#endif
