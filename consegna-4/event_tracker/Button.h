#ifndef __BUTTON__
#define __BUTTON__

#include "event.h"

#define BUTTON_PRESSED_EVENT 1


class Button {
 
public: 
  virtual bool isPressed() = 0;
};

class ButtonPressed: public Event {
public:
  ButtonPressed(Button* source) : Event(BUTTON_PRESSED_EVENT){
    this->source = source;  
  } 
 
  Button* getSource(){
    return source;
  } 
private:
  Button* source;  
};


#endif
