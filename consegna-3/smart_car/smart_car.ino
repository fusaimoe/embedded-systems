/*
 Consegna 3 - Smart Car - Programmazione di Sistemi Embdedded
 Authors: Giulia Cecchetti, Andrea Colombo
*/

#include "Scheduler.h"

#include "DetectCarTask.h"
#include "DetectProximityTask.h"
#include "DetectContactTask.h"
#include "IlluminateLampTask.h"
#include "IlluminateWarningTask.h"
#include "AttackTask.h"

//Pin config
#include "config.h"

//Components
#include "Led.h"
#include "ProximitySensor.h"
#include "Button.h"
#include "Slider.h"

Scheduler sched;

void setup(){
  Serial.begin(9600);

  sched.init(62);

  SharedContext* shared = new SharedContext();

  Led* l1 = new Led(LED1);
  Led* l2 = new Led(LED2);
  PriximitySensor* proximitySensor = new ProximitySensorImpl(UECHO, UTRIG);
  Button* button = new ButtonImpl(SWITCH);

  Task* t0 = new DetectCarTask();
  t0->init(124);
  sched.addTask(t0);

  Task* t1 = new DetectSliderTask();
  t1->init(248);
  sched.addTask(t1);

  Task* t2 = new DetectProximityTask();
  t2->init(124);
  sched.addTask(t2);

  Task* t3 = new DetectContactTask(shared, button);
  t3->init(62);
  sched.addTask(t3);

  Task* t4 = new IlluminateLampTask();
  t4->init(124);
  sched.addTask(t4);

  Task* t5 = new IlluminateWarningTask(L1);
  t5->init(124);
  sched.addTask(t5);

  Task* t6 = new AttackTask(L2);
  t6->init(124);
  sched.addTask(t6);
}

void loop(){
  sched.schedule();
};
