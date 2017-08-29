package com.fusaimoe.event_tracker.devices;

import com.fusaimoe.event_tracker.common.Event;

public class Tick implements Event {
	
	private long time;
	
	public Tick(long time ){
		this.time = time;
	}
	
	public long getTime(){
		return time;
	}
}
