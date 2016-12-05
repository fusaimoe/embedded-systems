#include "DetectButtonOneTask.h"
#include "Arduino.h"

extern bool alarm;

DetectButtonOneTask::DetectButtonOneTask(int pin) {
  this->pin = pin;
}

void DetectButtonOneTask::init(int period) {
  Task::init(period);
  btn = new ButtonImpl(pin);
  state = NOTPRESSED;
  counter = 0;
}

void DetectButtonOneTask::tick() {
  switch (state) {
    case NOTPRESSED:
      counter = 0;
      if (btn->isPressed()) {
        state = PRESSING;
      }
      break;
    case PRESSING:
      counter++;
      if (btn->isPressed() && counter>=16) { //16 = 2s con un periodo di 125ms
        state = PRESSED;
      }
      if (!btn->isPressed()) {
        state = NOTPRESSED;
      }
      break;
    case PRESSED:
      alarm = true;
      //if (!btn->isPressed()) {
        state = NOTPRESSED;
      //}
      break;
  }
}
