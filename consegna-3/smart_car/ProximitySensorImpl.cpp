#include "ProximitySensorImpl.h"
#include "Arduino.h"

ProximitySensorImpl::ProximitySensorImpl(int echoP, int trigP) : echoPin(echoP), trigPin(trigP){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

float ProximitySensorImpl::getDistance(){
    digitalWrite(trigPin,LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin,LOW);

    float tUS = pulseIn(echoPin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t*vs;
    return d;
}
