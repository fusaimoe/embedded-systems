#include "IlluminateLampTask.h"

extern bool motion, prox;

IlluminateLampTask::IlluminateLampTask(int pin) {
  this->pin = pin;
}

void IlluminateLampTask::init(int period) {
  Task::init(period);
  led = new LedImpl(pin);
  state = OFF;
  counter=0;
}

void IlluminateLampTask::tick() {
  switch (state) {
    case OFF:
      led->switchOff();
      if (motion || prox) {
        state = ON;
      }
      break;
    case ON:
      led->switchOn();
      counter = 0;
      if (!motion && !prox) {
        state = WAIT;
      }
      break;
    case WAIT:
      counter++;
      if (motion || prox) {
        state = ON;
      }
      if (!motion && !prox && counter >= 80) { //80 = 10s con un periodo di 125ms
        state = OFF;
      }
      break;
  }
}
