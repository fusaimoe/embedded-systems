#include "DetectProximityTask.h"
#include "Arduino.h"

// units are cm, which are good for testing purposes
#define DMAX 0.30
#define DMIN 0.15

DetectProximityTask::DetectProximityTask(SharedContext* shared, ProximitySensor* proximity, Display* display) {
  this->shared = shared;
  this->proximity = proximity;
  this->display = display;
}

void DetectProximityTask::init(int period) {
  Task::init(period);
  state = OUT;
}

void DetectProximityTask::tick() {
  switch (state) {
    case OUT:
      if ( proximity->getDistance() < DMAX && shared->isMoving()) {
        display->showMsg("proximity");
        state = IN;
      }
      break;
    case IN:
      if (proximity->getDistance() < DMIN) {
        shared->setDanger(true);
        state = CLOSE;
      }
      if (proximity->getDistance() > DMAX) {
        state = OUT;
      }
      break;
    case CLOSE:
      if (proximity->getDistance() > DMIN) {
        shared->setDanger(false);
        state = IN;
      }
      break;
  }
}
