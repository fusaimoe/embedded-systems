#ifndef __EVENT__
#define __EVENT__

class Event {
public:
  Event(int type);
  int getType();
private:
  int type;
};

/* register a new event handler reacting to events of some type */
bool addEventHandler(int eventType, void (*proc)(Event* ev));  
void dispatchEvent(Event* ev);
void mainEventLoop();

#endif

