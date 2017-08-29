package com.fusaimoe.event_tracker.common;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

public abstract class BasicEventLoopController extends Thread implements Observer {
	
	public static final int defaultEventQueueSize = 50;
	protected BlockingQueue<Event> eventQueue;
	
	protected BasicEventLoopController(int size){
		eventQueue = new ArrayBlockingQueue<Event>(size);
	}

	protected BasicEventLoopController(){
		this(defaultEventQueueSize);
	}
	
	abstract protected void processEvent(Event ev);
	
	public void run(){
		while (true){
			try {
				Event ev = this.waitForNextEvent();
				this.processEvent(ev);
			} catch (Exception ex){
				ex.printStackTrace();
			}
		}
	}
	
	protected void startObserving(Observable object){
		object.addObserver(this);
	}

	protected void stopObserving(Observable object){
		object.removeObserver(this);
	}
	
	protected Event waitForNextEvent() throws InterruptedException {
		return eventQueue.take();
	}

	protected Event pickNextEventIfAvail() throws InterruptedException {
		return eventQueue.poll();
	}
	
	public boolean notifyEvent(Event ev){
		return eventQueue.offer(ev);
	}
}
