package com.fusaimoe.event_tracker.devices;

import com.fusaimoe.event_tracker.common.Event;

public class ObjDetected implements Event {
	private ProximitySensor source;
	private double distance;
	
	public ObjDetected(ProximitySensor source, double distance){
		this.source = source;
		this.distance = distance;
	}
	
	public ProximitySensor getSource(){
		return source;
	}
	
	public double getDistance(){
		return distance;
	}
}
