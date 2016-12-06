#ifndef __PROXIMITYSENSORIMPL__
#define __PROXIMITYSENSORIMPL__

#include "ProximitySensor.h"

class ProximitySensorImpl: public ProximitySensor {

public:  
  ProximitySensorImpl(int echoPin, int trigPin);
  float getDistance();
  
private:
    const float vs = 331.5 + 0.6*20;
    int echoPin, trigPin;
};

#endif 
