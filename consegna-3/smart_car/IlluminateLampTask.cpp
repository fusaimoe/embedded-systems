#include "IlluminateLampTask.h"

IlluminateLampTask::IlluminateLampTask(SharedContext* shared, Led* led) {
  this->shared = shared;
  this->led = led;
}

void IlluminateLampTask::init(int period) {
  Task::init(period);
  state = OFF;
}

void IlluminateLampTask::tick() {
  switch (state) {
    case OFF:
      if (shared->isMoving() || shared->isStopped()) {
        led->switchOn();
        state = ON;
      }
      break;
    case ON:
      if (!shared->isStopped() && !shared->isMoving()) {
        led->switchOff();
        state = OFF;
      } else if (shared->isStopped()){
        led->switchOff();
        state = WAIT;
      }
      break;
    case WAIT:
      led->switchOn();
      state = ON;
      break;
  }
}
