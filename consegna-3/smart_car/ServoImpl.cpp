#include "ServoImpl.h"
#include "Arduino.h"

ServoImpl::ServoImpl(int pin){
  myservo.attach(pin);
}

void ServoImpl::setValue(int value){
  Serial.println(value);
  value = map(value, 0, 180, 750, 2250); // Only needed if using ServoTimer2 instead of servo
  Serial.println(value);
  myservo.write(value);
}
