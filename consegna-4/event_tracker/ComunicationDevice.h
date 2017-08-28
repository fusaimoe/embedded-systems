#ifndef __COMUNICATIONDEVICE__
#define __COMUNICATIONDEVICE__
#include "InputDevice.h"
#include "OutputDevice.h"
#include "event.h"


#define SERIAL_EVENT 2
#define BLUETOOTH_EVENT 3

class ComunicationDevice : virtual public InputDevice, virtual public OutputDevice
{
};

class BluetoothEvent: public Event {
public:
  BluetoothEvent(ComunicationDevice* source) : Event(BLUETOOTH_EVENT){
    this->source = source;
  }

  ComunicationDevice* getSource(){
    return source;
  }
private:
  ComunicationDevice* source;
};

class SerialInputEvent: public Event {
public:
  SerialInputEvent(ComunicationDevice* source) : Event(SERIAL_EVENT){
    this->source = source;
  }

  ComunicationDevice* getSource(){
    return source;
  }
private:
  ComunicationDevice* source;
};



#endif
