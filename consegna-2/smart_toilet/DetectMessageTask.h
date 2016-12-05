#ifndef __DETECTMESSAGETASK__
#define __DETECTMESSAGETASK__

#include "Task.h"
#include "MsgService.h"

class DetectMessageTask: public Task {

    enum { OFF, USERS, STATUS } state;

  public:

    void init(int period);
    void tick();
};

#endif
