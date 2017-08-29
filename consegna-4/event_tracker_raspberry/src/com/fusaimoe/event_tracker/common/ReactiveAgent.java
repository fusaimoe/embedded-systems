package com.fusaimoe.event_tracker.common;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

public abstract class ReactiveAgent extends BasicEventLoopController {
	
	protected ReactiveAgent(int size){
		super(size);
	}

	protected ReactiveAgent(){
	}
	
	protected boolean sendMsgTo(ReactiveAgent agent, Msg m){
		MsgEvent ev = new MsgEvent(m,this);
		return agent.notifyEvent(ev);
	}
}
