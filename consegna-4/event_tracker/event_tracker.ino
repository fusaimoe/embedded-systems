#include <MsTimer2.h>
#include "MyHardwareSerial.h"
#include "StandardComunicationProtocol.h"
#include "DHT11.h"
#include "event.h"
#include "HC06.h"
#include "Pir.h"
#include "Led.h"


ComunicationDevice* hs;
DHT11* tmp;
ComunicationDevice* hc;
Pir* p;
Led* bz;
void setup() {
  hs = MyHardwareSerial::getIstance(new StandardComunicationProtocol());
  tmp = new DHT11(7);
  hc = new HC06(2, 9);
  p = new Pir(3);
  bz = new Led(12);
  addEventHandler(EventType::TIMER_EVENT, timerEventHandler);
  addEventHandler(EventType::ALARM_EVENT, alarmEventHandler);
  addEventHandler(EventType::STOP_ALARM_EVENT, stopAlarmEventHandler);
  addEventHandler(EventType::PRESENCE_EVENT, presenceEventHandler);
  addEventHandler(EventType::PIR_EVENT, pirEventHandler);
  MsTimer2::set(10000, timerEvent); // 500ms period
  MsTimer2::start();

}

void loop() {
  while(1) {
    if(hs->isMsgAvailable()) {
    InputMessages ms = hs->getMessage()->convertToStandardMsg();
    switch (ms)
    {
      case InputMessages::STOP_ALARM:
        dispatchEvent(new StopAlarmE(NULL));
        break;
      default:
        break;
    }
  }
  mainEventLoop();
  if(hc->isMsgAvailable()) {
    InputMessages ms = hc->getMessage()->convertToStandardMsg();
    switch (ms)
    {
      case InputMessages::ALARM:
        dispatchEvent(new AlarmE(NULL));
        break;
       case InputMessages::PRESENCE:
        dispatchEvent(new PresenceE(NULL));
        break;
      default:
        break;
    }
  } 
 }
}


void timerEvent(){
  Event* ev = new TimerClock(NULL);
  dispatchEvent(ev);
}

void timerEventHandler(Event* ev) {
  hs->sendMessage(OutputMessages::TEMPERATURE, tmp->getTemperature());
}

void pirEventHandler(Event* ev) {
  hc->sendMessage(OutputMessages::PRESENCE);
}

void alarmEventHandler(Event* ev) {
  hs->sendMessage(OutputMessages::ALARM);
  bz->switchOn();
}

void stopAlarmEventHandler(Event* ev) {
  bz->switchOff();
}

void presenceEventHandler(Event* ev) {
  hs->sendMessage(OutputMessages::PRESENCE);
}
