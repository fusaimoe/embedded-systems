#include "StandardComunicationProtocol.h"
#include "Arduino.h"


StandardComunicationProtocol::StandardComunicationProtocol() {
}

SendableMessage StandardComunicationProtocol::getEncodedMessage(String msg) {
	int lenght = msg.length();
  byte output[lenght+2];

	msg.getBytes((output), lenght+2);
  output[lenght+1] = output[lenght];
  output[lenght] = '\n';
	return SendableMessage(output, lenght+2);
}

Msg * StandardComunicationProtocol::receiveDecodedMessage(SerialComunicationChannel * serialChannel) {
  if (serialChannel->isMsgAvailable()) {
    String content = "";
    char contentR;
    while (true) {
      if(serialChannel->isMsgAvailable()) {
        contentR = (char)serialChannel->read();
        if(contentR != '\n') {
          content+=contentR;
        } else {
          break;
        }
      }
    }
    return new Msg(content);
  }
  else {
    return NULL;
  }
}
