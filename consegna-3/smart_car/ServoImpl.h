#ifndef __SERVOIMPL__
#define __SERVOIMPL__

#include <Servo.h>

class ServoImpl {

public:
  ServoImpl(int pin);
  void setValue(int value);

private:
    Servo myservo;
};

#endif
