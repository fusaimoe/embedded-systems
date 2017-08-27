#include "DHT11.h"
#include "Arduino.h"

DHT11::DHT11(int pin) : Component::Component(new int[1]{pin}, ComponentTypes::PIR)
{
}

float DHT11::getTemperature()
{
	int chk = DHT.read11(this->getPin()[0]);
  switch (chk)
  {
    case DHTLIB_OK:
      return DHT.temperature;
    break;
    case DHTLIB_ERROR_CHECKSUM:
      return NULL;
    break;
    case DHTLIB_ERROR_TIMEOUT:
      return NULL;
    break;
    default:
      return NULL;
    break;
  }
}
