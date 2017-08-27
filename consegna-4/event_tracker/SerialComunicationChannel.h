#ifndef __SERIALCOMUNICATIONCHANNEL__
#define __SERIALCOMUNICATIONCHANNEL__

#include "Arduino.h"

class Msg {
	String content;

public:
	Msg(const String& content) {
		this->content = content;
	}

	String getContent() {
		return content;
	}
};

class SerialComunicationChannel {

public:
	virtual bool isMsgAvailable() = 0;
	virtual Msg* receiveMsg() = 0;
	virtual bool sendMsg(Msg msg) = 0;
	virtual int read() = 0;
	virtual void write(const char* message, int lenght) = 0;
};

#endif

