#ifndef __RASPBERRYEVENTSMANAGER__
#define __RASPBERRYEVENTSMANAGER__

#include "InputDevice.h"

class RaspberryEventsManager{
public:
	static RaspberryEventsManager* getInstance();
	static void inizialize(InputDevice* raspbi);
	void checkEvents();
private:
	static RaspberryEventsManager* instance;
	RaspberryEventsManager(InputDevice* raspbi);
  InputDevice* raspbi;
};

#endif
