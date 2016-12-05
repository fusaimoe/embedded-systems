#include "IlluminateWarningTask.h"

#define USERMAX 4

extern bool motion, prox, alarm;
extern int usersWC;

IlluminateWarningTask::IlluminateWarningTask(int pin) {
  this->pin = pin;
}

void IlluminateWarningTask::init(int period) {
  Task::init(period);
  led = new LedImpl(pin);
  state = OFF;
  counter=0;
}

void IlluminateWarningTask::tick() {
  switch (state) {
    case OFF:
      sent = false;
      led->switchOff();
      counter = 0;
      if (usersWC >= USERMAX) { //usersWC % USERMAX = 0 se non c'è distinzione fra userWC e userTLT 
        state = CLEANING;
      }
      if (alarm) {
        state = EMERGENCY;
      }
      break;
    case CLEANING:
      led->switchOn();
      counter++;
      if ((prox || motion) && !sent){
        MsgService.sendMsg("SI PREGA DI USCIRE, TOILETTE IN FASE DI AUTO-PULIZIA");
        sent = true;
      }
      if (counter >= 80) { //80 = 10s con un periodo di 125ms
        usersWC=0;
        state = OFF;
      }
      break;
    case EMERGENCY:
      if (!alarm) {
        state = OFF;
      } else {
        led->switchOn();
        state = WAIT;
      }
      break;
    case WAIT:
      led->switchOff();
      state = EMERGENCY;
      break;
  }
}
