#ifndef __MYHARDWARESERIAL__
#define __MYHARDWARESERIAL__
#include "./SerialComunicationChannel.h"
#include "./OutputDevice.h"
#include "./InputDevice.h"
#include "./ComunicationProtocol.h"
#include "Arduino.h"
#include "event.h"

#define SERIAL_EVENT 2

class MyHardwareSerial : virtual public SerialComunicationChannel, virtual public InputDevice,  virtual public OutputDevice
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

class SerialInputEvent: public Event {
public:
  SerialInputEvent(MyHardwareSerial* source) : Event(SERIAL_EVENT){
    this->source = source;
  }

  MyHardwareSerial* getSource(){
    return source;
  }
private:
  MyHardwareSerial* source;
};

#endif // !__MYHARDWARESERIAL__
