#include "SharedContext.h"

SharedContext::SharedContext(){
	this->alarm = false;
}


bool SharedContext::isAlarm()
{
	return this->alarm;
}

void SharedContext::setAlarm(bool alarm)
{
	this->alarm = alarm;
}
