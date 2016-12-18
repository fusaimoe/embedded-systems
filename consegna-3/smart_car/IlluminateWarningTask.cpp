#include "IlluminateWarningTask.h"

IlluminateWarningTask::IlluminateWarningTask(SharedContext* shared, Led* led) {
  this->shared = shared;
  this->led = led;
}

void IlluminateWarningTask::init(int period) {
  Task::init(period);
  state = OFF;
}

void IlluminateWarningTask::tick() {
  switch (state) {
    case OFF:
      if (shared->isDanger() || (shared->isContact() && shared->isStopped())) {
        led->switchOn();
        state = ON;
      }
      break;
    case ON:
      if (shared->isContact() && shared->isStopped()) {
        state = WAIT;
      } else if (!shared->isDanger()){
        led->switchOff();
        state = OFF;
      }
      break;
    case WAIT:
      counter++;
      if (counter >= 8) { //8 corresponds to 2 seconds
        led->switchOff();
        counter = 0;
        state = OFF;
      }
      break;
  }
}
