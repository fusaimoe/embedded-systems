#include "Arduino.h"
#include "MsgService.h"


MsgService::MsgService(int rxPin, int txPin){
  channel = new SoftwareSerial(rxPin, txPin);
}

void MsgService::init(){
  content.reserve(256);
  channel->begin(9600);
}

bool MsgService::sendMsg(Msg msg){
  byte output[256];
  String content = msg.getContent();
  int len = content.length();
  if (len >= 0 && len <= 255){
    output[0] = (byte) len;
    content.getBytes((output+1),len+1);
    channel->write((const char*)output,len+1);
    return true;
  } else {
    return false;
  }
}

bool MsgService::isMsgAvailable(){
  return channel->available();
}

Msg* MsgService::receiveMsg(){
  if (channel->available()){    
    content="";
    int size = channel->read();
    // Serial.println("> "+String(size));
    int nDataRec = 0;
    while (nDataRec < size) {
      if (channel->available()){
        content += (char)channel->read();      
        nDataRec++;
      }
    }
    return new Msg(content);
  } else {
    return NULL;  
  }
}




