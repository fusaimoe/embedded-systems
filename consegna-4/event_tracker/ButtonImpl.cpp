#include "ButtonImpl.h"
#include "Arduino.h"
#include "event.h"

ButtonImpl* buttons[2]; 

long last_0, last_1;

void notifyButtonListeners_0(){
  if (buttons[0] != NULL){
    long curr = millis();
    if (curr - last_0 > 100){
      last_0 = curr;
      Event* ev = new ButtonPressed(buttons[0]);
      dispatchEvent(ev);
    }
  }
}

void notifyButtonListeners_1(){
  if (buttons[1] != NULL){
    long curr = millis();
    if (curr - last_1 > 100){
      last_1 = curr;
      Event* ev = new ButtonPressed(buttons[1]);
      dispatchEvent(ev);
    }
  }
}

void registerNewButton(int pin, ButtonImpl* button){
  switch (pin){
    case 2: buttons[0] = button;
            attachInterrupt(0, notifyButtonListeners_0, RISING); 
            break;
    case 3: buttons[1] = button;
            attachInterrupt(1, notifyButtonListeners_1, RISING); 
            break;
  } 
}


ButtonImpl::ButtonImpl(int pin){
  this->pin = pin;
  pinMode(pin, INPUT);  
  registerNewButton(pin,this);
} 
  
bool ButtonImpl::isPressed(){
  return digitalRead(pin) == HIGH;
}


