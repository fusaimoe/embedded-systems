#include "DetectMotionTask.h"

extern bool motion;

DetectMotionTask::DetectMotionTask(int pin) {
  this->pin = pin;
}

void DetectMotionTask::init(int period) {
  Task::init(period);
  presence = new PresenceSensorImpl(pin);
  state = UNDETECTED;
}

void DetectMotionTask::tick() {
  switch (state) {
    case UNDETECTED:
      motion = false;
      if (presence->isPresent()) {
        state = DETECTED;
      }
      break;
    case DETECTED:
      motion = true;
      if (!presence->isPresent()) {
        state = UNDETECTED;
      }
      break;
  }
}
