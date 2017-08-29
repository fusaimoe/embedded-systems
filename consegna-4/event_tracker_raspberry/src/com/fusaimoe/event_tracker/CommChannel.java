package com.fusaimoe.event_tracker;


/**
 * Simple interface for an async msg communication channel
 * @author aricci
 *
 */
public interface CommChannel {
	
	/**
	 * To send an message.
	 * 
	 * Asynchronous model.
	 * 
	 * @param msg
	 */
	void sendMsg(String msg);
	
	/**
	 * To receive a message. 
	 * 
	 * Blocking behaviour.
	 */
	String receiveMsg() throws InterruptedException;

	/**
	 * To check if a message is available.
	 * 
	 * @return
	 */
	boolean isMsgAvailable();

}
