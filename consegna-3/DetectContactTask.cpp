#include "DetectContactTask.h"
#include "Arduino.h"

DetectContactTask::DetectContactTask(SharedContext* shared, Button* button) {
  this->shared = shared;
  this->button = button;
}

void DetectContactTask::init(int period) {
  Task::init(period);
  state = OFF;
}

void DetectContactTask::tick() {
  switch (state) {
    case OFF:
      if (button->isPressed() && (shared->isStopped() || shared->isMoving())) {
        shared->setContact(true);
        state = ON;
      }
      break;
    case ON:
      state = OFF;
      break;
  }
}
