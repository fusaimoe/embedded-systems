#include "LedImpl.h"
#include "Arduino.h"

LedImpl::LedImpl(int pin){
  this->pin = pin;
  pinMode(pin,OUTPUT);
}

void LedImpl::switchOn(){
  digitalWrite(pin,HIGH);
}

void LedImpl::switchOff(){
  digitalWrite(pin,LOW);
};
