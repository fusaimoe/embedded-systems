#ifndef __MSGSERVICE__
#define __MSGSERVICE__

#include "Arduino.h"
#include "SoftwareSerial.h"

class Msg {
  String content;

public:
  Msg(const String& content){
    this->content = content;
  }
  
  String getContent(){
    return content;
  }
};

class MsgService {
    
public: 
  MsgService(int rxPin, int txPin);  
  void init();  
  bool isMsgAvailable();
  Msg* receiveMsg();
  bool sendMsg(Msg msg);

private:
  String content;
  SoftwareSerial* channel;
  
};

#endif

