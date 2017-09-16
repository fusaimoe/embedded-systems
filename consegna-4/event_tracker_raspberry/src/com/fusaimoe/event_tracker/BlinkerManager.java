package com.fusaimoe.event_tracker;

import com.fusaimoe.event_tracker.devices.Light;

public class BlinkerManager {
	
	private final Light led;
	private static BlinkerManager instance = null;
	private volatile boolean running;

	private BlinkerManager(Light led) {
		this.led = led;
		this.running = false;
	}
	
	public static BlinkerManager buildInstance(Light led) {
		if(instance == null) {
			instance = new BlinkerManager(led);
		} else {
			throw new IllegalStateException();
		}
		
		return instance;
	}
	
	public static BlinkerManager getInstance() {
		if(instance != null) {
			return instance;
		}
		
		throw new IllegalStateException();
	}
	
	public void startBlinking() {
		if(!running) {
			new Blinker().start();
		}
	}
	
	private class Blinker extends Thread {
		
		@Override
		public synchronized void start() {
			super.start();
			running = true;
		}
		
		@Override
		public void run() {
			super.run();
			int i = 0;
			while(running) {
				try {
					led.switchOn();
					
					Thread.sleep(100);

					led.switchOff();
					
					Thread.sleep(100);
				} catch (Exception e) {
					e.printStackTrace();
				}
				
				if(i>=4) {
					running = false;
				}
				
				i++;
				
			}
		}
	}

}
