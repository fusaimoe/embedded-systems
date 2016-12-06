#include "SharedContext.h"

SharedContext::SharedContext(){
  stopped = false;
  moving = false;
  contact = false;
  danger = false;
  attack = false;
};

bool SharedContext::isStopped(){
	return stopped;
};

void SharedContext::setStopped(bool stopped){
	this->stopped = stopped;
};

bool SharedContext::isMoving(){
	return moving;
};

void SharedContext::setMoving(bool moving){
	this->moving = moving;
};

bool SharedContext::isContact(){
	return contact;
};

void SharedContext::setContact(bool contact){
	this->contact = contact;
};

bool SharedContext::isDanger(){
	return danger;
};

void SharedContext::setDanger(bool danger){
	this->danger = danger;
};

int SharedContext::getAttack(){
  return this->attack;
};

void SharedContext::resetAttack(){
  this->attack = 0;
}
