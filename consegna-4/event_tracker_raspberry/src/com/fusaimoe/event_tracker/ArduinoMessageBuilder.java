package com.fusaimoe.event_tracker;

public class ArduinoMessageBuilder {
	String time;
	Float temperature;
	boolean presence;
	boolean alarm;
	
	public ArduinoMessageBuilder() {
		super();
		this.temperature = null;
		this.presence = false;
		this.alarm = false;
	}

	public ArduinoMessageBuilder setTime(String time) {
		this.time = time;
		return this;
	}

	public ArduinoMessageBuilder setTemperature(Float temperature) {
		this.temperature = temperature;
		return this;
	}

	public ArduinoMessageBuilder setPresence(boolean presence) {
		this.presence = presence;
		return this;
	}

	public ArduinoMessageBuilder setAlarm(boolean alarm) {
		this.alarm = alarm;
		return this;
	}
	
	public ArduinoMessage build() {
		return new ArduinoMessage(this.time, this.temperature, this.presence, this.alarm);
	}
	
}
