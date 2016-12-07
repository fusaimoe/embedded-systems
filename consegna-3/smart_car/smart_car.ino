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

  sched.init(50);

  SharedContext* shared = new SharedContext();

  MsgService* message = new MsgService();
  msgService->init();

  Led* led1 = new Led(LED1);
  Led* led2 = new Led(LED2);
  PriximitySensor* proximity = new ProximitySensorImpl(UECHO, UTRIG);
  Button* button = new ButtonImpl(SWITCH);
  AppButton* buttonPark = new AppButtonImpl(message, "park");
  AppButton* buttonMove = new AppButtonImpl(message, "move");
  AppButton* buttonOn = new AppButtonImpl(message, "on");
  AppSlider* slider = new AppButtonImpl(message);
  Display* display = new Display(message);


  Task* t0 = new DetectCarTask(shared, buttonPark, buttonMove, buttonOn);
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

  Task* t5 = new AttackTask(shared, servo, slider);
  t5->init(50);
  sched.addTask(t5);
}

void loop(){
  sched.schedule();
};
