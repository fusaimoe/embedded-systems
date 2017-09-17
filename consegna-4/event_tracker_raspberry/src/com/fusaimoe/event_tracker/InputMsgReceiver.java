package com.fusaimoe.event_tracker;

import java.util.Calendar;

import com.fusaimoe.event_tracker.common.*;
import com.fusaimoe.event_tracker.devices.*;

public class InputMsgReceiver extends BasicController {

	private EventTracker eventTracker;
	private Serial serialDevice;
	
	public InputMsgReceiver(EventTracker eventTracker, Serial serialDevice){
		this.eventTracker = eventTracker;
		this.serialDevice = serialDevice;
	}
	
	@Override
	public void run() {
		Calendar cal = Calendar.getInstance();
		while (true){
			try {
				String msg = serialDevice.waitForMsg();
				BlinkerManager.getInstance().startBlinking();
				//System.out.println("MESSAGE: " + msg);
				
				try {
					
					ArduinoMessage am = new ArduinoMessageBuilder()
							.setTime(cal.getTime().toString())
							.setTemperature(Float.parseFloat(msg))
							.build();
					
					eventTracker.notifyEvent(new InformationEvent(am));
					
				} catch (NumberFormatException e) {
					
					//System.out.println("exception, message: " + msg);
					if(msg.contains("p")) {
						
						System.out.println("presence");
						
						ArduinoMessage am = new ArduinoMessageBuilder()
								.setTime(cal.getTime().toString())
								.setPresence(true)
								.build();
						
						eventTracker.notifyEvent(new InformationEvent(am));
					} else if(msg.contains("a")) {
						
						ArduinoMessage am = new ArduinoMessageBuilder()
								.setTime(cal.getTime().toString())
								.setAlarm(true)
								.build();
						
						eventTracker.notifyEvent(new AlarmEvent(am));
					}
					
				}
			} catch (Exception ex){
				ex.printStackTrace();
			}
		}
	}

}
