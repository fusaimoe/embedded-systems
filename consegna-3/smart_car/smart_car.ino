/*
 Consegna 3 - Smart Car - Programmazione di Sistemi Embedded
 Authors: Giulia Cecchetti, Andrea Colombo
*/

#include "Scheduler.h"

#include "MsgService.h"
#include "SoftwareSerial.h"

#include "DetectCarTask.h"
#include "DetectProximityTask.h"
#include "DetectContactTask.h"
#include "IlluminateLampTask.h"
#include "IlluminateWarningTask.h"
#include "AttackTask.h"
#include "DetectMessageTask.h"

//Pin config
#include "config.h"

//Components
#include "Led.h"
#include "ProximitySensor.h"
#include "Button.h"
//#include "ServoImpl.h"

Scheduler sched;

void setup(){
  Serial.begin(9600);
  while (!Serial){}

  sched.init(50);

  SharedContext* shared = new SharedContext();

  MsgService* msgService = new MsgService(RX, TX);
  msgService->init();

  Led* led1 = new LedImpl(LED1);
  Led* led2 = new LedImpl(LED2);
  ProximitySensor* proximity = new ProximitySensorImpl(UECHO, UTRIG);
  Button* button = new ButtonImpl(SWITCH);
  Display* display = new Display(msgService);
  //ServoImpl* servo = new ServoImpl(SERVO);

  Task* t0 = new DetectCarTask(shared);
  t0->init(50);
  sched.addTask(t0);

  Task* t1 = new DetectProximityTask(shared, proximity, display);
  t1->init(50);
  sched.addTask(t1);

  Task* t2 = new DetectContactTask(shared, button, display);
  t2->init(50);
  sched.addTask(t2);

  Task* t3 = new IlluminateLampTask(shared, led1);
  t3->init(100);
  sched.addTask(t3);

  Task* t4 = new IlluminateWarningTask(shared, led2);
  t4->init(100);
  sched.addTask(t4);

  Task* t5 = new AttackTask(shared/*, servo*/);
  t5->init(50);
  sched.addTask(t5);

  Task* t6 = new DetectMessageTask(shared, msgService);
  t6->init(50);
  sched.addTask(t6);
}

void loop(){
  sched.schedule();
};
