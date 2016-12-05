#include "DetectProximityTask.h"
#include "Arduino.h"

// units are cm, which are good for testing purposes
#define DMAX 0.20
#define DMIN 0.10

extern bool prox, poop, motion;
extern int usersTLT, usersWC;

DetectProximityTask::DetectProximityTask(int echo, int trig) {
  this->echo = echo;
  this->trig = trig;
}

void DetectProximityTask::init(int period) {
  Task::init(period);
  proximity = new ProximitySensorImpl(echo, trig);
  state = OUT;
}

void DetectProximityTask::tick() {
  switch (state) {
    case OUT:
      prox = false;
      if ( proximity->getDistance() < DMAX && proximity->getDistance() > DMIN) {
        usersTLT++;
        state = SINK;
      }
      break;
    case SINK:
      prox = true;
      if (proximity->getDistance() < DMIN) {
        state = WC;
      }
      if (proximity->getDistance() > DMAX) {
        state = OUT;
      }
      break;
    case WC:
      prox = true; // not needed
      if (proximity->getDistance() > DMAX) {
        state = EXIT;
      }
      break;
    case EXIT:
      usersWC++;
      poop = true;
      state = OUT;
      break;
  }
}
