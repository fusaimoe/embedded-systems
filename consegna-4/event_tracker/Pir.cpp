#include "Pir.h"
#include "Arduino.h"

#include "config.h"

Pir* interPir;

void notifyPir() {
  Event* ev = new PirEvent(interPir);
  dispatchEvent(ev);
}

void registerNewPir(int pin, Pir* pir){
  interPir = pir;
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), notifyPir, RISING);
}

Pir::Pir(int pin) : Component::Component(new int[1]{pin}, ComponentTypes::PIR) {
	pinMode(pin, INPUT);
  registerNewPir(pin, this);
}

boolean Pir::movement() {
	return digitalRead(this->getPin()[0]);
}
