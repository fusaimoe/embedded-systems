#ifndef __DETECTCARTASK__
#define __DETECTCARTASK__

#include "Task.h"
#include "SharedContext.h"

class DetectCarTask: public Task {

  private:

    SharedContext* shared;
    enum { OFF, ONSTOP, ONMOVE, OFFPARK } state;

  public:

    DetectCarTask(SharedContext* shared);
    void init(int period);
    void tick();
};

#endif
