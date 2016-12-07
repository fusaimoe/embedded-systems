#include "DetectContactTask.h"
#include "Arduino.h"

DetectContactTask::DetectContactTask(SharedContext* shared, Button* button, Display* display) {
  this->shared = shared;
  this->button = button;
  this->display = display;
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
        display->showMsg("contact");
        state = ON;
      }
      break;
    case ON:
      state = OFF;
      break;
  }
}
