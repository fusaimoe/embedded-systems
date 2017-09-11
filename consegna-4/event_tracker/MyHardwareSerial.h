#ifndef __MYHARDWARESERIAL__
#define __MYHARDWARESERIAL__
#include "./SerialComunicationChannel.h"
#include "./ComunicationDevice.h"
#include "./ComunicationProtocol.h"
#include "Arduino.h"
#include "event.h"

class MyHardwareSerial : virtual public SerialComunicationChannel, virtual public ComunicationDevice
{
public:
	static MyHardwareSerial* getIstance(ComunicationProtocol* protocol);
	bool isMsgAvailable();
	Msg* receiveMsg();
	bool sendMsg(Msg msg);
	int read();
	void write(const char* message, int lenght);
	InputMsg* getMessage();
	void sendMessage(OutputMessages message);
	void sendMessage(OutputMessages message, float value);
private:
	MyHardwareSerial(ComunicationProtocol* protocol);
	ComunicationProtocol* protocol;
	static MyHardwareSerial* istance;
};

#endif // !__MYHARDWARESERIAL__
