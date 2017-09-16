#include "AndroidEventsManager.h"
#include "event.h"

class AlarmE: public Event {
public:
  AlarmE(InputDevice* source) : Event(EventType::ALARM_EVENT){
    this->source = source;
  }

  InputDevice* getSource(){
    return source;
  }
private:
  InputDevice* source;
};

class PresenceE: public Event {
public:
  PresenceE(InputDevice* source) : Event(EventType::PRESENCE_EVENT){
    this->source = source;
  }

  InputDevice* getSource(){
    return source;
  }
private:
  InputDevice* source;
};

AndroidEventsManager* AndroidEventsManager::instance = NULL;

void AndroidEventsManager::inizialize(InputDevice* android) {
  if(AndroidEventsManager::instance == NULL) {
    AndroidEventsManager::instance = new AndroidEventsManager(android);
  }
}

AndroidEventsManager* AndroidEventsManager::getInstance() {
  return AndroidEventsManager::instance;
}

AndroidEventsManager::AndroidEventsManager(InputDevice* android)
{
  this->android = android;
}

void AndroidEventsManager::checkEvents()
{
  if(android->isMsgAvailable()) {
    InputMessages ms = android->getMessage()->convertToStandardMsg();
    switch (ms)
    {
      case InputMessages::ALARM:
        dispatchEvent(new AlarmE(android));
        break;
       case InputMessages::PRESENCE:
        dispatchEvent(new PresenceE(android));
        break;
      default:
        break;
    }
  }
}
