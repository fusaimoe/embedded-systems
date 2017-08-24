/*
 Consegna 4 - Event Tracker - Programmazione di Sistemi Embedded
 Authors: Giulia Cecchetti, Andrea Colombo
*/
#include "event.h"
#include "button.h"
#include "buttonImpl.h"
#include "display.h"
#include "MsgService.h"
#include "SoftwareSerial.h"


#include "config.h"

int count = 0;
Display* android;
Button* button;
MsgService* msgService;

void buttonPressedHandler(Event* ev){
  count = count + 1;
  android->showMsg("contactOn");
}



void setup() {
  Serial.begin(9600);
  button = new ButtonImpl(PIR);

  android = new Display(msgService);

  msgService = new MsgService(RX, TX);
  msgService->init();

  addEventHandler(BUTTON_PRESSED_EVENT, buttonPressedHandler);
}

void loop() {
  mainEventLoop();
}
