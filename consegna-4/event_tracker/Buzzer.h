#ifndef __BUZZER__
#define __BUZZER__
#include "Component.h"
//implementa le funzionalit� richieste dall'interfaccia light
class Buzzer: public Component {
public:
  Buzzer(int pin);
  void switchOn();
  void switchOff();
};

#endif
