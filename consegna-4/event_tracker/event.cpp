#include "event.h"
#include "Arduino.h"

#define MAX_HANDLERS 50
#define MAX_EVQUEUE_SIZE 20 

class EventQueue {  
    
public:
  EventQueue(){
    head = tail = 0; 
  }
  bool isEmpty() {
    return head == tail; 
  }
  void enqueue(Event* ev){
    queue[tail] = ev;
    tail = (tail+1) % MAX_EVQUEUE_SIZE;
  }
  Event* dequeue(){
    if (isEmpty()){
      return 0;
    } else {
      Event* pev = queue[head];
      head = (head+1) % MAX_EVQUEUE_SIZE;
      return pev; 
    }
  }

private:
  Event* queue[MAX_EVQUEUE_SIZE];
  int head, tail; 
};

class EventHandler {
public:
  EventHandler(int type, void (*proc)(Event* ev));
  bool isTriggered(Event* ev);
  bool exec(Event* ev);
private:
  int type;
  void (*proc)(Event* ev);
};

class EventHandlerManager {

  public:
  static EventHandlerManager* getInstance();  
  bool addEventHandler(int event, void (*proc)(Event* ev));  
  void dispatchEvent(Event* ev);
  void mainEventLoop();  

private:
  EventHandlerManager();    
  EventQueue eventQueue;
  int nEventHandlers;
  EventHandler* eventHandlers[MAX_HANDLERS];
  
  /* singleton */
  static EventHandlerManager* instance;
  
};

/* ------------------------ Event  ------------------------ */

Event::Event(int type){
  this->type = type;
} 
  
int Event::getType(){
  return type;  
}
  
  
/* ------------------------ Event Handlers  ------------------------ */

EventHandler::EventHandler(int type, void (*proc)(Event* ev)){
  this->type = type;
  this->proc = proc;
}
  
bool EventHandler::isTriggered(Event* ev){
  if (ev->getType() == this->type){
    return true;
  } else {
    return false; 
  }
}
  
bool EventHandler::exec(Event* ev){
  (*proc)(ev);
}

/* ------------------------ Event Handler Manager  ------------------------ */

EventHandlerManager* EventHandlerManager::instance = new EventHandlerManager();

EventHandlerManager* EventHandlerManager::getInstance(){
  return instance;
}

EventHandlerManager::EventHandlerManager(){
  nEventHandlers = 0;  
}
  
bool EventHandlerManager::addEventHandler(int event, void (*proc)(Event* ev)){
  if (nEventHandlers < MAX_HANDLERS){
    eventHandlers[nEventHandlers] = new EventHandler(event, proc);
    nEventHandlers++;
    return true;
  } else {
    return false;  
  }
}
  
void EventHandlerManager::dispatchEvent(Event* ev){
  eventQueue.enqueue(ev);
}

void EventHandlerManager::mainEventLoop(){
  while (1){
    bool isEmpty = true;
    while (isEmpty){
      cli();
      isEmpty = eventQueue.isEmpty();
      sei();
    }
    cli();
    Event* ev = eventQueue.dequeue();
    sei();

    // dispatch event 
    for (int i = 0; i < nEventHandlers; i++){
      if (eventHandlers[i]->isTriggered(ev)){
        eventHandlers[i]->exec(ev);
      }
    }    
    
    delete ev;
  }
}

/* ------------------------ Global  ------------------------ */

bool addEventHandler(int event, void (*proc)(Event* ev)){
  return EventHandlerManager::getInstance()->addEventHandler(event, proc);
}  

void dispatchEvent(Event* ev){
  return EventHandlerManager::getInstance()->dispatchEvent(ev);
}

void mainEventLoop(){
  EventHandlerManager::getInstance()->mainEventLoop();
}



