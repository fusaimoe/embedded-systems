#ifndef __DETECTCARTASK__
#define __DETECTCARTASK__

#include "Task.h"
#include "AppButton.h"
#include "SharedContext.h"

class DetectCarTask: public Task {

  private:

    AppButton* buttonPark;
    AppButton* buttonMove;
    AppButton* buttonOn;
    SharedContext* shared;
    enum { OFF, ONSTOP, ONMOVE, OFFPARK } state;

  public:

    DetectCarTask(SharedContext* shared, AppButton* buttonPark, AppButton* buttonMove, AppButton* buttonOn);
    void init(int period);
    void tick();
};

#endif
