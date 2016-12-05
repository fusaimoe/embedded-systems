/*
 Consegna 2 - Smart Toilet - Programmazione di Sistemi Embdedded
 Authors: Giulia Cecchetti, Andrea Colombo
*/

#include "Scheduler.h"

// Sensors
#include "DetectMotionTask.h"
#include "DetectProximityTask.h"
#include "DetectButtonOneTask.h"
#include "DetectButtonTwoTask.h"
#include "DetectDeathTask.h"
#include "DetectMessageTask.h"
// Actuators
#include "IlluminateLampTask.h"
#include "FlushWCTask.h"
#include "IlluminateWarningTask.h"

// Switches
#define S1 2
#define S2 3
// Leds
#define L1 4
#define L2 5
#define L3 6
// Sensors
#define PIR 7
#define UTRIG 8
#define UECHO 9

// Global variables for the various states machines
bool motion = false, prox = false, poop = false, alarm = false;
int usersWC = 0, usersTLT = 0;

Scheduler sched;

void setup(){
  Serial.begin(9600);

  sched.init(62);

  Task* t0 = new DetectMotionTask(PIR);
  t0->init(124);
  sched.addTask(t0);

  Task* t1 = new DetectProximityTask(UECHO, UTRIG);
  t1->init(248);
  sched.addTask(t1);

  Task* t2 = new DetectButtonOneTask(S1);
  t2->init(124);
  sched.addTask(t2);

  Task* t3 = new DetectButtonTwoTask(S2);
  t3->init(62);
  sched.addTask(t3);

  Task* t4 = new DetectDeathTask();
  t4->init(124);
  sched.addTask(t4);

  Task* t5 = new IlluminateLampTask(L1);
  t5->init(124);
  sched.addTask(t5);
  
  Task* t6 = new FlushWCTask(L2);
  t6->init(124);
  sched.addTask(t6);

  Task* t7 = new IlluminateWarningTask(L3);
  t7->init(124);
  sched.addTask(t7);

  Task* t8 = new DetectMessageTask();
  t8->init(124);
  sched.addTask(t8);

}


void loop(){
  sched.schedule();
};
