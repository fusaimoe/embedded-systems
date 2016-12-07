#ifndef __ATTACKTASKTASK__
#define __ATTACKTASKTASK__

#include "Task.h"
#include "AppSlider.h"
#include "ServoImpl.h"
#include "SharedContext.h"

class AttackTask: public Task {

  private:

    AppSlider* slider;
    Servo* servo;
    SharedContext* shared;
    enum { OFF, ON, FULL } state;

  public:

    AttackTask(SharedContext* shared, AppSlider* slider, Servo* servo);
    void init(int period);
    void tick();
};

#endif
