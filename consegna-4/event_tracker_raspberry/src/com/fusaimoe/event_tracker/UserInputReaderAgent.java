package com.fusaimoe.event_tracker;


import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.nio.charset.Charset;

public class UserInputReaderAgent extends Thread {
	
	private OutputStream output;

	public UserInputReaderAgent(OutputStream output){
		this.output = output;
	}
	
	public void run(){
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		while (true){
			try {
				String st = reader.readLine();
				output.write(st.getBytes(Charset.forName("UTF-8")));
			} catch (Exception ex){
				ex.printStackTrace();
			}
		}
	}
}
