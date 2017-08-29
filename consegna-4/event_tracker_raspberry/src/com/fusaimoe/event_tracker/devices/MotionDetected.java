package com.fusaimoe.event_tracker.devices;

import com.fusaimoe.event_tracker.common.Event;

public class MotionDetected implements Event {
	private ObservableMotionDetectorSensor source;
	
	public MotionDetected(ObservableMotionDetectorSensor source){
		this.source = source;
	}
	
	public ObservableMotionDetectorSensor getSource(){
		return source;
	}
}
