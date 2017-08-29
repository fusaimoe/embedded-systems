package com.fusaimoe.event_tracker;

public class ArduinoMessage {

	String time;
	Float temperature;
	boolean presence;
	boolean alarm;
	
	public ArduinoMessage(String time, Float temperature, boolean presence, boolean alarm) {
		super();
		this.time = time;
		this.temperature = temperature;
		this.presence = presence;
		this.alarm = alarm;
	}
	
	public String getTime() {
		return time;
	}
	public void setTime(String time) {
		this.time = time;
	}
	public Float getTemperature() {
		return temperature;
	}
	public void setTemperature(Float temperature) {
		this.temperature = temperature;
	}
	public boolean isPresence() {
		return presence;
	}
	public void setPresence(boolean presence) {
		this.presence = presence;
	}
	public boolean isAlarm() {
		return alarm;
	}
	public void setAlarm(boolean alarm) {
		this.alarm = alarm;
	}
	
	
	
}
