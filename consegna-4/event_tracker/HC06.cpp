#include "HC06.h"
#include "Arduino.h"
#include "./MyHardwareSerial.h"
#include "MySoftwareSerial.h"
#include "./HC06ComunicationProtocol.h"

#include "./StandardComunicationProtocol.h"

HC06::HC06(int rxPin, int txPin) : Component(new int[2]{ rxPin, txPin }, ComponentTypes::HC06) {
	ComunicationProtocol* protocol = new HC06ComunicationProtocol(255);
	if (rxPin == 0 && txPin == 1) {
		this->channel = MyHardwareSerial::getIstance(protocol);
	}
	else {
		this->channel = new MySoftwareSerial(protocol, rxPin, txPin);
	}
	while (!Serial) {}
}

bool HC06::isMsgAvailable() {
	return this->channel->isMsgAvailable();
}

InputMsg* HC06::getMessage() {
	return new InputMsg(this->channel->receiveMsg());
}

void HC06::sendMessage(OutputMessages message) {
	switch (message) {
	case OutputMessages::PRESENCE:
		this->channel->sendMsg(Msg("presence"));
		break;
	default:
		break;
	}
}

void HC06::sendMessage(OutputMessages message, float value)
{
	//this->channel->sendMsg(Msg(String(value)));
}
