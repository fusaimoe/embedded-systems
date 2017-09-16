package com.fusaimoe.event_tracker;

import java.io.IOException;

import com.fusaimoe.event_tracker.common.*;
import com.fusaimoe.event_tracker.devices.*;

public class EventTracker extends BasicEventLoopController {
	
	private final Light l1;
	private final Light l3;
	private final JSONServer server;
	private final Serial serial;
	
	private enum State {ALARM, IDLE};
	private State currentState;

	public EventTracker(Serial serial, Light l1, Light l3, ObservableButton button){
		
		this.serial=serial;
		this.l1 = l1;
		this.l3 = l3;
		
		this.server = new JSONServer();
		
		button.addObserver(this);
		
		currentState = State.IDLE;
	}
	
	protected void processEvent(Event ev){
		switch (currentState){
		case IDLE:
			try {
				if (ev instanceof AlarmEvent){
					sendMessageToServer(((MessageEvent)ev));
					this.currentState = State.ALARM;
					l3.switchOn();
					System.out.println("DEBUG: alarm start");
				} else if (ev instanceof InformationEvent){
					sendMessageToServer(((MessageEvent)ev));
				}
			} catch (Exception ex){
				ex.printStackTrace();
			}
			break;
		case ALARM:
			try {
				if (ev instanceof InformationEvent){
					sendMessageToServer(((MessageEvent)ev));
				} else if (ev instanceof ButtonPressed){
					currentState = State.IDLE;
					serial.sendMsg("s");
					l3.switchOff();
					System.out.println("DEBUG: alarm end");
				}
			} catch (Exception ex){
				ex.printStackTrace();
			}
			break;
		}
	}
	
	private void sendMessageToServer(MessageEvent msgEv) {
		ArduinoMessage msg = msgEv.getMessage();
		this.server.post(msg);
	}
	
	@Override
	public synchronized void start() {
		super.start();
		try {
			l1.switchOn();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
}
