#include "DetectButtonTwoTask.h"
#include "Arduino.h"

extern bool alarm;

DetectButtonTwoTask::DetectButtonTwoTask(int pin) {
  this->pin = pin;
}

void DetectButtonTwoTask::init(int period) {
  Task::init(period);
  btn = new ButtonImpl(pin);
  state = OFF;
}

void DetectButtonTwoTask::tick() {
  switch (state) {
    case OFF:
      if (btn->isPressed()) {
        state = DEACTIVATE;
      }
      break;
    case DEACTIVATE:
      alarm = false;
      Serial.println(alarm);
      //if (!btn->isPressed()) {
        state = OFF;
      //}
      break;
  }
}
