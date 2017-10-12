#ifndef __LED__
#define __LED__

#include "Light.h"
#include "Component.h"
//implementa le funzionalit� richieste dall'interfaccia light
class Led: public Light, public Component {
  public:
    Led(int pin);
    void switchOn();
    void switchOff();
    int switchState();
    bool isOn();
  private:
    int state;
  };

#endif
