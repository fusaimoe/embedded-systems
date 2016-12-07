#ifndef __DISPLAY__
#define __DISPLAY__

#include "MsgService.h"

class Display { 
public:
  Display(MsgService* msgService);
  void showMsg(const String& msg);
private:
  MsgService* msgService;
};

#endif
