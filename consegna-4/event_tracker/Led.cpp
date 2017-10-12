#include "Led.h"
#include "Arduino.h"

Led::Led(int pin) : Component(new int[1]{pin}, ComponentTypes::LED) {
  pinMode(pin,OUTPUT);
}

void Led::switchOn() {
	this->state = HIGH;
  digitalWrite(this->getPin()[0],HIGH);
}

void Led::switchOff() {
	this->state = LOW;
  digitalWrite(this->getPin()[0],LOW);
}

int Led::switchState() {
	if (this->state == HIGH) {
		this->switchOff();
	}
	else {
		this->switchOn();
	}
	return this->state;
}

bool Led::isOn() {
	return this->state;
}
