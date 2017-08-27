#include "MyHardwareSerial.h"

#include <ArduinoJson.h>

MyHardwareSerial* MyHardwareSerial::istance = NULL;

MyHardwareSerial::MyHardwareSerial(ComunicationProtocol* protocol)
{
	Serial.begin(9600);
	this->protocol = protocol;
}

MyHardwareSerial* MyHardwareSerial::getIstance(ComunicationProtocol* protocol)
{
	if(MyHardwareSerial::istance == NULL) {
		MyHardwareSerial::istance = new MyHardwareSerial(protocol);
	}
	return MyHardwareSerial::istance;
}

bool MyHardwareSerial::isMsgAvailable()
{
	return Serial.available();
}

InputMsg* MyHardwareSerial::getMessage()
{
	return new InputMsg(this->receiveMsg());
}

Msg * MyHardwareSerial::receiveMsg()
{
	return this->protocol->receiveDecodedMessage(this);
}

bool MyHardwareSerial::sendMsg(Msg msg)
{
	SendableMessage message = this->protocol->getEncodedMessage(msg.getContent());
	if (message.getMessageLenght() > 0) {
		this->write((const char*)message.getMessage(), message.getMessageLenght());
		return true;
	}
	return false;
}

int MyHardwareSerial::read()
{
	return Serial.read();
}

void MyHardwareSerial::write(const char * message, int lenght)
{
	Serial.write(message, lenght);
}

void MyHardwareSerial::sendMessage(OutputMessages message)
{
	switch (message)
	{
	case OutputMessages::PRESENCE:
		this->sendMsg(Msg("Crash"));
		break;
	case OutputMessages::ALARM:
		this->sendMsg(Msg("Away"));
		break;
	default:
		break;
	}
}

void MyHardwareSerial::sendMessage(OutputMessages message, float value)
{
  
  StaticJsonBuffer<200> jsonBuffer;
  char buffer[200];

  JsonObject& root = jsonBuffer.createObject();
	switch (message)
	{
		case OutputMessages::TEMPERATURE:
				root["temperature"] = value;
				root["time"] = NULL;
				root["presence"] = NULL;
				root["alarm"] = NULL;
				root.printTo(buffer, sizeof(buffer));
				this->sendMsg(Msg(String(buffer)));
			break;
		default:
			break;
	}
}
