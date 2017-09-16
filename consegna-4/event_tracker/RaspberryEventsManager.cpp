#include "RaspberryEventsManager.h"
#include "event.h"

class StopAlarmE: public Event {
public:
  StopAlarmE(InputDevice* source) : Event(EventType::STOP_ALARM_EVENT){
    this->source = source;
  }

  InputDevice* getSource(){
    return source;
  }
private:
  InputDevice* source;
};

RaspberryEventsManager* RaspberryEventsManager::instance = NULL;

void RaspberryEventsManager::inizialize(InputDevice* raspbi) {
  if(RaspberryEventsManager::instance == NULL) {
    RaspberryEventsManager::instance = new RaspberryEventsManager(raspbi);
  }
}

RaspberryEventsManager* RaspberryEventsManager::getInstance() {
  return RaspberryEventsManager::instance;
}

RaspberryEventsManager::RaspberryEventsManager(InputDevice* raspbi)
{
  this->raspbi = raspbi;
}

void RaspberryEventsManager::checkEvents()
{
  if(raspbi->isMsgAvailable()) {
    InputMessages ms = raspbi->getMessage()->convertToStandardMsg();
    switch (ms)
    {
      case InputMessages::STOP_ALARM:
        dispatchEvent(new StopAlarmE(raspbi));
        break;
      default:
        break;
    }
  }
}
