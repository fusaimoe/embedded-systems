#include "HC06ComunicationProtocol.h"
#include "Arduino.h"

/**
 * il protocollo di comunicazione modellato è identico a quello proposto a lezione.
 */

HC06ComunicationProtocol::HC06ComunicationProtocol(int maxMessageSize)
{
	this->maxMessageSize = maxMessageSize;
}


SendableMessage HC06ComunicationProtocol::getEncodedMessage(String msg)
{
	int len = msg.length();
	if (len >= 0 && len <= this->maxMessageSize) {
    byte output[len+2];//TODO forse +2
		output[0] = (byte)len;
		msg.getBytes((output + 1), len + 2);
    //Serial.println("finished");
		return SendableMessage(output, len + 2);
	}
	else {
		return SendableMessage(new byte[1], -1);
	}
}

Msg * HC06ComunicationProtocol::receiveDecodedMessage(SerialComunicationChannel * serialChannel)
{
	if (serialChannel->isMsgAvailable()) {
		String content = "";
		int size = serialChannel->read();
		// Serial.println("> "+String(size));
		int nDataRec = 0;
		while (nDataRec < size) {
			if (serialChannel->isMsgAvailable()) {
				content += (char)serialChannel->read();
				nDataRec++;
			}
		}
		return new Msg(content);
	}
	else {
		return NULL;
	}
}
