package com.fusaimoe.event_tracker;

import java.util.Calendar;

import com.fusaimoe.event_tracker.common.*;
import com.fusaimoe.event_tracker.devices.*;
import com.google.gson.Gson;

public class InputMsgReceiver extends BasicController {

	private EventTracker eventTracker;
	private Serial serialDevice;
	
	public InputMsgReceiver(EventTracker eventTracker, Serial serialDevice){
		this.eventTracker = eventTracker;
		this.serialDevice = serialDevice;
	}
	
	@Override
	public void run() {
		while (true){
			try {
				String msg = serialDevice.waitForMsg();
				Gson gson = new Gson();
				ArduinoMessage message = gson.fromJson(msg, ArduinoMessage.class);
				setupDate(message);
				if (message.isAlarm()){
					eventTracker.notifyEvent(new AlarmEvent(message));
				} else {
					eventTracker.notifyEvent(new InformationEvent(message));
				}
			} catch (Exception ex){
				ex.printStackTrace();
			}
		}
	}
	
	private void setupDate(ArduinoMessage message) {
		Calendar cal = Calendar.getInstance();
		message.setTime(cal.getTime().toString());
	}

}
