#ifndef __ANDROIDEVENTSMANAGER__
#define __ANDROIDEVENTSMANAGER__

#include "InputDevice.h"

class AndroidEventsManager {
	public:
		static AndroidEventsManager* getInstance();
		static void inizialize(InputDevice* android);
		void checkEvents();
		
	private:
		static AndroidEventsManager* instance;
		AndroidEventsManager(InputDevice* android);
	  InputDevice* android;
};

#endif
