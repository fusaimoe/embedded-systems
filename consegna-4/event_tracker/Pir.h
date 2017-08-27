#ifndef __PIR__
#define __PIR__

#include "Component.h"
#include "MovementSensor.h"
#include "event.h"

#define PIR_EVENT 5

class Pir : public Component, public MovementSensor {
public:
	Pir(int pin);
	bool movement();
};

class PirEvent: public Event {
public:
  PirEvent(Pir* source) : Event(PIR_EVENT){
    this->source = source;
  }

  Pir* getSource(){
    return source;
  }
private:
  Pir* source;
};

#endif
