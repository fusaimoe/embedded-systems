#include "Buzzer.h"
#include "Arduino.h"

Buzzer::Buzzer(int pin) : Component(new int[1]{pin}, ComponentTypes::BUZZER) {
  pinMode(pin,OUTPUT);
}

void Buzzer::switchOn(){
  tone(this->getPin()[0],1000);
}

void Buzzer::switchOff(){
    noTone(this->getPin()[0]);
}
