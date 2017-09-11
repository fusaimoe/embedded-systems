package com.fusaimoe.event_tracker;

import java.io.IOException;

import com.fusaimoe.event_tracker.devices.*;
public class Main extends Thread {
	
	public static void main(String[] args) throws Exception {
		
		SerialCommChannel channel = SerialCommChannel.getInstance(args[0], 9600);
		
		System.out.println("Waiting Arduino for rebooting...");
		Thread.sleep(4000);
		System.out.println("Ready.");
		
		Light l1 = new com.fusaimoe.event_tracker.devices.p4j_impl.Led(1);
		Light l2 = new com.fusaimoe.event_tracker.devices.p4j_impl.Led(4);
		Light l3 = new com.fusaimoe.event_tracker.devices.p4j_impl.Led(3);
		ObservableButton button = new com.fusaimoe.event_tracker.devices.p4j_impl.Button(0);
		
		Serial serial = new SerialImpl(channel);
		
		EventTracker ev = new EventTracker(serial, l1, l3, button);
		
		BlinkerManager.buildInstance(l2);
		InputMsgReceiver rec = new InputMsgReceiver(ev,serial);
		ev.start();
		rec.start();
		
	}
}