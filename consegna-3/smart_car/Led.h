#ifndef __LED__
#define __LED__

class Led {
public:
  virtual void switchOn() = 0;
  virtual void switchOff() = 0;    
};

#endif

