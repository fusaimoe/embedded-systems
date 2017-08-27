#ifndef __EVENT__
#define __EVENT__


#define TIMER_EVENT 1

class Event {
public:
  Event(int type);
  int getType();
private:
  int type;
};

class TimerClock: public Event {
public:
  TimerClock(int source) : Event(TIMER_EVENT){
    this->source = source;
  }

  int getSource(){
    return source;
  }
private:
  int source;
};

/* register a new event handler reacting to events of some type */
bool addEventHandler(int eventType, void (*proc)(Event* ev));
void dispatchEvent(Event* ev);
void mainEventLoop();

#endif
