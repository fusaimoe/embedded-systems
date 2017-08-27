#include "StandardComunicationProtocol.h"
#include "Arduino.h"


StandardComunicationProtocol::StandardComunicationProtocol()
{
}

SendableMessage StandardComunicationProtocol::getEncodedMessage(String msg)
{
	int lenght = msg.length();
  byte output[lenght+1];

	msg.getBytes((output), lenght+1);
	return SendableMessage(output, lenght+1);
}

Msg * StandardComunicationProtocol::receiveDecodedMessage(SerialComunicationChannel * serialChannel)
{
	return new Msg(Serial.readString());
}
