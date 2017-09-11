#ifndef  __INPUTDEVICE__
#define __INPUTDEVICE__
#include "SerialComunicationChannel.h"

enum class InputMessages { ALARM, PRESENCE, STOP_ALARM };

class InputMsg {
public:
InputMsg(Msg* msg)
{
  //TODO controllo NULL
  this->msg = msg->getContent();
  delete msg;
}

InputMsg(String msg)
{
  this->msg = msg;
}

bool isStandardMessage()
{
  return this->convertToStandardMsg() != InputMessages(-1);
}

InputMessages getStandardMessage()
{
  return this->convertToStandardMsg();
}

bool isValue()
{
  return this->convertToStandardMsg() == InputMessages(-1);
}

int getValue()
{
  return this->msg.toInt();
}

InputMessages convertToStandardMsg()
{
  //TODO trova modo di parse enum
  //Serial.println(msg);
  if (msg == "a") {
    return InputMessages::ALARM;
  }
  else if (msg == "n") {
    return InputMessages::PRESENCE;
  }
  else if (msg == "s") {
    return InputMessages::STOP_ALARM;
  }
  return InputMessages(-1);
}

private:
  String msg;
};

class InputDevice {
public:
  virtual bool isMsgAvailable() = 0;
  virtual InputMsg* getMessage() = 0;
};





#endif // ! __InputDevice__
