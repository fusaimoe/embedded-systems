#include "FlushWCTask.h"

extern bool poop;

FlushWCTask::FlushWCTask(int pin) {
  this->pin = pin;
}

void FlushWCTask::init(int period) {
  Task::init(period);
  led = new LedImpl(pin);
  state = OFF;
  counter=0;
}

void FlushWCTask::tick() {
  switch (state) {
    case OFF:
      counter = 0;
      led->switchOff();
      if (poop) {
        state = ON;
      }
      break;
    case ON:
      led->switchOn();
      counter++;
      if (counter >= 40) { //4 pulsazioni (8 passaggi) * 5 secondi con un periodo di 125ms
        poop = false;
        state = OFF;
      } else {
        state = WAIT;
      }
      break;
    case WAIT:
      led->switchOff();
      counter++;
      state = ON;
      break;
  }
}
