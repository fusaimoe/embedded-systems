#include "Pir.h"
#include "Arduino.h"

Pir* interPir;

void notifyPir() {
  Event* ev = new PirEvent(interPir);
  dispatchEvent(ev);
}

void registerNewPir(int pin, Pir* pir){
  switch (pin){
    case 3: interPir = pir;
            attachInterrupt(1, notifyPir, RISING); 
            break;
  } 
}

Pir::Pir(int pin) : Component::Component(new int[1]{pin}, ComponentTypes::PIR)
{
	pinMode(pin, INPUT);
  registerNewPir(pin, this);
}

boolean Pir::movement()
{
	return digitalRead(this->getPin()[0]);
}
