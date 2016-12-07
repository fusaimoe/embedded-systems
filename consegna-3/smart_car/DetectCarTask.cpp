#include "DetectCarTask.h"
#include "Arduino.h"

DetectCarTask::DetectCarTask(SharedContext* shared, AppButton* buttonPark, AppButton* buttonMove, AppButton* buttonOn) {
  this->shared = shared;
  this->buttonPark = buttonPark;
  this->buttonMove = buttonMove;
  this->buttonOn = buttonOn;
}

void DetectCarTask::init(int period) {
  Task::init(period);
  state = OFF;
}

void DetectCarTask::tick() {
  switch (state) {
    case OFF:
      if (buttonPark->isPressed()) {
        shared->setStopped(true);
        state = OFFPARK;
      }
      if (buttonOn->isPressed()) {
        shared->setStopped(true);
        state = ONSTOP;
      }
      break;
    case ONSTOP:
      if (buttonMove->isPressed()) {
        shared->setStopped(false);
        shared->setMoving(true);
        state = ONMOVE;
      }
      if (!buttonOn->isPressed()) {
        shared->setStopped(false);
        state = OFF;
      }
      break;
    case ONMOVE:
      if (!buttonMove->isPressed()) {
        shared->setStopped(true);
        shared->setStopped(false);
        state = ONSTOP;
      }
      break;
    case OFFPARK:
      if (!buttonPark->isPressed()) {
        shared->setStopped(false);
        state = OFF;
      }
      break;
  }
}
