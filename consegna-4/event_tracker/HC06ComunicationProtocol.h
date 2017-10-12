#ifndef __HC06COMUNICATIONPROTOCOL__
#define __HC06COMUNICATIONPROTOCOL__
#include "./SerialComunicationChannel.h"
#include "./ComunicationProtocol.h"


class HC06ComunicationProtocol : virtual public ComunicationProtocol{
	public:
		HC06ComunicationProtocol(int maxMessageSize);
		SendableMessage getEncodedMessage(String msg);
		Msg* receiveDecodedMessage(SerialComunicationChannel* serialChannel);
	private:
		int maxMessageSize;
	};
#endif
