#include "PresenceSensorImpl.h"
#include "Arduino.h"

PresenceSensorImpl::PresenceSensorImpl(int pin){
  this->pin = pin;
  pinMode(pin, INPUT);     
} 
  
bool PresenceSensorImpl::isPresent(){
  return digitalRead(pin) == HIGH;
}


