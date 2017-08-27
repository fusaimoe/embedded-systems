#ifndef __DHT__
#define __DHT__

#include "Component.h"
#include "TemperatureSensor.h"
#include <dht.h>

class DHT11 : public Component, public TemperatureSensor {
public:
	DHT11(int pin);
	float getTemperature();
private:
  dht DHT;
};
#endif
