package com.fusaimoe.event_tracker;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.BufferedReader;
import java.io.InputStreamReader;

import javax.swing.JButton;
import javax.swing.JFrame;

public class SerialImpl implements com.fusaimoe.event_tracker.devices.Serial {

	private boolean isMsgAvailable;
	private String msg;
	private SerialCommAgent auxWorker;
	private final SerialCommChannel serial;
	
	public SerialImpl(SerialCommChannel serial){
		this.serial = serial;
		try {
			auxWorker = new SerialCommAgent(serial);
			System.out.println("Debug: SERIALIMPL");
			auxWorker.start();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	@Override
	public synchronized boolean isMsgAvailable() {
		return isMsgAvailable;
	}
	
	public synchronized String readMsg(){
		String m = msg;
		isMsgAvailable = false;
		msg = null;
		return m;
	}
	
	public synchronized void sendMsg(String msg){
		serial.sendMsg(msg);
	}
	
	synchronized void setMsg(String msg){
		this.isMsgAvailable = true;
		this.msg = msg;
		notifyAll();
	}
	
	public synchronized String waitForMsg() throws InterruptedException {
			while (!isMsgAvailable){
				wait();
			}
			String m = msg;
			isMsgAvailable = false;
			msg = null;
			return m;
	}
	
	
	class SerialCommAgent extends Thread {
		private final SerialCommChannel serial;
		
		public SerialCommAgent(SerialCommChannel serial){
			this.serial = serial;
		}
		
		public void run(){
			System.out.println("[Serial Comm Agent] running.");
			while (true){
				
				if(serial.isMsgAvailable()) {
					String msg;
					try {
						msg = serial.receiveMsg();
						setMsg(msg);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
		}
	}

}
