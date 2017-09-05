package com.fusaimoe.event_tracker;

import java.io.IOException;

import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.HttpClientBuilder;

import com.fusaimoe.event_tracker.common.*;
import com.fusaimoe.event_tracker.devices.*;

public class EventTracker extends BasicEventLoopController {
	
	private final Light led;
	private final ObservableTimer timer;
	private final ObservableButton button;
	private final JSONServer server;
	private final Serial serial;
	
	private enum State {ALARM, IDLE};
	private State currentState;

	public EventTracker(Serial serial, Light led, ObservableButton button){
		
		this.serial=serial;
		this.led = led;
		
		this.server = new JSONServer();
		
		this.timer = new ObservableTimer();
		timer.addObserver(this);
		
		this.button = button;
		button.addObserver(this);
		
		currentState = State.IDLE;
	}
	
	protected void processEvent(Event ev){
		switch (currentState){
		case IDLE:
			try {
				if (ev instanceof AlarmEvent){
					sendMessage(((MessageEvent)ev));
					led.switchOn();
					this.currentState = State.ALARM;
					System.out.println("ALARM");
				} else if (ev instanceof InformationEvent){
					sendMessage(((MessageEvent)ev));
				}
			} catch (IOException ex){
				ex.printStackTrace();
			}
			break;
		case ALARM:
			try {
				if (ev instanceof InformationEvent){
					sendMessage(((MessageEvent)ev));
					led.switchOff();
				} else if (ev instanceof ButtonPressed){
					led.switchOff();
					currentState = State.IDLE;
					timer.stop();
					serial.sendMsg("s");
					System.out.println("STOP");
				}
			} catch (IOException ex){
				ex.printStackTrace();
			}
			break;
		}
	}
	
	private void sendMessage(MessageEvent msgEv) {
		ArduinoMessage msg = msgEv.getMessage();
		this.server.post(msg);
	}
	
}
