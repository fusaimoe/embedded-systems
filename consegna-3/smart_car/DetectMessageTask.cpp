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
    Msg* message = msgService->receiveMsg();
    String msg = message->getContent();
    if(msg == "park"){
       shared->setPark(true);
    } else if(msg == "notPark"){
       shared->setPark(false);
    } else if(msg == "on"){
       shared->setOn(true);
    } else if(msg == "notOn"){
       shared->setOn(false);
    } else if(msg == "moving"){
       shared->setMoving(true);
    } else if(msg == "notMoving"){
       shared->setMoving(false);
    } else {
       
       shared->setAttack(msg.toInt());
    }
    delete message;
  }

}
