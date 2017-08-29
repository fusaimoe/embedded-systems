package com.fusaimoe.event_tracker.common;

public abstract class BasicController extends Thread {

	protected void waitFor(long ms) throws InterruptedException{
		Thread.sleep(ms);
	}
}
