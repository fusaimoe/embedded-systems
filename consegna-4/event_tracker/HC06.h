#ifndef __HC06__
#define __HC06__
#include "./InputDevice.h"
#include "./OutputDevice.h"
#include "Arduino.h"
#include "./SerialComunicationChannel.h"
#include "./Component.h"
#include "event.h"

#define BLUETOOTH_EVENT 3



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

class HC06 : public Component, virtual public InputDevice, virtual public OutputDevice
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

class BluetoothEvent: public Event {
public:
  BluetoothEvent(HC06* source) : Event(BLUETOOTH_EVENT){
    this->source = source;
  }

  HC06* getSource(){
    return source;
  }
private:
  HC06* source;
};

#endif
