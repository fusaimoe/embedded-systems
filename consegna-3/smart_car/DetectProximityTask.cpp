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
        display->showMsg("risk");
        state = IN;
      }
      break;
    case IN: {
      // Concatenate a float and a string in the message
      float distance = proximity->getDistance();
      String prefix = "Distance:";
      char tmp[10];
      dtostrf(distance,4,2,tmp);
      display->showMsg(prefix + tmp);
      
      if (proximity->getDistance() < DMIN) {
        shared->setDanger(true);
        state = CLOSE;
      }
      if (proximity->getDistance() > DMAX) {
        display->showMsg("notRisk");
        state = OUT;
      }
      break;
    }
    case CLOSE:
      if (proximity->getDistance() > DMIN) {
        shared->setDanger(false);
        state = IN;
      }
      break;
  }
}
