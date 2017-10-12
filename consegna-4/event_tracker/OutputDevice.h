#ifndef __OUTPUTDEVICE__
#define __OUTPUTDEVICE__
enum class OutputMessages { PRESENCE, TEMPERATURE, ALARM};

class OutputDevice {
	public:
		virtual void sendMessage(OutputMessages message) = 0;
		virtual void sendMessage(OutputMessages message, float value) = 0;
	};
	
#endif
