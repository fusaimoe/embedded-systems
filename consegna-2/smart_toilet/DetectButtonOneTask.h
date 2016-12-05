#ifndef __DETECTBUTTONONETASK__
#define __DETECTBUTTONONETASK__

#include "Task.h"
#include "ButtonImpl.h"

class DetectButtonOneTask: public Task {

    int pin;
    Button* btn;
    enum { NOTPRESSED, PRESSING, PRESSED } state;
    int counter;

  public:

    DetectButtonOneTask(int pin);
    void init(int period);
    void tick();
};

#endif
