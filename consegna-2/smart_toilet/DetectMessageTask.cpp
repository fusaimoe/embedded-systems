#include "DetectMessageTask.h"
#include "Arduino.h"

extern bool alarm, prox, motion;
extern int usersTLT;

void DetectMessageTask::init(int period) {
  Task::init(period);
  state = OFF;
  MsgService.init();
}

void DetectMessageTask::tick() {
  switch (state) {
    case OFF:
      if (MsgService.isMsgAvailable()){
        Msg* msg = MsgService.receiveMsg();
        if (msg->getContent()=="users"){
          state = USERS;
        }
        if (msg->getContent()=="status"){
          state = STATUS;
        }
        delete msg;
      }
      break;
    case USERS:
      MsgService.sendMsg(String(usersTLT));
      state = OFF;
      break;
    case STATUS:
      if(alarm){
        MsgService.sendMsg("Allarme");
      } else if(prox || motion){
        MsgService.sendMsg("Occupato");
      } else {
        MsgService.sendMsg("Libero");
      }
      state = OFF;
      break;
  }
}
