#ifndef __HC06__
#define __HC06__
#include "./ComunicationDevice.h"
#include "Arduino.h"
#include "./SerialComunicationChannel.h"
#include "./Component.h"
#include "event.h"

class HC06Msg : virtual public InputMsg
{
public:
	HC06Msg(Msg* msg);
  ~HC06Msg();
	HC06Msg(String msg);
	bool isStandardMessage();
	InputMessages getStandardMessage();
	bool isValue();
	int getValue();
private:
	InputMessages convertToStandardMsg();
	String msg;
};

class HC06 : public Component, virtual public ComunicationDevice
{
public:
	HC06(int rxPin, int txPin);
	bool isMsgAvailable();
	InputMsg* getMessage();
	void sendMessage(OutputMessages message);
	void sendMessage(OutputMessages message, float value);
private:
	SerialComunicationChannel* channel;
};

#endif
