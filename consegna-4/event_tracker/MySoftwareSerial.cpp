#include "MySoftwareSerial.h"
#include "Arduino.h"
#include "event.h"
 
MySoftwareSerial::MySoftwareSerial(ComunicationProtocol* protocol, int rxpin, int txpin)
{
	ss = new SoftwareSerial(rxpin, txpin);
	this->protocol = protocol;
}

bool MySoftwareSerial::isMsgAvailable()
{
	return ss->available();
}

Msg * MySoftwareSerial::receiveMsg()
{
	return this->protocol->receiveDecodedMessage(this);
}

bool MySoftwareSerial::sendMsg(Msg msg)
{
	SendableMessage message = this->protocol->getEncodedMessage(msg.getContent());
	if (message.getMessageLenght() > 0) {
		this->write((const char*)message.getMessage(), message.getMessageLenght());
		return true;
	}
	return false;
}

int MySoftwareSerial::read()
{
	return ss->read();
}

void MySoftwareSerial::write(const char * message, int lenght)
{
	ss->write(message, lenght);
}
