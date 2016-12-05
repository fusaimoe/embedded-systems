#include "DetectDeathTask.h"

extern bool alarm, prox, motion;

void DetectDeathTask::init(int period) {
  Task::init(period);
  state = OFF;
  counter = 0;
}

void DetectDeathTask::tick() {
  switch (state) {
    case OFF:
      counter = 0;
      if (prox && !motion) {
        state = CHECK;
      }
      break;
    case CHECK:
      counter++;
      if (counter >= 160) { //160 = 20s con un periodo di 125ms
        state = DEATH;
      }
      if (motion || !prox) {
        state = OFF;
      }
      break;
    case DEATH:
      alarm = true;
      state = OFF;
      break;
  }
}
