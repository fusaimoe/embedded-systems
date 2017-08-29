package com.fusaimoe.event_tracker;

import com.fusaimoe.event_tracker.common.*;

public class MessageEvent implements Event {
	private final ArduinoMessage message;

	public MessageEvent(ArduinoMessage message) {
		super();
		this.message = message;
	}

	public ArduinoMessage getMessage() {
		return message;
	}
	
}
