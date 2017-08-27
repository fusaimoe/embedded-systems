#pragma once
#include "./ComunicationProtocol.h"
class StandardComunicationProtocol : virtual public ComunicationProtocol
{
public:
	StandardComunicationProtocol();
	SendableMessage getEncodedMessage(String msg);
	Msg* receiveDecodedMessage(SerialComunicationChannel* serialChannel);
};

