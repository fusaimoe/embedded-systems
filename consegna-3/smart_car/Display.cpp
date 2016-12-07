#include "Display.h"
#include "Arduino.h"

Display::Display(MsgService* msgService){
  this->msgService = msgService;
}

void Display::showMsg(const String& msg){
  msgService->sendMsg("display:"+msg);
}

