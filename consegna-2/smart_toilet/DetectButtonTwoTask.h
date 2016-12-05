#ifndef __DETECTBUTTONTWOTASK__
#define __DETECTBUTTONTWOTASK__

#include "Task.h"
#include "ButtonImpl.h"

class DetectButtonTwoTask: public Task {

    int pin;
    Button* btn;
    enum { OFF, DEACTIVATE} state;

  public:

    DetectButtonTwoTask(int pin);
    void init(int period);
    void tick();
};

#endif
