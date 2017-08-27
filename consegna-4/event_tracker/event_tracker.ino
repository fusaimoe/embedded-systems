#include <FlexiTimer2.h>
#include "MyHardwareSerial.h"
#include "StandardComunicationProtocol.h"
#include "DHT11.h"
#include "event.h"
#include "HC06.h"
#include "Pir.h"
#include "Led.h"

MyHardwareSerial* hs;
DHT11* tmp;
HC06* hc;
Pir* p;
Light* l1;
Light* l2;
Light* l3;
void setup() {
  hs = MyHardwareSerial::getIstance(new StandardComunicationProtocol());
  tmp = new DHT11(7);
  hc = new HC06(2, 8);
  p = new Pir(3);
  l1 = new Led(9);
  l2 = new Led(10);
  l3 = new Led(11);
  addEventHandler(TIMER_EVENT, timerEventHandler);
  addEventHandler(SERIAL_EVENT, serialEventHandler);
  addEventHandler(BLUETOOTH_EVENT, bluetoothEventHandler);
  addEventHandler(PIR_EVENT, pirEventHandler);
  FlexiTimer2::set(10000, timerEvent);
  FlexiTimer2::start();
  l1->switchOn();
  l2->switchOn();
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

  l2->switchState();
  Msg* m = ((SerialInputEvent*)ev)->getSource()->receiveMsg();
  ((SerialInputEvent*)ev)->getSource()->sendMsg(Msg("ciao"));
}

void bluetoothEventHandler(Event* ev) {
  Msg* m = hs->receiveMsg();
  hs->sendMsg(Msg("ciao"));
}

void pirEventHandler(Event* ev) {
  Msg* m = hs->receiveMsg();
  hs->sendMsg(Msg("pir"));
}
