package com.fusaimoe.event_tracker.devices;

import com.fusaimoe.event_tracker.common.Event;

public class ButtonReleased implements Event {
	private Button source;
	
	public ButtonReleased(Button source){
		this.source = source;
	}
	
	public Button getSourceButton(){
		return source;
	}
}
