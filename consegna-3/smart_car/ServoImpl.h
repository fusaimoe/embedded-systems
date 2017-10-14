#ifndef __SERVOIMPL__
#define __SERVOIMPL__

#include <ServoTimer2.h>

class ServoImpl {

public:
  ServoImpl(int pin);
  void setValue(int value);

private:
    ServoTimer2 myservo;
};

#endif
