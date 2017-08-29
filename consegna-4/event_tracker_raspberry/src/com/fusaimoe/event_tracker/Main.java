package com.fusaimoe.event_tracker;

import com.fusaimoe.event_tracker.devices.Light;
import com.fusaimoe.event_tracker.devices.Serial;

public class Main extends Thread {
	
	public static void main(String[] args) throws Exception {

		SerialCommChannel channel = SerialCommChannel.getInstance(args[0], 9600);
		
		System.out.println("Waiting Arduino for rebooting...");
		Thread.sleep(4000);
		System.out.println("Ready.");
		
		Light led = new com.fusaimoe.event_tracker.devices.p4j_impl.Led(4);
		Serial serial = new SerialImpl(channel);
		
		EventTracker blinker = new EventTracker(led);
		InputMsgReceiver rec = new InputMsgReceiver(blinker,serial);
		blinker.start();
		rec.start();

		
	}
}