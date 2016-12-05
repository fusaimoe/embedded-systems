#ifndef __PRESENCESENSORIMPL__
#define __PRESENCESENSORIMPL__

#include "PresenceSensor.h"

class PresenceSensorImpl: public PresenceSensor {

  public:
    PresenceSensorImpl(int pin);
    bool isPresent();

  private:
    int pin;

};

#endif
