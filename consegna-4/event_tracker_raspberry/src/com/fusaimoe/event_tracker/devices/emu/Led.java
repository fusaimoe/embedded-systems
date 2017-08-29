package com.fusaimoe.event_tracker.devices.emu;

import java.io.IOException;

import com.fusaimoe.event_tracker.devices.Light;


public class Led implements Light {
	private int pinNum;
	private String id;

	public Led(int pinNum, String id){
		this.pinNum = pinNum;
		this.id = id;
		try {
			System.out.println("[LED "+id+"] installed on pin "+pinNum);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public Led(int pinNum){
		this(pinNum,"green");
	}	
	
	@Override
	public synchronized void switchOn() throws IOException {
		System.out.println("[LED "+id+"] ON");
	}

	@Override
	public synchronized void switchOff() throws IOException {
		System.out.println("[LED "+id+"] OFF");
	}
		
}
