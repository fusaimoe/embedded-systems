

#ifndef __MYSOFTWARESERIAL__
#define __MYSOFTWARESERIAL__
#include "./SerialComunicationChannel.h"
#include "./ComunicationProtocol.h"
#include "Arduino.h"
#include <SoftwareSerial.h>
class MySoftwareSerial : virtual public SerialComunicationChannel
{
public:
  MySoftwareSerial(ComunicationProtocol* protocol, int rxpin, int txpin);
	bool isMsgAvailable();
	Msg* receiveMsg();
	bool sendMsg(Msg msg);
	int read();
	void write(const char* message, int lenght);
private:
	ComunicationProtocol* protocol;
  SoftwareSerial* ss;
};



#endif // !__MYHARDWARESERIAL__
