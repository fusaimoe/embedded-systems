#include <FlexiTimer2.h>
#include "MyHardwareSerial.h"
#include "StandardComunicationProtocol.h"
#include "DHT11.h"
#include "event.h"
#include "HC06.h"
#include "Pir.h"
#include "Led.h"
//#include "Buzzer.h"


ComunicationDevice* hs;
DHT11* tmp;
ComunicationDevice* hc;
Pir* p;
//Buzzer* bz;
void setup() {
  hs = MyHardwareSerial::getIstance(new StandardComunicationProtocol());
  tmp = new DHT11(7);
  hc = new HC06(2, 9);
  p = new Pir(3);
  //bz = new Buzzer(12);
  addEventHandler(TIMER_EVENT, timerEventHandler);
  addEventHandler(SERIAL_EVENT, serialEventHandler);
  addEventHandler(BLUETOOTH_EVENT, bluetoothEventHandler);
  addEventHandler(PIR_EVENT, pirEventHandler);
  FlexiTimer2::set(10000, timerEvent);
  FlexiTimer2::start();
}

void loop() {
  mainEventLoop();
}

void serialEvent() {
  Event* ev = new SerialInputEvent(hs);
  dispatchEvent(ev);
}

void timerEvent(){
  Event* ev = new TimerClock(0);
  dispatchEvent(ev);
}

void timerEventHandler(Event* ev) {
  hs->sendMessage(OutputMessages::TEMPERATURE, tmp->getTemperature());
}

void serialEventHandler(Event* ev) {
  ComunicationDevice* com = ((SerialInputEvent*)ev)->getSource();
  if(com->isMsgAvailable()) {
    InputMessages ms = com->getMessage()->convertToStandardMsg();
    switch (ms)
    {
      case InputMessages::STOP_ALARM:
        //bz->switchOff();
        break;
      default:
        break;
    }
  }
}

void bluetoothEventHandler(Event* ev) {
  ComunicationDevice* com = ((BluetoothEvent*)ev)->getSource();
  if(com->isMsgAvailable()) {
    InputMessages ms = com->getMessage()->convertToStandardMsg();
    switch (ms)
    {
      case InputMessages::ALARM:
        hs->sendMessage(OutputMessages::ALARM);
          //bz->switchOn();
        break;
       case InputMessages::PRESENCE:
        hs->sendMessage(OutputMessages::PRESENCE);
        break;
      default:
        break;
    }
  }
}

void pirEventHandler(Event* ev) {
  hc->sendMessage(OutputMessages::PRESENCE);
}
