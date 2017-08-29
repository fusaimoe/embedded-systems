package com.fusaimoe.event_tracker.common;

public class MsgEvent implements Event {
	
	private Msg msg;
	private ReactiveAgent from;
	
	public MsgEvent(Msg msg, ReactiveAgent from){
		this.msg = msg;
		this.from = from;
	}

	public MsgEvent(Msg msg){
		this.msg = msg;
	}
	
	public Msg getMsg(){
		return msg;
	}
	
	public ReactiveAgent getFrom(){
		return from;
	}
}
