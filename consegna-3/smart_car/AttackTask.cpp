#include "AttackTask.h"
#include "Arduino.h"

AttackTask::AttackTask(SharedContext* shared, AppSlider* slider, Servo* servo) {
  this->shared = shared;
  this->slider = slider;
  this->servo = servo;
}

void AttackTask::init(int period) {
  Task::init(period);
  state = OFF;
}

void DetectSliderTask::tick() {
  switch (state) {
    case OFF:
      if (shared->isContact()) {
        state = ON;
      }
      break;
    case ON:
      servo->setValue(slider->getValue());
      if (slider->getValue() = 180) {
        state = FULL;
      }
      break;
    case FULL:
      shared->setContact(false);
      shared->resetAttack();
      servo->resetValue();
      state = OFF;
      break;
  }
}
