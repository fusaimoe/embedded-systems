#include "AttackTask.h"
#include "Arduino.h"

AttackTask::AttackTask(SharedContext* shared, ServoImpl* servo) {
  this->shared = shared;
  this->servo = servo;
}

void AttackTask::init(int period) {
  Task::init(period);
  state = OFF;
}

void AttackTask::tick() {
  switch (state) {
    case OFF:
      if (shared->isContact() && shared->isOn()) {
        state = ON;
      }
      break;
    case ON:
      servo->setValue(shared->getAttack());
      if (shared->getAttack() == 180) {
        state = FULL;
      }
      break;
    case FULL:
      shared->setContact(false);
      shared->setAttack(0);
      servo->setValue(0);
      state = OFF;
      break;
  }
}
