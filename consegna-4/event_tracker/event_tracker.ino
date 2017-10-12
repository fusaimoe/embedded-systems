#include <MsTimer2.h>

 // COMPONENTS
#include "DHT11.h"
#include "HC06.h"
#include "Pir.h"
#include "Led.h"

//EVENTS MANAGEMENT
#include "event.h"
#include "RaspberryEventsManager.h"
#include "AndroidEventsManager.h"

//SERIAL COMUNICATION
#include "MyHardwareSerial.h"
#include "StandardComunicationProtocol.h"

// PIN
#include "config.h"

ComunicationDevice* raspbi;
ComunicationDevice* android;
TemperatureSensor* tmp;
Pir* p;
Led* act;

void setup() {
  raspbi = MyHardwareSerial::getIstance(new StandardComunicationProtocol());
  android = new HC06(RX_PIN, TX_PIN);
  RaspberryEventsManager::inizialize(raspbi);
  AndroidEventsManager::inizialize(android);
  tmp = new DHT11(DHT11_PIN);
  p = new Pir(PIR_PIN);
  act = new Led(LED_PIN);
  addEventHandler(EventType::TIMER_EVENT, timerEventHandler);
  addEventHandler(EventType::ALARM_EVENT, alarmEventHandler);
  addEventHandler(EventType::STOP_ALARM_EVENT, stopAlarmEventHandler);
  addEventHandler(EventType::PRESENCE_EVENT, presenceEventHandler);
  addEventHandler(EventType::PIR_EVENT, pirEventHandler);

  MsTimer2::set(10000, timerEvent);
  MsTimer2::start();
}

void loop() {
  while(1) {
    RaspberryEventsManager::getInstance()->checkEvents();

    mainEventLoop();

    AndroidEventsManager::getInstance()->checkEvents();
   }
}

void timerEvent(){
  Event* ev = new TimerClock(NULL);
  dispatchEvent(ev);
}

void timerEventHandler(Event* ev) {
  raspbi->sendMessage(OutputMessages::TEMPERATURE, tmp->getTemperature());
}

void pirEventHandler(Event* ev) {
  android->sendMessage(OutputMessages::PRESENCE);
}

void alarmEventHandler(Event* ev) {
  raspbi->sendMessage(OutputMessages::ALARM);
  act->switchOn();
}

void stopAlarmEventHandler(Event* ev) {
  act->switchOff();
}

void presenceEventHandler(Event* ev) {
  raspbi->sendMessage(OutputMessages::PRESENCE);
}
