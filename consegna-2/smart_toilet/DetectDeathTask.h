#ifndef __DETECTDEATHTASK__
#define __DETECTDEATHTASK__

#include "Task.h"

class DetectDeathTask: public Task {

    enum { OFF, CHECK, DEATH } state;
    int counter;
    
  public:

    void init(int period);
    void tick();
};

#endif
