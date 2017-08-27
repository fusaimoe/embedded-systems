#ifndef __COMUNICATIONPROTOCOL__
#define __COMUNICATIONPROTOCOL__
#include "./SerialComunicationChannel.h"
class SendableMessage {
public:
	SendableMessage(byte* message, int lenght) {
		this->message = new byte[lenght];
    for(int i=0; i<lenght; i++) {
      this->message[i] = message[i];
    }
		this->lenght = lenght;
	}

  ~SendableMessage() {
    delete this->message;
  }
 
	byte* getMessage() {
		return this->message;
	}
	int getMessageLenght() {
		return this->lenght;
	}

private:
	byte* message;
	int lenght;
};

class ComunicationProtocol {
public:
	virtual SendableMessage getEncodedMessage(String msg) = 0;
	virtual Msg* receiveDecodedMessage(SerialComunicationChannel* serialChannel) = 0;
};

#endif
