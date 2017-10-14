#include "DetectContactTask.h"
#include "Arduino.h"

DetectContactTask::DetectContactTask(SharedContext* shared, Button* button, Display* display) {
  this->shared = shared;
  this->button = button;
  this->display = display;
}

void DetectContactTask::init(int period) {
  Task::init(period);
  state = IDLE;
}

void DetectContactTask::tick() {
  switch (state) {
    case IDLE:
      if (button->isPressed() && shared->isOn()) {
        state = ON;
      } else if(button->isPressed() &&  shared->isPark()) {
        state = PARK;
      }
      break;
    case ON:
      shared->setContact(true);
      display->showMsg("contactOn");
      state = IDLE;
      break;
    case PARK:
      shared->setContact(true);
      display->showMsg("contactPark");
      state = IDLE;
      break;
  }
}
