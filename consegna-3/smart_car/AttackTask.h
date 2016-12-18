#ifndef __ATTACKTASKTASK__
#define __ATTACKTASKTASK__

#include "Task.h"
#include "ServoImpl.h"
#include "SharedContext.h"

class AttackTask: public Task {

  private:

    //ServoImpl* servo;
    SharedContext* shared;
    enum { OFF, ON, FULL } state;

  public:

    AttackTask(SharedContext* shared/*, ServoImpl* servo*/);
    void init(int period);
    void tick();
};

#endif
