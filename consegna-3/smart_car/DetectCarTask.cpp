#include "DetectCarTask.h"
#include "Arduino.h"

DetectCarTask::DetectCarTask(SharedContext* shared) {
  this->shared = shared;
}

void DetectCarTask::init(int period) {
  Task::init(period);
  state = OFF;
}

void DetectCarTask::tick() {
  switch (state) {
    case OFF:
      if (shared->isPark()) {
        shared->setStopped(true);
        state = OFFPARK;
      }
      if (shared->isOn()) {
        shared->setStopped(true);
        state = ONSTOP;
      }
      break;
    case ONSTOP:
      if (shared->isMoving()) {
        shared->setStopped(false);
        state = ONMOVE;
      }
      if (!shared->isOn()) {
        shared->setStopped(false);
        state = OFF;
      }
      break;
    case ONMOVE:
      if (!shared->isMoving()) {
        shared->setStopped(true);
        state = ONSTOP;
      }
      break;
    case OFFPARK:
      if (!shared->isPark()) {
        shared->setStopped(false);
        state = OFF;
      }
      break;
  }
}
