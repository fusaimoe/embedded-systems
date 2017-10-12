#ifndef __EVENT__
#define __EVENT__

enum class EventType {TIMER_EVENT, ALARM_EVENT, PRESENCE_EVENT, STOP_ALARM_EVENT, PIR_EVENT};

class Event {
  public:
    Event(EventType type);
    EventType getType();
    
  private:
    EventType type;
  };

class TimerClock: public Event {
  public:
    TimerClock(void* source) : Event(EventType::TIMER_EVENT){
      this->source = source;
    }

    void* getSource(){
      return source;
    }

  private:
    void* source;
};

/* register a new event handler reacting to events of some type */
bool addEventHandler(EventType eventType, void (*proc)(Event* ev));
void dispatchEvent(Event* ev);
void mainEventLoop();

#endif
