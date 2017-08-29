package com.fusaimoe.event_tracker.devices;

import com.fusaimoe.event_tracker.common.Event;

public class ButtonPressed implements Event {
	private Button source;
	
	public ButtonPressed(Button source){
		this.source = source;
	}
	
	public Button getSourceButton(){
		return source;
	}
}
