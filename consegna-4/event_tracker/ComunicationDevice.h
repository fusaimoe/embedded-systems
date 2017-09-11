#ifndef __COMUNICATIONDEVICE__
#define __COMUNICATIONDEVICE__
#include "InputDevice.h"
#include "OutputDevice.h"
#include "event.h"

class ComunicationDevice : virtual public InputDevice, virtual public OutputDevice
{
};

class StopAlarmE: public Event {
public:
  StopAlarmE(ComunicationDevice* source) : Event(EventType::STOP_ALARM_EVENT){
    this->source = source;
  }

  ComunicationDevice* getSource(){
    return source;
  }
private:
  ComunicationDevice* source;
};

class AlarmE: public Event {
public:
  AlarmE(ComunicationDevice* source) : Event(EventType::ALARM_EVENT){
    this->source = source;
  }

  ComunicationDevice* getSource(){
    return source;
  }
private:
  ComunicationDevice* source;
};

class PresenceE: public Event {
public:
  PresenceE(ComunicationDevice* source) : Event(EventType::PRESENCE_EVENT){
    this->source = source;
  }

  ComunicationDevice* getSource(){
    return source;
  }
private:
  ComunicationDevice* source;
};

#endif
