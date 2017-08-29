package com.fusaimoe.event_tracker.devices.emu;

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class SerialImpl implements com.fusaimoe.event_tracker.devices.Serial {

	private int rx;
	private int tx;
	private boolean isMsgAvailable;
	private String msg;
	private StdInputAgent auxWorker;
	
	public SerialImpl(int rx, int tx){
		this.rx = rx;
		this.tx = tx;
		try {
			auxWorker = new StdInputAgent();
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
		System.out.println(msg);
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
	
	
	class StdInputAgent extends Thread {
		public StdInputAgent(){
		}
		
		public void run(){
			System.out.println("[StdInput Emu Agent] running.");
			BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
			while (true){
				try {
					String msg = input.readLine();
					setMsg(msg);
				} catch (Exception ex){
					ex.printStackTrace();
				}
			}
		}
	}

}
