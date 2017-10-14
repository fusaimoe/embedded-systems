#ifndef __DETECTMESSAGETASK__
#define __DETECTMESSAGETASK__

#include "Task.h"
#include "SharedContext.h"
#include "MsgService.h"

class DetectMessageTask: public Task {

  private:

    SharedContext* shared;
    MsgService* msgService;
    const String prefix = "Slider:";
    
  public:

    DetectMessageTask(SharedContext* shared, MsgService* msgService);
    void init(int period);
    void tick();
};

#endif
