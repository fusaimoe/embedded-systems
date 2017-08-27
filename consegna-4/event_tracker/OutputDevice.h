#ifndef __OUTPUTDEVICE__
#define __OUTPUTDEVICE__
enum class OutputMessages { PRESENCE, TEMPERATURE, ALARM};
/*Interfaccia che modella un dispositivo in grado di inviare messaggi standardizzati e limitati all'apposita enumerazione*/
class OutputDevice {
public:
	virtual void sendMessage(OutputMessages message) = 0;
	virtual void sendMessage(OutputMessages message, float value) = 0;
};
#endif
