#include "DetectMessageTask.h"
#include "Arduino.h"

DetectMessageTask::DetectMessageTask(SharedContext* shared, MsgService* msgService) {
  this->shared = shared;
  this->msgService = msgService;
}

void DetectMessageTask::init(int period) {
  Task::init(period);
}

void DetectMessageTask::tick() {

  if (msgService->isMsgAvailable()){
    Msg* msg = msgService->receiveMsg();
    if(msg->getContent() == "park"){
       shared->setPark(true);
    } else if(msg->getContent() == "notPark"){
       shared->setPark(false);
    } else if(msg->getContent() == "on"){
       shared->setOn(true);
    } else if(msg->getContent() == "notOn"){
       shared->setOn(false);
    } else if(msg->getContent() == "moving"){
       shared->setMoving(true);
    } else if(msg->getContent() == "notMoving"){
       shared->setMoving(false);
    } else if(msg->getContent().indexOf(prefix)>0){
       String removedPrefix = msg->getContent().substring(prefix.length(), msg->getContent().length());
       shared->setAttack(removedPrefix.toInt());
    }
    delete msg;
  }

}
