#ifndef __DETECTCONTACTTASK__
#define __DETECTCONTACTTASK__

#include "Task.h"
#include "ButtonImpl.h"
#include "Display.h"
#include "SharedContext.h"

class DetectContactTask: public Task {

  private:

    Button* button;
    Display* display;
    SharedContext* shared;
    enum { OFF, ON } state;

  public:

    DetectContactTask(SharedContext* shared, Button* button, Display* display);
    void init(int period);
    void tick();
};

#endif
